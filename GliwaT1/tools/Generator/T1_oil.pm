######################################################################################
#
#   File:           T1_oil.pm
#
#   Description:    Parse OIL file and extract task and interrupt configuration
#                   Assumes that OIL file is well-formed
#
#   $Author: christophger $
#
#   $Revision: 11497 $
#
#   $URL: https://gliwa.com/svn/repos/T1target/trunk/doc/internal/integration_guide/OIL/T1_oil.pm $
#
#   Copyright:      Gliwa GmbH | know- how in embedded software
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################

package T1_oil;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(readOIL theCPU getVals getRef getDescription);

use strict;
use warnings;
use File::Spec::Functions 'rel2abs', 'splitpath', 'catfile', 'catpath';

my $debug = 0;

######################################################################################
# Read OIL files into an array of characters
######################################################################################

my $checkIncludes = 'false';  # this was not required in all recent customer integrations
my @includeDirs;
my @tokens;

# Parse tree
my %oilData;

sub localReadOIL($);
sub parse($$);

sub theCPU();
sub getVals($$);
sub getRef($$$);
sub getDescription($);

sub readOIL($@)
{
    my $oilFileName = rel2abs(shift);
    my @relIncludeDirs = shift;

    foreach my $includeDir (@relIncludeDirs)
    {
        push @includeDirs, ( rel2abs( $includeDir ) );
    }

    if( $debug )
    {
        print "OIL file: \"$oilFileName\"\n";
        foreach my $dir (@includeDirs)
        {
            print "Include: \"$dir\"\n";
        }
    }

    localReadOIL( $oilFileName );
    if( $debug )
    {
        print ( (join "\n", @tokens) . "\n" );
    }

    parse( \%oilData, 0 );
}

my $inAComment = 0;     # Reading a /* comment */
my $inAString = 0;      # Reading a "string"
my $string = "";        # The "string" being read

sub localReadOIL($)
{
    my $fileName = shift;
    local *OIL;

    open OIL, "$fileName" or die "Unable to read OIL file \"$fileName\"";
    print "Reading \"$fileName\"\n" if $debug;

LINE:
    while( my $line = <OIL> )
    {
        # Remove line endings
        chomp $line;
        # Remove leading whitespace
        $line =~ s/^\s+//;

        while( $line ne "" )
        {
            if( $inAComment )
            {
                if( $line =~ m/^\*\/\s*(.*)$/ )
                {
                    $inAComment = 0;
                    $line = $1;
                }
                else
                {
                    next LINE;      # Still in the comment so get another line
                }
            }
            elsif( $inAString )
            {
                $string .= "\n";
                if( $line =~ m/^([^"]*")\s*(.*)$/ )
                {
                    $inAString = 0;
                    push @tokens, ($string . $1);
                    $string = "";
                    $line = $2;
                }
                else
                {
                    $string .= $line;
                    next LINE;      # Still in the string so get another line
                }
            }
            # Check for #include
            elsif( $line =~ m/#include\s+([<"])(.+)[">]/)
            {
                my $quotedFileName = $2;
                print "Quoted file name $quotedFileName\n" if $debug;
                my $includeFileName = "";
                if( $checkIncludes eq 'true')
                {
                    if( $1 eq "<" )
                    {
                        # Find include file in includeDirs
                        foreach my $dir (@includeDirs)
                        {
                            print (catfile(($dir), $quotedFileName) . "\n") if $debug;
                            if( -r (catfile(($dir), $quotedFileName)) )
                            {
                                $includeFileName = catfile(($dir), $quotedFileName);
                                last;
                            }
                        }
                        $includeFileName ne "" or die "Unable to find <$quotedFileName>";
                    }
                    else
                    {
                        my ($vol, $dir, $file) = splitpath( $fileName );
                        print (catpath($vol, $dir, $quotedFileName) . "\n") if $debug;
                        $includeFileName = catpath($vol, $dir, $quotedFileName);
                    }
                    localReadOIL( $includeFileName );
                }
                next LINE;
            }
            # Check for start of comment or string
            elsif( $line =~ m/^\/\*(.*)$/ )
            {
                # Start of /* comment */
                $line = $1;
                if( $line =~ m/\*\/\s*(.*)$/ )
                {
                    $line = $1;         # Comment ends in same line
                }
                else
                {
                    $inAComment = 1;    # Comment does not end in same line
                    next LINE;          # Get another line
                }
            }
            elsif( $line =~ m/^\/\// )
            {
                # Line comment, discard the rest of this line
                next LINE;
            }
            elsif( $line =~ m/^"(.*)$/ )
            {
                # Start of "string"
                $line = $1;
                if( $line =~ m/^([^"]*")\s*(.*)$/ )
                {
                    # String ends within line
                    push @tokens, ('"' . $1);
                    $line = $2;
                }
                else
                {
                    $inAString = 1;     # String does not end in same line
                    $string = '"' . $line;
                    next LINE;
                }
            }
            elsif( $line =~ m/^0x([a-fA-F0-9]+)\s*(.*)$/ )
            {
                # Got a hex token, convert to decimal
                push @tokens, (hex $1);
                $line = $2;
            }
            elsif( $line =~ m/^([{}\[\]=,;:]|(\.\.)|([+-]?\d+(\.\d+)?([eE]\d+)?)|\w+)\s*(.*)$/ )
            {
                # Got any other kind of token
                push @tokens, ($1);
                $line = $6;
            }
            else
            {
                die "Unable to lex \"$line\"";
            }
        }
    }

    close OIL;
}

######################################################################################
# Parse array of tokens
######################################################################################

# Recursive descent parser
sub parse($$)
{
    my $entry = shift;
    my $depth = shift;  # Recursion depth counter
    my $sym0;
    my $sym1;

    while( @tokens )
    {
        $sym0 = shift @tokens;

        # Skip ;
        if( $sym0 eq ';' )
        {
            next;
        }
        # Look for }
        elsif( $sym0 eq '}' )
        {
            return;
        }

        last unless @tokens;
        $sym1 = shift @tokens;
        # Ignore =
        if( $sym1 eq '=' )
        {
            last unless @tokens;
            $sym1 = shift @tokens;
        }
        print ( ("  " x $depth) . "$sym0 = $sym1\n" ) if $debug;
        if( @tokens and $tokens[0] eq '{' )
        {
            shift @tokens;
            $entry->{$sym0}->{$sym1} = {};
            parse( $entry->{$sym0}->{$sym1}, $depth + 1 );
            if( scalar @tokens > 1 and $tokens[0] eq ':' )
            {
                shift @tokens; # Discard ':'
                my $description = shift @tokens;
                $description =~ s/^"(.*)"$/$1/; # Remove quotes
                $entry->{$sym0}->{$sym1}->{'*description*'} = $description;
            }
        }
        else
        {
            if( scalar @tokens > 1 and $tokens[0] eq ':' )
            {
                shift @tokens; # Discard ':'
                my $description = shift @tokens;
                $description =~ s/^"(.*)"$/$1/; # Remove quotes
                $entry->{$sym0}->{$sym1}->{'*description*'} = $description;
            }
            else
            {
                $entry->{$sym0}->{$sym1} = 1;
            }
        }
    }
}

######################################################################################
# Return reference to the CPU object, if there is exactly one CPU object.
######################################################################################

sub theCPU()
{
    my @cpuRefs;

    if( exists $oilData{"CPU"} )
    {
        foreach my $cpu (keys %{$oilData{"CPU"}})
        {
            print "CPU $cpu\n" if $debug;
            push @cpuRefs, ($oilData{"CPU"}->{$cpu});
        }
    }
    if( scalar @cpuRefs == 1 )
    {
        return $cpuRefs[0];
    }
    return 0;
}

######################################################################################
# Return list of values for a reference and a value name.
######################################################################################

sub getVals($$)
{
    my $ref = shift;
    my $name = shift;
    my @values;

    if( exists $ref->{$name} )
    {
        @values = keys %{$ref->{$name}};
    }

    return @values;
}

######################################################################################
# Return the reference for a particular value.
######################################################################################

sub getRef($$$)
{
    my $ref = shift;
    my $name = shift;
    my $value = shift;

    if( exists $ref->{$name} and exists $ref->{$name}->{$value} )
    {
        return $ref->{$name}->{$value};
    }

    return 0;
}

######################################################################################
# Return description for a reference.
######################################################################################

sub getDescription($)
{
    my $ref = shift;

    if( exists $ref->{'*description*'} )
    {
        return $ref->{'*description*'};
    }

    return "";
}


1;
