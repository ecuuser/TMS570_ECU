######################################################################################
#
#   File:           T1_Microsar.pm
#
#   Description:    Parse OIL or arxml file and extract task and interrupt configuration
#                   Assumes that OIL file is well-formed
#                   Get OS Task and cat2 ISR IDs from tcb.h
#
#   $Author: nick $
#
#   $Revision: 14155 $
#
#   Copyright:      Gliwa GmbH | know- how in embedded software
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################
package T1_Microsar;
require Exporter;
our @ISA = ("Exporter");
our @EXPORT = qw(OsReadOsConfiguration OsGetValue OsGetSysElementReference OsGetIsrWrapper OsPerformInstrumentation OsGetRunnableDefinitions);

use strict;
use warnings;
use File::Spec::Functions 'rel2abs';
use File::stat;
use XML::Parser;


######################################################################################
# Values to be assigned by reading OS-invocation file
######################################################################################
my $mcuCore = "";               # used MCU [MPC55xx/XC2000/V850/TMS570]
my @osToPhysicalCoreIdMapping = ( 0, 1, 2 ); # Only to be specified if OS-configuration uses different core IDs than the physical ones. Specify only cors that are used by the OS
my $oilFileName = "";           # oil-file containing the OS-configuration information -> Wildcard allowed: e.g. ".\myFolder\proj*.oil" -> most recent file will be taken if more files are matching
my $arxmlFileName = "";         # alternatively: name and path of arxml file -> Wildcard allowed: e.g. ".\myFolder\proj*.arxml" -> most recent file will be taken if more files are matching
my $tcbHFileName = "";          # name and path of tcb.h. Required for parsing tasks and corresponding IDs
my $tcbCFileName = "";          # name and path of tcb.c. Mandatory if tcb.c osConfigBlock holds the ISR start adresses (mostly in newer SC3 versions) otherwise optional. Then the tcb.c will be patched to include T1_config.h which in turn performs cat2. ISR instrumentation
my @runnableParseModules = qw();# Optional: modules such RTE.c can be parsed for runnable names. Macros are created accordingly in T1_config.h (or T1_ids.h respectively)
my $cat2IsrPrefix = "default";  # Optional: prefix of ISR function names (default ones are used if parameter not defined)
my $cat2IsrSuffix = "default";  # Optional: suffix of ISR function names (default ones are used if parameter not defined)
my $crossCoreIsrPattern = '^RemoteCallCore'; # Pattern for detecting system cross-core ISR

######################################################################################
# Other global variables
######################################################################################
my $debug = 0;
my %taskIds;
my %isrIds;
my $cMacroWrappersRequired = 0;
my $taskSymbolSuffix = "func";
my $isrShims = "";
my $runnableShims = "";
my $osTimerInterruptName = "osTimerInterrupt";
my @includeDirs = ();
my @cpuFreq = (0);
my $maxTaskId = 0;
my $maxCat2Id = 0;

my $isrPrioIdentifier = "";
my $nofCores = 1;
my $osName = "unnamed OS";
my %systemElements = qw();
my %systemInfos = qw();
my $compilerSpecificSymbolPrefix = "";

#----------------------------------------------------------------------------------
sub OsParseParam($)
{

    my $currentParam = $_[0];
    if (not $currentParam =~ /^;/) # a ';' funtions as a comment operator
    {
        my $val = "";
        my $validParamFound = 0;
        my @substr = split(/;/, $currentParam);
        $currentParam = $substr[0];
        $currentParam =~ s/\s+$//;
        if( $debug )
        {
            print "$currentParam \n";
        }

        if (($val) = $currentParam =~ /-oilfile=(.*)/)              { $oilFileName      = rel2abs($val);            $validParamFound = 1; }
        if (($val) = $currentParam =~ /-osToPhysicalCoreIdMapping=(.*)/){ assignCoreIdMapping($val);            $validParamFound = 1; }
        if (($val) = $currentParam =~ /-arxmlFileName=(.*)/)        { $arxmlFileName    = rel2abs($val);            $validParamFound = 1; }
        if (($val) = $currentParam =~ /-tcbcfile=(.*)/)             { $tcbCFileName     = rel2abs($val);            $validParamFound = 1; }
        if (($val) = $currentParam =~ /-tcbhfile=(.*)/)             { $tcbHFileName     = rel2abs($val);            $validParamFound = 1; }
        if (($val) = $currentParam =~ /-runnableParseModule=(.*)/)  { push @runnableParseModules, rel2abs($val);    $validParamFound = 1; }
        if (($val) = $currentParam =~ /-mcuCore=(.*)/)              { $mcuCore          = $val;                     $validParamFound = 1; }
        if (($val) = $currentParam =~ /-cat2IsrPrefix=(.*)/)        { $cat2IsrPrefix    = $val;                     $validParamFound = 1; }
        if (($val) = $currentParam =~ /-cat2IsrSuffix=(.*)/)        { $cat2IsrSuffix    = $val;                     $validParamFound = 1; }
        if (($val) = $currentParam =~ /-remoteCallPattern=(.*)/)    { $crossCoreIsrPattern = $val;                  $validParamFound = 1; }

        if ( (not $validParamFound) and ($currentParam =~ /\s*-.*/) )
        {
            #die "error: invalid parameter $currentParam found in command line";
        }
    }
}

######################################################################################
# sub getNewestFileMatchingWildcard
######################################################################################
sub getNewestFileMatchingWildcard($)
{
    my $pathAndFileName = $_[0];
    my $fileName = File::Basename::basename($pathAndFileName);
    my $dir = "";
    my $fileSuffix = "";
    my $returnPath = "";
    my $highestModTime = 0;
    my $selectedFile = "";

    if( $fileName =~ /\*/ ) # fileName contains wildcard
    {
         my $fileNameWithStarChar = $fileName;
         $fileNameWithStarChar =~ s/\*/\\\*/;
         $pathAndFileName =~ s/$fileNameWithStarChar//;
         $dir = $pathAndFileName;
         $fileNameWithStarChar =~ /.*\.(.*)$/;
         $fileSuffix = $1;

         opendir(FILE_DIR, $dir) or die "Directory '$dir' for $pathAndFileName not found";
         my @files = grep { /\.$fileSuffix$/ } readdir(FILE_DIR);
         closedir(FILE_DIR);

         my $regExFileName = $fileName;
         $regExFileName =~ s/\*/\(\.\*\)/;
         foreach my $file (@files)
         {
            if( $file =~ /^$regExFileName$/)
            {
                $returnPath = $dir.$file;
                my $mTime = stat($returnPath)->mtime;
                if( $mTime > $highestModTime)
                {
                    $highestModTime = $mTime;
                    $selectedFile = $file;
                }
            }
         }
         if( $returnPath ne "" )
         {
            print "Wildcard for file $fileName : Selected newest file: $selectedFile\n";
            return $returnPath;
         }
         else
         {
            die "No file matched wildcard $dir$fileName";
         }
    }
    else # fileName contains no wildcard. Simply return the passed string
    {
        return $pathAndFileName;
    }
}

######################################################################################
# assign coreID mapping
######################################################################################
sub assignCoreIdMapping($)
{
    my $coreIdMappingStr = $_[0];
    if( $coreIdMappingStr =~ /^[\s]*([\-0-9]+)[\s]*,[\s]*([\-0-9]+)[\s]*,[\s]*([\-0-9]+)/ )
    {
        @osToPhysicalCoreIdMapping = ( $1, $2, $3 );
    }
    elsif( $coreIdMappingStr =~ /^[\s]*([\-0-9]+)[\s]*,[\s]*([\-0-9]+)/ )
    {
        @osToPhysicalCoreIdMapping = ( $1, $2, -1 );
    }
    elsif( $coreIdMappingStr =~ /^[\s]*([\-0-9]+)/ )
    {
        @osToPhysicalCoreIdMapping = ( $1, -1, -1 );
    }
    else
    {
        die "incorrect format of parameter -osToPhysicalCoreIdMapping!\nin T1_OsCfg.invFormat:-osToPhysicalCoreIdMapping=0,1,2";
    }
}

######################################################################################
# Parse command line
######################################################################################
sub OsReadOsConfiguration
{
    my( $invocationFile, @incDirs) = @_;

    @includeDirs = @incDirs;

    if ($invocationFile)
    {
        open (INVOKATION_FILE, "$invocationFile") or die "error: could not locate invocation file '$invocationFile.'";
        my $currentLine;
        while ($currentLine = <INVOKATION_FILE>)
        {
            &OsParseParam($currentLine);
        }
        close (INVOKATION_FILE);
    }

    if( $debug )
    {
        print "OIL file: \"$oilFileName\"\n";
        foreach my $dir (@includeDirs)
        {
            print "Include: \"$dir\"\n";
        }
    }

    if( $oilFileName ne "" )
    {
        $oilFileName = getNewestFileMatchingWildcard( $oilFileName);

        if( $arxmlFileName ne "" )
        {
            die "only one file must be specified at time: oil or arxml!";
        }
        require T1_oil;
        import T1_oil;
        T1_oil::readOIL( $oilFileName, @includeDirs );
    }
    elsif( $arxmlFileName eq "")
    {
        die "either oil or arxml file must be specified!";
    }

    ######################################################################################
    # Extract task and cat2 ISR IDs from tcb.h
    ######################################################################################

    open TCBH, $tcbHFileName or die "Unable to read \"$tcbHFileName\"";
    while( <TCBH> )
    {
        if( /^#\s*define\s+(\w+)\s+\(\(TaskType\)\s*(\d+)\)/ )
        {
            $taskIds{$1} = $2;
            if( $maxTaskId < $2 )
            {
                $maxTaskId = $2;
            }
            $cMacroWrappersRequired = 1; # in OS-variants where these macros are present there is no common cat2 ISR wrapper. Therefore, the macro wrappers per cat2 ISR are required
        }
        elsif( /^#\s*define\s+(\w+)\s+\(\(ISRType\)\s*(\d+)\)/ )
        {
            $isrIds{$1} = $2 + $maxTaskId + 1 ;
            if( $maxCat2Id < $isrIds{$1} )
            {
                $maxCat2Id = $isrIds{$1};
            }
        }
    }
    close TCBH;

    ######################################################################################
    # read tcb.c and firstly determine whether this defines osConfigBlock also holding the ISR start adresses.
    # If this applies all ISRs do have a common cat2 ISR wrapper that needs to be instrumented manually
    # otherwise each cat2 ISR does have its own wrapper and a list of macro-wrappers will have to be generated
    ######################################################################################

    my $TcbCLineNumber = 0;
    my $TcbLineNumberMatch = 1000000;
    my $currentLine;
    my $tcbCFileNameTemp = $tcbCFileName."_";

    if($tcbCFileName ne "")
    {
        if( $cMacroWrappersRequired eq 0) # in this case the osConfigBlock implicitly contains the IDs
        {
            my $idCntr = 0;
            my $foundTasks = 0;
            my $foundIsrs = 0;

            open (TCBC, "$tcbCFileName") or die "Unable to read \"$tcbCFileName\"";
            while( $currentLine = <TCBC> )
            {
                if( $currentLine =~ /translation table: task -> os-application/ )
                {
                    $foundTasks = 1;
                }
                elsif( $currentLine =~ /translation table: isr -> os-application/ )
                {
                    $foundIsrs = 1;
                }
                elsif( $currentLine =~ /\},/ )
                {
                    $foundIsrs = 0;
                    $foundTasks = 0;
                }
                elsif( $foundTasks eq 1 )
                {
                    if( $currentLine =~ /\/\*[\s]*([a-zA-Z_0-9]+)[\s]*\*\// )
                    {
                        $taskIds{$1} = $idCntr;
                        $idCntr ++;
                    }
                }
                elsif( $foundIsrs eq 1 )
                {
                    if( $currentLine =~ /\/\*[\s]*([a-zA-Z_0-9]+)[\s]*\*\// )
                    {
                        $isrIds{$1} = $idCntr;
                        $idCntr ++;
                    }
                }
            }
            close TCBC;
        }
        else # default case for SC1 and SC2 and older SC3 variants: the tasks IDs can be derived from tcb.h and wrapper macros need to be included in tcb.c
        {
            open (TCBC, "$tcbCFileName") or die "Unable to read \"$tcbCFileName\"";
            open (TCBC_TEMP, ">$tcbCFileNameTemp") or die "error: Could not open temp file '$tcbCFileNameTemp' RIGHTS?";

            while( $currentLine = <TCBC> )
            {
                $TcbCLineNumber++;
                if( $currentLine =~ /#include <osekext.h>/ )
                {
                    $TcbLineNumberMatch = $TcbCLineNumber;
                }
                if($TcbCLineNumber == ($TcbLineNumberMatch+2) && !($currentLine =~ /#ifdef T1_ENABLE/) )
                {
                   print TCBC_TEMP "#ifdef T1_ENABLE\n";
                   print TCBC_TEMP "#   include \"T1_AppInterface.h\"\n";
                   print TCBC_TEMP "#   include \"T1_config.h\"\n";
                   print TCBC_TEMP "#endif\n";
                }
                print TCBC_TEMP "$currentLine";
            }
            close TCBC;
            close TCBC_TEMP;
            rename ("$tcbCFileNameTemp", "$tcbCFileName");
        }
    }
    else # tcbCFileName not specified
    {
        if( $cMacroWrappersRequired eq 0)
        {
            die "for this OS variant parameter -tcbCFileName is mandatory! tcb.c will be left unchanged."
        }
    }

    ######################################################################################
    # define architecture (and compiler) specific symbol prefixes
    ######################################################################################

    if( $mcuCore eq "V850" )
    {
        $compilerSpecificSymbolPrefix = "_";
    }


    # define architecture specific cat2 ISR prefixes
        if( $cat2IsrPrefix eq "default") # if no suffix is defined by user -> use default ones
        {
            if( $mcuCore eq "MPC55xx" )
            {
                $cat2IsrPrefix = "";
            }
            elsif( $mcuCore eq "XC2000" )
            {
                $cat2IsrPrefix = "";
            }
            elsif( $mcuCore eq "V850" )
            {
                if( $cMacroWrappersRequired eq 1)
                {
                    $cat2IsrPrefix = "osIWrap";
                }
                else
                {
                    $cat2IsrPrefix = "";
                }
            }
        }

    # define architecture specific cat2 ISR suffixes
        if( $cat2IsrSuffix eq "default") # if no suffix is defined by user -> use default ones
        {
            if( $mcuCore eq "MPC55xx" )
            {
                if( $cMacroWrappersRequired eq 1)
                {
                    $cat2IsrSuffix = "_cat2c";
                }
                else
                {
                    $cat2IsrSuffix = "func";
                }
            }
            elsif( $mcuCore eq "XC2000" )
            {
                $cat2IsrSuffix = "func";
            }
            elsif( $mcuCore eq "V850" )
            {
                if( $cMacroWrappersRequired eq 1)
                {
                    $cat2IsrSuffix = "";
                }
                else
                {
                    $cat2IsrSuffix = "func";
                }
            }
        }

    # define architecture specific ISR-prio identifier
        if( $mcuCore eq "MPC55xx" )
        {
            $isrPrioIdentifier = "InterruptPriority";
        }
        elsif( $mcuCore eq "XC2000" )
        {
            $isrPrioIdentifier = "InterruptLevel";
        }
        elsif( $mcuCore eq "TMS570" )
        {
            $isrPrioIdentifier = "InterruptLevel";
        }
        elsif( $mcuCore eq "V850" )
        {
            $isrPrioIdentifier = "InterruptLevel";
            if( $cMacroWrappersRequired eq 1)
            {
                $isrShims .= <<EOT;
#ifdef osdKillTaskIsrPossible
#   if osdKillTaskIsrPossible
#       define T1_ISR_ARG_TYPE osuint32
#       define T1_ISR_ARG SPtoStore
#   else /* !osdKillTaskIsrPossible */
#       define T1_ISR_ARG_TYPE void
#       define T1_ISR_ARG
#   endif /* osdKillTaskIsrPossible */
#endif /* defined osdKillTaskIsrPossible */
EOT
            }
        }
        else
        {
            die "No MCU via parameter -mcuCore defined";
        }



    ######################################################################################
    # Read OIL-file for priorities, max activations as well as additional information
    ######################################################################################

    if( $oilFileName ne "" )
    {
        my $cpuRef = theCPU( );

        $cpuRef or die "Unable to find unique CPU";

        # Get tasks
        my $oilNofApplications = 1;
        my @AppNames = ();

        if( @AppNames = getVals( $cpuRef, 'APPLICATION' ) )  #only applicable if more than one system
        {
            $oilNofApplications = scalar @AppNames;
        }
        else #only one system
        {
            $oilNofApplications = 1;
        }

        foreach my $taskName ( getVals( $cpuRef, 'TASK' ) )
        {
            exists $taskIds{$taskName} or die "Found task \"$taskName\" not in tcb.h";

            my $taskRef = getRef( $cpuRef, 'TASK', $taskName );
            my @priorities = getVals( $taskRef, 'PRIORITY' );
            next unless scalar @priorities == 1;
            my $taskDesc = getDescription( $taskRef );
            my $taskCore;

            if($oilNofApplications > 1) # explicit applications: multi-core system -> perform task to core mapping
            {
                foreach my $appName ( @AppNames )
                {
                    my $appRef      = getRef( $cpuRef, 'APPLICATION', $appName );
                    my @cores       = getVals( $appRef, 'CORE' );
                    my @taskNames   = getVals( $appRef, 'TASK' );

                    if( scalar @cores == 0 ) # some Single-Core projects do actually use two applications in this case fix to core 0
                    {
                        $cores[0] = 0;
                    }

                    foreach my $task ( @taskNames )
                    {
                        if( $task eq $taskName)
                        {
                            $taskCore = $osToPhysicalCoreIdMapping[$cores[0]];
                            if($taskCore > $nofCores - 1 )
                            {
                                $nofCores = $taskCore + 1;
                            }
                            if($debug)
                            {
                                print "$taskName scheduled on core $taskCore\n";
                            }
                        }
                    }
                }
            }
            else   # no explicit application: single-core system
            {
                $taskCore = $osToPhysicalCoreIdMapping[0];
            }
            $systemElements{"Task"}{$taskName} = { "Name"           => $taskName,
                                                   "SymbolName"     => ($compilerSpecificSymbolPrefix.$taskName.$taskSymbolSuffix),
                                                   "Comment"        => $taskDesc,
                                                   "Offset"         => 0,
                                                   "Period"         => 0,
                                                   "ID"             => $taskIds{$taskName},
                                                   "Priority"       => $priorities[0],
                                                   "Core"           => "all", #formerly $osToPhysicalCoreIdMapping[$taskCore]. Changed to address cross-core activations
                                                   "ScriptInternalCore" => $taskCore,
                                                   "MaxActivations" => 1,
                                                   "Type"           => "Task" };
        }

        # Handle OS timer ISR and any OS cross-core ISRs
        my @oss = getVals( $cpuRef, 'OS' );
        scalar @oss == 1 or die "Unable to find unique OS";
        $osName = $oss[0];
        my $osRef = getRef( $cpuRef, 'OS', $osName );
        @cpuFreq = getVals( $osRef, 'CpuFrequency' );
        my @sysTimers = getVals( $osRef, 'SystemTimer' );
        scalar @sysTimers == 1 or die "Unable to find unique OS timer";
        my $sysTimerRef = getRef( $osRef, 'SystemTimer', $sysTimers[0] );

        if( $sysTimers[0] ne "UserDefined" )
        {
            my @sysTimerPrios;
            my $sysTimerPrio;


            if( $mcuCore eq "MPC55xx" )
            {
                @sysTimerPrios = getVals( $sysTimerRef, 'InterruptPriority' );
                scalar @sysTimerPrios == 1 or die "Unable to find SystemTimer prio";
                $sysTimerPrio = 1000 + $sysTimerPrios[0];   # Ensure all ISRs have higher priority than all tasks
            }
            elsif( $mcuCore eq "XC2000" )
            {
                # no system Timer ISR found so far
            }
            elsif( $mcuCore eq "V850" or $mcuCore eq "TMS570" )
            {
                @sysTimerPrios = getVals( $osRef, 'SystemTimerIntLevel' );

                if( scalar @sysTimerPrios != 1 ) # if nothing found try attributes SystemTimerIntPriority next
                {
                    @sysTimerPrios = getVals( $osRef, 'SystemTimerIntPriority' );
                }

                scalar @sysTimerPrios == 1 or die "Unable to find SystemTimer prio";
                $sysTimerPrio = 1000 - $sysTimerPrios[0];   # Ensure all ISRs have higher priority than all tasks
            }

            $systemElements{"Interrupt"}{$osTimerInterruptName} = {    "Name"           => $osTimerInterruptName,
                                                                       "Comment"        => "",
                                                                       "Offset"         => 0,
                                                                       "Period"         => 0,
                                                                       "Priority"       => $sysTimerPrio,
                                                                       "Core"           => "all",
                                                                       "Type"           => "Interrupt"};

            if( not exists $isrIds{$osTimerInterruptName} ) # check if osTimerInterrupt has already an ID. If not, it is not defined as an cat2 ISR. Add as ordinary cat1 ISR.
            {
                $maxCat2Id ++ ;
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "ID" }         = $maxCat2Id;
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "SymbolName" } = $osTimerInterruptName;
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "Category" }   = 1;
            }
            else # handled as ordinary cat2 ISR
            {
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "ID" }         = $isrIds{$osTimerInterruptName};
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "SymbolName" } = ($compilerSpecificSymbolPrefix.$cat2IsrPrefix.$osTimerInterruptName.$cat2IsrSuffix);
                $systemElements{"Interrupt"}{$osTimerInterruptName}{ "Category" }   = 2;

                if( $cMacroWrappersRequired eq 1)
                {
                    AddIsrToIsrShims($osTimerInterruptName);
                }
            }

            foreach my $curCrossCoreIsrName ( keys %isrIds )
            {
                if( $curCrossCoreIsrName =~ /$crossCoreIsrPattern(\d+)/ )
                {
                    # Found a cross-core ISR
                    my $curCoreId = $1;
                    $systemElements{"Interrupt"}{$curCrossCoreIsrName}
                        = {
                            "Name"          => $curCrossCoreIsrName,
                            "ID"            => $isrIds{$curCrossCoreIsrName},
                            "SymbolName"    => ($compilerSpecificSymbolPrefix.$curCrossCoreIsrName.$cat2IsrSuffix),
                            "Category"      => 2,
                            "Comment"       => "",
                            "Offset"        => 0,
                            "Period"        => 0,
                            "Priority"      => 1000,   # TMP TMP TMP lowest priority
                            "Core"          => $curCoreId,
                            "Type"          => "Interrupt"
                        };
                    if( $cMacroWrappersRequired )
                    {
                        AddIsrToIsrShims($curCrossCoreIsrName);
                    }
                }
            }
        }

        my $curCat = 2;

        # Get application ISRs
        foreach my $curIsrName ( getVals( $cpuRef, 'ISR' ) )
        {
            my $isrPrio = "";
            my $isrRef = getRef( $cpuRef, 'ISR', $curIsrName );
            my @cats = getVals( $isrRef, 'CATEGORY' );
            my $isrDesc = getDescription( $isrRef );
            next unless scalar @cats == 1;
            # osCAN-specific attributes
            my @srcs = getVals( $isrRef, 'ExceptionSource' );
            if( scalar @srcs ne 1 ) # try attribute ExceptionType next
            {
                @srcs = getVals( $isrRef, 'ExceptionType' );
            }
            if( scalar @srcs == 1 ) # exception source is available -> grep only external interrupts
            {
                if( $srcs[0] eq 'ExternalInterrupt' )
                {
                    my $extIntRef = getRef( $isrRef, 'ExceptionSource', 'ExternalInterrupt' );
                    my @isrPrios = getVals( $extIntRef, 'InterruptPriority' ); # attribute is either InterruptPriority
                    if( scalar @isrPrios ne 1 )
                    {
                        @isrPrios = getVals( $extIntRef, 'InterruptLevel' ); # or InterruptLevel
                    }
                    if( scalar @isrPrios == 1 )
                    {
                        $isrPrio = $isrPrios[0];
                    }
                }
                elsif( $srcs[0] eq 'EIINT' )
                {
                    my $extIntRef = getRef( $isrRef, 'ExceptionType', 'EIINT' );

                    my @isrPrios = getVals( $extIntRef, 'InterruptPriority' ); # attribute is either InterruptPriority
                    if( scalar @isrPrios ne 1 )
                    {
                        @isrPrios = getVals( $extIntRef, 'InterruptLevel' ); # or InterruptLevel
                    }
                    if( scalar @isrPrios == 1 )
                    {
                        $isrPrio = $isrPrios[0];
                    }
                }
            }
            else # exception source not available -> grep all available interrupts
            {
                my @isrPrios = getVals( $isrRef, 'InterruptPriority' ); # attribute is either InterruptPriority
                if( scalar @isrPrios ne 1 )
                {
                    @isrPrios = getVals( $isrRef, 'InterruptLevel' ); # or InterruptLevel
                }
                if( scalar @isrPrios == 1 )
                {
                    $isrPrio = $isrPrios[0];
                }
            }

            my $isrCore;

            if( $isrPrio ne "" )
            {
                if($oilNofApplications > 1) # explicit applications: multi-core system -> perform ISR to core mapping
                {
                    foreach my $appName ( @AppNames )
                    {
                        my $appRef      = getRef( $cpuRef, 'APPLICATION', $appName );
                        my @cores       = getVals( $appRef, 'CORE' );
                        my @isrNames    = getVals( $appRef, 'ISR' );

                        if( scalar @cores == 0 ) # some Single-Core projects do actually use two applications in this case fix to core 0
                        {
                            $cores[0] = 0;
                        }

                        foreach my $isr ( @isrNames )
                        {
                            if( $isr eq $curIsrName)
                            {
                                $isrCore = $osToPhysicalCoreIdMapping[$cores[0]];
                                if($isrCore > $nofCores - 1 )
                                {
                                    $nofCores = $isrCore + 1;
                                }
                                if($debug)
                                {
                                    print "$isr scheduled on core $isrCore\n";
                                }
                            }
                        }
                    }
                }
                else   # no explicit application: single-core system
                {
                    $isrCore = $osToPhysicalCoreIdMapping[0];
                }
                # Create a system element for each external interrupt handler
                if( $mcuCore eq "V850" or $mcuCore eq "TMS570" )
                {
                    $isrPrio = 1000 - $isrPrio; # priorities for ISRs are inverted
                }
                else
                {
                    $isrPrio += 1000;   # Ensure all ISRs have higher priority than all tasks
                }

                $systemElements{"Interrupt"}{$curIsrName} = { "Name"            => $curIsrName,
                                                               "Comment"        => $isrDesc,
                                                               "Offset"         => 0,
                                                               "Period"         => 0,
                                                               "Priority"       => $isrPrio,
                                                               "Core"           => $isrCore,
                                                               "Type"           => "Interrupt"};
                if( $cats[0] == 1 )
                {
                    # cat 1 ISRs have not yet an ID. this needs to be appended after all existing cat2 ISRs derived from tcb.h
                    # REVIEWNOTE $maxCat2Id is being abused as the maximum Cat1 ID
                    $maxCat2Id ++;
                    $systemElements{"Interrupt"}{$curIsrName}{ "ID" }         = $maxCat2Id;
                    $systemElements{"Interrupt"}{$curIsrName}{ "SymbolName" } = $curIsrName;
                    $systemElements{"Interrupt"}{$curIsrName}{ "Category" }   = 1;

                }
                elsif( $cats[0] == 2 )
                {
                    # cat2 ISRs have already been assigned an ID from tcb.h
                    $systemElements{"Interrupt"}{$curIsrName}{ "ID" } = $isrIds{$curIsrName};
                    $systemElements{"Interrupt"}{$curIsrName}{ "SymbolName" } = ($compilerSpecificSymbolPrefix.$cat2IsrPrefix.$curIsrName.$cat2IsrSuffix);
                    $systemElements{"Interrupt"}{$curIsrName}{ "Category" }   = 2;

                    if(  $cMacroWrappersRequired eq 1 )
                    {
                        AddIsrToIsrShims($curIsrName);
                    }
                }
            }
        }
    }
    elsif( $arxmlFileName ne "" ) # parse arxml if no oil file is available
    {
        $arxmlFileName = getNewestFileMatchingWildcard( $arxmlFileName);
        my $pXML = new XML::Parser ();
        $pXML->setHandlers (Start => \&XML_Start,End => \&XML_End,Char=>\&XML_Content );
        $pXML->parsefile ($arxmlFileName);
    }
    else
    {
        die "neither oil.file nor arxml file specified";
    }

    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
    my $dateAndTime = sprintf "on %02d.%02d.%04d at %02d:%02d:%02d", $mday, ($mon + 1), ($year + 1900), $hour, $min, $sec;
    my @isCoreUnused = ( 1,1,1);

    for my $core (0..2)
    {
        if( $osToPhysicalCoreIdMapping[$core] ne "-1" )
        {
            $isCoreUnused[$osToPhysicalCoreIdMapping[$core]] = 0;
        }
    }

    $systemElements{"OS"}{'Info'} = {   "GenDate"               => $dateAndTime,
                                        "GenSource"             => ($oilFileName.$arxmlFileName), # one or the other must be empty anyway
                                        "NofCores"              => ($osToPhysicalCoreIdMapping[$nofCores-1]+1),
                                        "UnusedCoreLookupTable" => (\@isCoreUnused),
                                        "CpuFreq"               => $cpuFreq[0]};

    ######################################################################################
    # Read runnables from RTE.c and others if desired:
    ######################################################################################

    my $runnableIdCntr = 0;

    foreach my $runnableParseModule (@runnableParseModules)
    {
        my $currentTask = "";
        my $isTask = 0;
        my $runnablePosInTask = 0;
        my @symbolsPerTask = qw();
        my $curRunnable = "";
        my $foundStartMacro = 0;
        my $excludeMacro = "";

        open (RUN_MOD, "$runnableParseModule") or die "Unable to read \"$runnableParseModule\"";

        while( $currentLine = <RUN_MOD> )
        {
            if( $currentLine =~ /^TASK\((.*)\)/ )
            {
                $isTask = 1;
                $currentTask = $1;
                $excludeMacro = "T1_EXCLUDE_".uc($currentTask)."_RUNNABLES";
                @symbolsPerTask = qw(); # clear on new task definition
                $runnableShims .= <<EOT;
#   if !defined $excludeMacro
EOT
            }
            if( $isTask eq 1 )
            {
                if( $foundStartMacro eq 1)
                {
                    chomp($currentLine);
                    $currentLine =~ s/\(\);//;
                    $currentLine =~ s/\s*//;
                    my $runnableName = $currentLine;
                    my $startMacro = "Rte_Runnable_".$curRunnable."_Start";
                    my $stopMacro = "Rte_Runnable_".$curRunnable."_Return";
                    $curRunnable =~ s/_$runnableName//;
                    my $swcRef = $curRunnable;

                    $systemElements{"Runnable"}{$runnableName} = {"Name"        => $runnableName,
                                                               "SymbolName"     => ($compilerSpecificSymbolPrefix.$runnableName),
                                                               "ID"             => $runnableIdCntr,
                                                               "PosInTask"      => $runnablePosInTask,
                                                               "StartMacro"     => $startMacro,
                                                               "TaskRef"        => $currentTask,
                                                               "SwcRef"         => $swcRef,
                                                               "Core"           => ($systemElements{"Task"}{$currentTask}{"ScriptInternalCore"}),
                                                               "Comment"        => "",
                                                               "Type"           => "RunnableDynamic"};
                    $runnablePosInTask ++;
                    $runnableIdCntr ++;
                    push @symbolsPerTask, ($compilerSpecificSymbolPrefix.$runnableName);
                    $foundStartMacro = 0;
                    $runnableShims .= <<EOT;
#       undef ${startMacro}
#       define ${startMacro}()   T1_TraceEventFast(T1_RUNNABLE_START, T1_${runnableName}_ID)
#       if !defined T1_DO_NOT_TRACE_RUNNABLE_RETURN
#           undef ${stopMacro}
#           define ${stopMacro}()   T1_TraceEventFast(T1_RUNNABLE_STOP, T1_${runnableName}_ID)
#       endif /* !defined T1_DO_NOT_TRACE_RUNNABLE_RETURN */

EOT
                }
                elsif( $currentLine =~ /Rte_Runnable_(.*)_Start\(\);/ )
                {
                        $curRunnable = $1;
                        $foundStartMacro = 1;
                }
                elsif( $currentLine =~ /^\}/ )
                {
                    $isTask = 0;
                    $runnableShims .= <<EOT;
#   endif /* !defined $excludeMacro */

EOT
                    my @array_ref = @symbolsPerTask;
                    $systemElements{"SymbolGroup"}{$currentTask} = {   "Name"               => ($currentTask."_Runnables"),
                                                                       "IsCode"             => "true",
                                                                       "MeasureDuration"    => 1000,
                                                                       "FocusIntervalCount" => 16777216,
                                                                       "TraceCount"         => 0,
                                                                       "Core"               => ($systemElements{"Task"}{$currentTask}{"ScriptInternalCore"}),
                                                                       "SymbolGroupElemRef" => (\@array_ref) };

                }
            }
        }
        close(RUN_MOD);
    }
}


######################################################################################
# Common routine in order to append ISRs to th eISR shims
######################################################################################
sub AddIsrToIsrShims
{
    my $isrName = shift;

    if( $mcuCore eq "MPC55xx" )
    {
        $isrShims .= <<EOT;

#define ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}                                    \\
${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_(void);                                    \\
osqFunc1 osuint32 osqFunc2 ${cat2IsrPrefix}$isrName${cat2IsrSuffix}(void)             \\
{                                                           \\
    osuint32 retCode;                                       \\
    T1_TraceEvent( T1_START, T1_${isrName}_ID );            \\
    retCode = ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_();                          \\
    T1_TraceEvent( T1_STOP, T1_${isrName}_ID );             \\
    return retCode;                                         \\
}                                                           \\
osqFunc1 osuint32 osqFunc2 ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_
EOT
    }
    elsif( $mcuCore eq "XC2000" )
    {
        $isrShims .= <<EOT;

#   define ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}                                 \\
    ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_(void);                                \\
    void ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}(void)                             \\
    {                                                       \\
        T1_TraceEvent( T1_START, T1_${isrName}_ID );        \\
        ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_();                                \\
        T1_TraceEvent( T1_STOP, T1_${isrName}_ID );         \\
    }                                                       \\
    void ${cat2IsrPrefix}${isrName}${cat2IsrSuffix}_
EOT
    }
    elsif( $mcuCore eq "V850" )
    {
        $isrShims .= <<EOT;

#define $cat2IsrPrefix${isrName}${cat2IsrSuffix}                              \\
$cat2IsrPrefix${isrName}${cat2IsrSuffix}_(T1_ISR_ARG_TYPE T1_ISR_ARG);        \\
osuint32 $cat2IsrPrefix${isrName}${cat2IsrSuffix}(T1_ISR_ARG_TYPE T1_ISR_ARG) \\
{                                                                   \\
    osuint32 retCode;                                               \\
    T1_TraceEvent( T1_START, T1_${isrName}_ID );                    \\
    retCode = $cat2IsrPrefix${isrName}${cat2IsrSuffix}_(T1_ISR_ARG);          \\
    T1_TraceEvent( T1_STOP, T1_${isrName}_ID );                     \\
    return retCode;                                                 \\
}                                                                   \\
osuint32 $cat2IsrPrefix${isrName}${cat2IsrSuffix}_
EOT
    }
}

######################################################################################
# Routines for arxml parsing:
######################################################################################
my $starttag;
my $endtag;
my $content;
my $pointerValue;
my $currentShortName = "";
my $isShortName = 0;
my $isDefinitionRef = 0;
my $isValue = 0;
my $isNofCores = 0;

my $isTask = 0;
my $isTaskName = 0;
my $isTaskActivation = 0;
my $isTaskPriority = 0;
my $isTaskType = 0;
my $curTaskName = "";
my $curTaskActivation = 0;
my $curTaskPrio = 0;

my $isIsr = 0;
my $isIsrName = 0;
my $isIsrCategory = 0;
my $isIsrPriority = 0;
my $isIsrSpecialFuncName = 0;
my $isIsrType = 0;
my $isSystemTimerPriority = 0;
my $curIsrName = "";
my $curIsrCategory = 0;
my $curIsrPrio = 0;
my $curIsrSpecialFuncName = "";
my $curSystemTimerName = "";

sub XML_Start  # called on detection of tag start
{
    $pointerValue  = shift;
    $starttag= shift;
    chomp $starttag;

    if($starttag eq "SHORT-NAME")
    {
       $isShortName = 1;
    }
    elsif( $starttag eq "DEFINITION-REF")
    {
        $isDefinitionRef = 1;
    }
    elsif( $starttag eq "VALUE")
    {
        $isValue = 1;
    }


}
sub XML_End  # called on detection of tag stop
{
    ($pointerValue,$endtag) = @_;

    if($endtag eq "SHORT-NAME")
    {
       $isShortName = 0;
    }
    elsif( $endtag eq "DEFINITION-REF")
    {
        $isDefinitionRef = 0;
    }
    elsif( $endtag eq "VALUE")
    {
        $isValue = 0;
    }
    elsif( $endtag eq "ECUC-CONTAINER-VALUE" ) #end of task definition indicated by this tag
    {

        if( $isTask eq 1)
        {
            $systemElements{"Task"}{$curTaskName} = {  "Name"               => $curTaskName,
                                                       "SymbolName"         => ($compilerSpecificSymbolPrefix.$curTaskName.$taskSymbolSuffix),
                                                       "Comment"            => "",
                                                       "Offset"             => 0,
                                                       "Period"             => 0,
                                                       "ID"                 => $taskIds{$curTaskName},
                                                       "Priority"           => $curTaskPrio,
                                                       "Core"               => "all",
                                                       "ScriptInternalCore" => "all", # cannot be properly distinguished from xml -> assign to all
                                                       "MaxActivations"     => 1,
                                                       "Type"               => "Task" };
            $isTask = 0;
        }
        elsif( $isIsr eq 1)
        {
            $isIsr = 0;

            if( $mcuCore eq "V850" or $mcuCore eq "TMS570" )
            {
                $curIsrPrio = 1000 - $curIsrPrio; # priorities for ISRs are inverted
            }
            else
            {
                $curIsrPrio += 1000;   # Ensure all ISRs have higher priority than all tasks
            }

            $systemElements{"Interrupt"}{$curIsrName} = { "Name"            => $curIsrName,
                                                           "Comment"        => "",
                                                           "Offset"         => 0,
                                                           "Period"         => 0,
                                                           "Priority"       => $curIsrPrio,
                                                           "Core"           => "all", # cannot be properly distinguished from arxml
                                                           "Type"           => "Interrupt"};

            if( $curIsrCategory == 1 )
            {
                # cat 1 ISRs have not yet an ID. this needs to be appended after all existing cat2 ISRs derived from tcb.h
                $maxCat2Id ++;
                $systemElements{"Interrupt"}{$curIsrName}{ "ID" }         = $maxCat2Id;
                $systemElements{"Interrupt"}{$curIsrName}{ "SymbolName" } = $curIsrName;
                $systemElements{"Interrupt"}{$curIsrName}{ "Category" }   = 1;

            }
            elsif( $curIsrCategory == 2 )
            {
                # cat2 ISRs have already been assigned an ID from tcb.h
                $systemElements{"Interrupt"}{$curIsrName}{ "ID" } = $isrIds{$curIsrName};
                $systemElements{"Interrupt"}{$curIsrName}{ "SymbolName" } = ($compilerSpecificSymbolPrefix.$cat2IsrPrefix.$curIsrName.$cat2IsrSuffix);
                $systemElements{"Interrupt"}{$curIsrName}{ "Category" }   = 2;

                if( $cMacroWrappersRequired )
                {
                    AddIsrToIsrShims($curIsrName);
                }
            }
        }

    }
}
sub XML_Content  # called on detection of chars
{
    ($pointerValue,$content)=@_;

    chomp($content);
    $content=~ s/\s+$//g;  # the callback does often return strings containing only lots of white spaces

    if( $isShortName eq 1)
    {
        $currentShortName = $content;
        $isTaskName = 1;
    }


    if( $isDefinitionRef eq 1)
    {
        if( $content =~ /OsTask$/ )
        {
            $curTaskName = $currentShortName;
            $isTask = 1;
        }
        elsif( $content =~ /OsTaskActivation$/ )
        {
            $isTaskActivation = 1;
        }
        elsif( $content =~ /OsTaskPriority$/ )
        {
            $isTaskPriority = 1;
        }
        elsif( $content =~ /OsIsr$/ )
        {
            $curIsrName = $currentShortName;
            $isIsr = 1;
        }
        elsif( $content =~ /OsIsrCategory$/ )
        {
            $isIsrCategory = 1;
        }
        elsif( $content =~ /OsIsrInterruptPriority$/ )
        {
            $isIsrPriority = 1;
        }
        elsif( $content =~ /OsIsrFunctionName$/ )
        {
            $isIsrSpecialFuncName = 1;
        }
        elsif( $content =~ /OsNumberOfCores$/ )
        {
            $isNofCores = 1;
        }
        elsif( $content =~ /OsOSSystemTimer\/(.*)\/OsOSInterruptPriority$/ )
        {
            $isSystemTimerPriority = 1;
        }
    }

    if( $isValue eq 1)
    {
        if( $isTaskActivation eq 1)
        {
            $curTaskActivation = $content;
            $isTaskActivation = 0;
        }
        elsif( $isTaskPriority eq 1)
        {
            $curTaskPrio = $content;
            $isTaskPriority = 0;
        }
        elsif( $isIsrPriority eq 1)
        {
            $curIsrPrio= $content;
            $isIsrPriority = 0;
        }
        elsif( $isIsrCategory eq 1)
        {
            $content =~ s/[a-zA-Z_]+//;
            $curIsrCategory = $content;
            $isIsrCategory = 0;
        }
        elsif( $isIsrSpecialFuncName eq 1)
        {
            $curIsrSpecialFuncName = $content;
            $isIsrSpecialFuncName = 0;
        }
        elsif( $isSystemTimerPriority eq 1)
        {
            $curIsrPrio= $content;
            $isSystemTimerPriority = 0;
            $curIsrName = $osTimerInterruptName;

            $systemElements{"Interrupt"}{$curIsrName} = {  "Name"           => $curIsrName,
                                                           "SymbolName"     => ($compilerSpecificSymbolPrefix.$cat2IsrPrefix.$curIsrName.$cat2IsrSuffix),
                                                           "Comment"        => "",
                                                           "Offset"         => 0,
                                                           "Period"         => 0,
                                                           "ID"             => $isrIds{$curIsrName},
                                                           "Priority"       => ($curIsrPrio + 1000),
                                                           "Core"           => "all",
                                                           "Type"           => "Interrupt",
                                                           "Category"       => 2};
            if( $cMacroWrappersRequired eq 1 )
            {
                AddIsrToIsrShims($curIsrName);
            }
        }
        elsif( $isNofCores eq 1)
        {
            $nofCores = $content;
            $isNofCores = 0;
        }
    }

}

sub OsGetValue
{
    my($ref, $key, $name) = @_;

    if( exists {%$ref}->{$key}->{$name})
    {
        return  {%$ref}->{$key}->{$name};
    }
    return 0;
}

sub OsGetSysElementReference($)
{
    my $name = $_[0];
    if( exists $systemElements{$name} )
    {
        return \%{$systemElements{$name}};
    }

    return 0;
}

sub OsGetIsrWrapper()
{
    return $isrShims;
}

sub OsGetRunnableDefinitions()
{
    return $runnableShims;
}

sub OsPerformInstrumentation()
{
}

1;
