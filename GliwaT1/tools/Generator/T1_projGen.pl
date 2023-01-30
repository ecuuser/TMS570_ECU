######################################################################################
#
#   File:           T1_PreBuild.pl
#
#   Description:    Reading OS-configuration using OS-specific Perl-module
#                   Read parameters from T1 invocation files
#                   Generate T1_config.h and .t1p file
#
#   $Author: gunter $
#
#   $Revision: 13509 $
#
#   Copyright:      Gliwa GmbH | know- how in embedded software
#                   Weilheim i.OB.
#                   All rights reserved
#
######################################################################################
use strict;
use warnings;
use File::Spec::Functions ':ALL';
use File::Copy;
use File::Basename;
use File::Path;
use File::stat;


File::Basename::fileparse_set_fstype("MSWin32");

######################################################################################
# global variables. Values are to be assigned by reading invocation files
######################################################################################

#paths of required files:
my @inlineHeaders = qw();                           # the content of those files is copied to the T1 prject file (external data). Specify path and file name. Use next parameter optionally
my @includeHeaders = qw();                          # these files are referenced in the T1 project file. The T1 GUI parses the contents and searches for systemElements. Specify path and file name. Use previous parameter optionally
my $configHeader = "";                              # name and path of header file being generated containing T1 configuration parameter macros (and task/ISR-ID macros if $idHeader is not specified)
my $symbolFile = "";                                # name and path of symbol file being referenced by the T1 project file -> Wildcard allowed: e.g. ".\myFolder\proj*.elf"
my $projectFile = "";                               # name and path of T1 project file being generated

#paths of optional files:
my $runnableHeader = "";                            # name and path of header file being generated containing T1 definitions for runnable start/stop macros (only if supported by OS-specific Perl-module)
my $idHeader = "";                                  # name and path of header file being generated containing T1 task and ISR-ID macros. If specified no ID macros are generated to $configHeader
my $bidHeader = "";                                 # name and path of header file being generated conatining T1 Build ID. If not specified the BID will be generated into idHeader
my @t1pSymbolIncludeFiles = qw();                   # name and path of auxiliary t1p-files containing T1SymbolsPart (such as symbol groups)

#parameters that use default value if omitted:
my $copySymbolFile = "false";                       # copy symbol-file to T1 project path [true/false]
my $copyIncludeHeader = "false";                    # copy include headers to T1 project path [true/false]
my $generateBuildId = "true";                       # generate Build ID (BID) everytime the Perl script is executed. The BID is propagated to the t1p-file and T1_config.h and by that to the executable. The GUI checks if symbol-file and target-code are consistent
my $projectName = "T1 project";                     # any project name
my $readPreviousT1p = "true";                       # read user-configured parts from previous t1p (if exists) and copy to new t1p
my $storeTimingInformation = "";                    # store timing information in t1p [true/false]

my $useSameConnectionForAllSystems = 'true';        # are all systems using the same connection? [true/false]
my $txCycle = 10;                                   # TX cycle of T1 GUI
my $canBitrate = 500000;                            # CAN Bitrate
my $canHardware = 'U2C';                            # CAN hardware [U2C/VECTOR]
my $canUseFixedBlockSize = 'true';                 # GUI CAN TX-messages always use DLC=8
my $usingMulticoreLibs = 'false';                   # using Multicore-Libs [true/false]
my $bigEndian = "false";                            # target is Big Endian [true/false]
my $cortexM = "false";                              # is target ARM cortex M [true/false]


#parameters that are omitted if omitted:
my $timeoutRx = "";                                 # The receive timeout is the maximum time allowed between reception of two frames of the same message.This needs to be large enough to allow for network traffic and routing delays between the host and the target [multiple of t1HandlerPeriodMs of communication core]
my $timeoutTx = "";                                 # The transmit timeout is the maximum time allowed for (retrying) the sending of a frame. This needs to be large enough to allow for queuing in the CAN layer(s), typically a smaller number than the receive timeout [multiple of t1HandlerPeriodMs of communication core]
my $timeoutResponse = "";                           # It is the maximum time permitted between transmitting the last frame of a message that requires acknowledgement and receiving the last frame of that acknowledgement. It is typically very much larger than the GCP timeout limits, since it needs to allow for the T1 GUI to respond in addition to transmission and reception delays [multiple of t1HandlerPeriodMs of communication core]
my $initFeatureMask = "";                           # string of initial application feature mask [e.g. (T1_AF_TRACE_STARUP | T1_AF_MEASURE_T1_HANDLER)]
my $mainTickDuration = "";                          # This represents the tickduration for the main/synchronization clock. The GUI needs this to merge multicore traces. Strictly required for Multicore systems!
my $syncTimeBitLength = 29;                         # Synchronisation of Multicore systems requires a timer resolution of at least 24 bits
my @configHeaderIncludes = qw();                    # header files to be included in T1_config.h ["myFileToBeIncluded.h"]
my @idHeaderIncludes = qw();                        # header files to be included in idHeader ["myFileToBeIncluded.h"]
my @runnableHeaderIncludes = qw();                  # header files to be included in runnableHeader ["myFileToBeIncluded.h"]

#these connection parameters are project-specific (and thus global) if useSameConnectionForAllSystems == true
#if system-specific connections-settings are required state -useSameConnectionForAllSystems=false and add these parameters to each system
my @connectionType = ( 'pure T1', 'pure T1', 'pure T1');        # connection-type: [pure T1/Diagnosis]
my @canRxID = ( '0x6FA', '0x6FA', '0x6FA');                     # CAN ID ECU to GUI [0x6FA]
my @canTxID = ( '0x6CB', '0x6CB', '0x6CB');                     # CAN ID GUI to ECU [0x6CB]
my @canExtendedIds = ( 'false', 'false', 'false');              # use extended CAN IDs [true/false]
my @diagAddressingMode = ( 'normal', 'normal', 'normal');       # Diagnosis: addressing mode: [normal/extended]
my @diagSourceAddr = ( '0xFA', '0xFA', '0xFA');                 # Diagnosis: source address: Typically the lowest 8 byte of canRxID [0xFA]
my @diagTargetAddr = ( '0xCB', '0xCB', '0xCB');                 # Diagnosis: target address: Typically the lowest 8 byte of canTxID [0xCB]
my @diagUseServiceByLocalId = ( 'false', 'false', 'false');     # Diagnosis: use service by local ID (deprecated: only supported by KWP2000)
my @diagT1Identifier = ( 0, 0, 0 );                             # Diagnosis: T1 identifier 
my @diagLocalIdentifier = ( 0, 0, 0 );                          # Diagnosis: local identifier (deprecated: only supported by KWP2000)
my @diagRxDataSize = ( 8, 8, 8 );                               # Diagnosis: max. RX data size of one Frame (using ReadByIdentifier service)
my @diagMinTxDataSize = ( 8, 8, 8 );                            # Diagnosis: min. TX data size of one Frame (using WriteByIdentifier service)
my @diagTxDataSize = ( 8, 8, 8 );                               # Diagnosis: max. TX data size of one Frame (using WriteByIdentifier service)
my @useSameRxTxChannel = ( 'true', 'true', 'true');             # system uses the same channel for RX and TX [true/false]

#system-related configuration parameters:
#strictly required:
my @sid = qw();                                     # system ID. For Multicore systems the SID needs to be assigned linearily without gaps for each consecutive core!
my @systemType = qw();                              # addidtional info [OSEK/ErcosEK//gliwOS/PC Software/RTA OSEK/AUTOSAR OS/Unknown]
my @systemName = qw();                              # unique System Name. This name is displayed in the T1.base context menu of the GUI [any string]
my @systemComment = qw();                           # any comment. Just additional info [any string]
my @tickDurationNs = qw();                          # tick duration in ns of system-specific timer
my @osBasicSchedFrameName = qw();                   # OS-name of task used as Basic Scheduling Frame event. The BSF event determines the boundaries for CPU-load calculation. Alternatively use osBasicSchedFrameId if only the ID is known
my @osBasicSchedFrameId = qw();                     # T1 task ID of Basic Scheduling Frame Event
my @t1HandlerPeriodMs = qw();                       # System-specific period of T1_Handler [ms]. It is recommended to call T1_Handler every 5 to 10ms
my @t1ScopeOverheadNs = qw();                       # Duration of one call to T1_TraceEvent [ns]
my @t1FlexOverheadNs = qw();                        # T1.flex overhead [ns]
my @analysisCapacity = qw();                        # defines macro T1_CONT_ANALYSIS_CAPACITY_COREx and also attribute in t1p: T1.cont analysis capacity

#parameters that use default value if omitted:
my @traceTimerIsMainTimer = ( "true", "true", "true");                                      # when using different timers in Multicore systems one timer needs to be declared the main timer. If teh current systems used this timer assign true [true/false]
my @cpuLoadCallback = ( "T1_CPULoadCallback", "T1_CPULoadCallback", "T1_CPULoadCallback" ); # system-specific callback being executed if system-specific CPU-load threshold is exceeded
my @osBasicSchedFrameEventId = ( "T1_ACTIVATION", "T1_ACTIVATION", "T1_ACTIVATION" );       # system-specific Event ID used for BSF [T1_START/T1_ACTIVATION/T1_USEREVENT]. Use -osBasicSchedFrameId for specifying ID of UserEvent. Caution: The event field must be 0 on the target!
my @osBackgroundTaskName = ("", "", "");                                                    # system-specific OS-name of Background task. If any name is stated this task is excluded from T1.cont calculations. If nothing is stated T1_INVALID_TASK_ID is used instead and thus considering the BG-task
my @osBackgroundTaskId = ( 1000, 1000, 1000);                                               # alternatively if only task-ID is known
my @nofAdditionalCat1Isrs = ( 0, 0, 0);                                                     # number of additional ISRs that are not covered by OS-specific module
my @additionalCat1IsrIdOffset = (0, 0, 0);                                                  # if the external cat1 ISRs are starting at a fixed offset configure offset for each system
my @targetExcludeFromTraceByName = qw();                                                    # defines macro $configHeader
my @targetExcludeFromTraceById = qw();                                                      # defines macro $configHeader
my @flexAnalysisCapacity = ( 0, 0, 0);                                                      # T1.flex analysis capacity: Max. number of exception hanlder calls within T1_Handler period before measurement will be disabled

#optional config parameters used for macros in T1_config.h:
my @cpuLoadThreshold = qw();                        # defines macro T1_CPULOAD_THRESHOLD_PERCENT_COREx: CPU-load threshold [0..99]
my @traceBufferEntries = qw();                      # defines macro T1_TRACEBUFFER_ENTRIES_COREx: Number of trace buffer entries
my @numberOfUserStpws = qw();                       # defines macro T1_NOF_USER_STPWS_COREx: Number of user stopwatches
my @numberOfConstraints = qw();                     # defines macro T1_NOF_CSRNS_COREx: Number of constraints
my @nofDelays = qw();                               # defines macro T1_NOF_DELAYS_COREx: Number of delays
my @nofFlexStopwatches = ( 0, 0, 0);                # defines macro T1_NOF_FLEX_STPWS_COREx: Number of T1.flex stopwatches (e.g. used for feature "linked Stopwatches") [0..255]
my @nofFlexAddrs = ( 0, 0, 0);                      # defines macro T1_NOF_FLEX_ADDRS_COREx: Number of T1.flex addresses. Needs to be greater or equal $nofFlexStopwatches [0..255]
my @pTimer = qw();                                  # defines macro T1_PTIMER_COREx: If using memory mapped timer: address of timer. Otherwise omit
my @traceTimerDownCounting = qw();                  # defines macro T1_TRACE_TIMER_COUNTS_DOWN_COREx: Trace timer is counting down [true/false]
my @Is32BitCpuWithSmallerTimer = qw();              # defines macro T1_32BIT_CPU_SMALLER_TIMER_COREx: Using 32-bit CPU with smaller timer [true/false]
my @cpuLoadTxPeriod = qw();                         # defines macro T1_CPU_LOAD_TX_PERIOD_COREx: Transmit CPU load every x CPU load frames (BSF-frame). E.g. BasicSchedFrame-Event has a period of 100ms. If $cpuLoadTxPeriod is 10 the CPU-load is transmitted every second
my @cpuLoadAvgSamples = qw();                       # defines macro T1_CPU_LOAD_SAMPLES_COREx: Number of samples taken within period [1 or $cpuLoadTxPeriod]

######################################################################################
# global variables
######################################################################################

my @sysElems = qw();
my $t1ConfigHDefs = "";
my $t1BidHDefs = "";
my $t1idHDefs  = "";
my $t1runnableIds = "";
my $t1ConfigHIds = "";
my $t1IsrWrapper = "";
my $t1p = "";
my $includeHeader = "";

my $buildId = "123456";

my @includeDirs = ();

my @numberOfTasks = ( 0, 0, 0);
my @cat1IsrIdOffset = ( 1000, 1000, 1000);  # just any high initial value
my @cat2IsrIdOffset = ( 1000, 1000, 1000);  # just any high initial value
my @externalIsrIdOffset = ( 1000, 1000, 1000);  # just any high initial value
my @highestIsrIdCat1 = (0, 0, 0);
my @highestIsrIdCat2 = (0, 0, 0);

my $externDataAvailable = 0;
my $externData = "";

my $systemNo = 0 ;

my $debug = 0;

my $userCfgFile = "";
my $cfgFile= "";
my $osCfgFile = "";



######################################################################################
# sub ParseParam
######################################################################################
sub ParseParam($)
{

    my $curLine = $_[0];
    $curLine =~ s/^\s//;


    if ((my $no) = $curLine =~ /#system\s+(\d)/)
    {
        $systemNo = $no;
    }
    if ( $curLine =~ /^-/)
    {
        my $validParamFound = 0;
        my @substr = split(/;/, $curLine); # ';' funtions as a comment operator
        my $curAssignm = $substr[0];
        @substr = split(/=/, $curAssignm);
        my $curParam = $substr[0];
        $curParam =~ s/^-|^\s+|\s+$//;
        my $curVal = $substr[1];
        $curVal =~ s/\s+$|^\s+//;

        if( $debug )
        {
            print $curParam.'='.$curVal."\n";
        }

        if ( $curParam =~ /projectFile/)              { $projectFile                  = rel2abs($curVal);    $validParamFound = 1; }
        if ( $curParam =~ /configHeader$/)            { $configHeader                 = rel2abs($curVal);    $validParamFound = 1; }
        if ( $curParam =~ /runnableHeader$/)          { $runnableHeader               = rel2abs($curVal);    $validParamFound = 1; }
        if ( $curParam =~ /^idHeader/)                { $idHeader                     = rel2abs($curVal);    $validParamFound = 1; }
        if ( $curParam =~ /bidHeader/)                { $bidHeader                    = rel2abs($curVal);    $validParamFound = 1; }
        if ( $curParam =~ /inlineHeader/)             { push (@inlineHeaders,                   $curVal);    $validParamFound = 1; }
        if ( $curParam =~ /includeHeader/)            { push (@includeHeaders,                  $curVal);    $validParamFound = 1; }
        if ( $curParam =~ /symbolFile/)               { $symbolFile                           = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /t1pSymbolIncludeFile/)     { push (@t1pSymbolIncludeFiles,           $curVal);    $validParamFound = 1; }

        if ( $curParam =~ /configHeaderInclude/)      { push (@configHeaderIncludes,            $curVal);    $validParamFound = 1; }
        if ( $curParam =~ /idHeaderInclude/)          { push (@idHeaderIncludes,                $curVal);    $validParamFound = 1; }
        if ( $curParam =~ /runnableHeaderInclude/)    { push (@runnableHeaderIncludes,          $curVal);    $validParamFound = 1; }
        if ( $curParam =~ /copyIncludeHeader/)        { $copyIncludeHeader                    = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /copySymbolFile/)           { $copySymbolFile                       = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /generateBuildId/)          { $generateBuildId                      = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /projectName/)              { $projectName                          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /readPreviousT1p/)          { $readPreviousT1p                      = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /storeTimingInformation/)   { $storeTimingInformation               = $curVal;     $validParamFound = 1; }

        if ( $curParam =~ /usingMulticoreLibs/)       { $usingMulticoreLibs                   = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /initFeatureMask/)          { $initFeatureMask                      = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /mainTickDuration/)         { $mainTickDuration                     = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /syncTimeBitLength/)        { $syncTimeBitLength                    = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /bigEndian/)                { $bigEndian                            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /cortexM/)                  { $cortexM                              = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /timeoutRx/)                { $timeoutRx                            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /timeoutTx/)                { $timeoutTx                            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /timeoutResponse/)          { $timeoutResponse                      = $curVal;     $validParamFound = 1; }

        if ( $curParam =~ /canHardware/)              { $canHardware                          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /txCycle/)                  { $txCycle                              = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /canBitrate/)               { $canBitrate                           = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /canUseFixedBlockSize/)     { $canUseFixedBlockSize                 = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /useSameConnectionForAllSystems/) { $useSameConnectionForAllSystems = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /targetExcludeFromTraceByName/) { push (@targetExcludeFromTraceByName,$curVal);    $validParamFound = 1; }
        if ( $curParam =~ /targetExcludeFromTraceById/)   { push (@targetExcludeFromTraceById,  $curVal);    $validParamFound = 1; }

        if ( $curParam =~ /connectionType/)           { $connectionType[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /canRxID/)                  { $canRxID[$systemNo]                   = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /canTxID/)                  { $canTxID[$systemNo]                   = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /canExtendedIds/)           { $canExtendedIds[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagAddressingMode/)       { $diagAddressingMode[$systemNo]        = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagSourceAddr/)           { $diagSourceAddr[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagTargetAddr/)           { $diagTargetAddr[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagUseServiceByLocalId/)  { $diagUseServiceByLocalId[$systemNo]   = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagT1Identifier/)         { $diagT1Identifier[$systemNo]          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagLocalIdentifier/)      { $diagLocalIdentifier[$systemNo]       = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagRxDataSize/)           { $diagRxDataSize[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagTxDataSize/)           { $diagTxDataSize[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /diagMinTxDataSize/)        { $diagMinTxDataSize[$systemNo]         = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /useSameRxTxChannel/)       { $useSameRxTxChannel[$systemNo]        = $curVal;     $validParamFound = 1; }

        if ( $curParam =~ /sid/)                      { $sid[$systemNo]                       = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /systemName/)               { $systemName[$systemNo]                = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /systemComment/)            { $systemComment[$systemNo]             = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /osBackgroundTaskName/)     { $osBackgroundTaskName[$systemNo]      = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /osBackgroundTaskId/)       { $osBackgroundTaskId[$systemNo]        = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /osBasicSchedFrameName/)    { $osBasicSchedFrameName[$systemNo]     = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /osBasicSchedFrameId/)      { $osBasicSchedFrameId[$systemNo]       = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /osBasicSchedFrameEventId/) { $osBasicSchedFrameEventId[$systemNo]  = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /nofAdditionalCat1Isrs/)    { $nofAdditionalCat1Isrs[$systemNo]     = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /additionalCat1IsrIdOffset/){ $additionalCat1IsrIdOffset[$systemNo] = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /t1HandlerPeriodMs/)        { $t1HandlerPeriodMs[$systemNo]         = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /traceBufferEntries/)       { $traceBufferEntries[$systemNo]        = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /cpuLoadThreshold/)         { $cpuLoadThreshold[$systemNo]          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /cpuLoadCallback/)          { $cpuLoadCallback[$systemNo]           = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /numberOfUserStpws/)        { $numberOfUserStpws[$systemNo]         = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /numberOfConstraints/)      { $numberOfConstraints[$systemNo]       = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /analysisCapacity/)         { $analysisCapacity[$systemNo]          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /flexAnalysisCapacity/)     { $flexAnalysisCapacity[$systemNo]      = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /nofDelays/)                { $nofDelays[$systemNo]                 = $curVal;     $validParamFound = 1; }

        if ( $curParam =~ /systemType/)               { $systemType[$systemNo]                = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /tickDurationNs/)           { $tickDurationNs[$systemNo]            = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /traceTimerIsMainTimer/)    { $traceTimerIsMainTimer[$systemNo]     = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /t1ScopeOverheadNs/)        { $t1ScopeOverheadNs[$systemNo]         = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /t1FlexOverheadNs/)         { $t1FlexOverheadNs[$systemNo]          = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /nofFlexAddrs/)             { $nofFlexAddrs[$systemNo]              = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /nofFlexStopwatches/)       { $nofFlexStopwatches[$systemNo]        = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /pTimer/)                   { $pTimer[$systemNo]                    = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /traceTimerDownCounting/)   { $traceTimerDownCounting[$systemNo]    = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /32BitCpuWithSmallerTimer/) { $Is32BitCpuWithSmallerTimer[$systemNo]= $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /cpuLoadTxPeriod/)          { $cpuLoadTxPeriod[$systemNo]           = $curVal;     $validParamFound = 1; }
        if ( $curParam =~ /cpuLoadAvgSamples/)        { $cpuLoadAvgSamples[$systemNo]         = $curVal;     $validParamFound = 1; }

        if ( not $validParamFound )
        {
            die "error: invalid parameter $curParam found in invocation file $_[1]";
        }
    }
}

######################################################################################
# sub resolvePathRelToProjectFile
######################################################################################

sub resolvePathRelToProjectFile($$$)
{
    my $filePath = shift;
    my $prjFilePath = shift;
    my $copyFile = shift;
    my $relativeFilePath = "";
    my $fileBaseName = "";
    
    $fileBaseName = File::Basename::basename($filePath);
    $fileBaseName =~ s/\s//g;

    if($copyFile eq "true")
    {
        # remove the path of the file to be copied
        

        # Build up the path for the copied include file
        my $copiedFilePathName = File::Spec::Functions::catfile($prjFilePath, $fileBaseName);
        $copiedFilePathName =~ s/\s//g;
        # Copy the filePath to the same location as the projectFile
        copy($filePath, $copiedFilePathName) or die "copy(): $!\nsource file: $filePath\ntarget file: $copiedFilePathName\n";

        $relativeFilePath =~ s/\s//g;
        $relativeFilePath = $fileBaseName;
        
        return $relativeFilePath;
    }

    $relativeFilePath = abs2rel($filePath,$prjFilePath);
    $relativeFilePath =~ s/^.://; #workaround for abs2rel bug: Remove drive
    $relativeFilePath =~ s/\s//g;

    return $relativeFilePath;
}

######################################################################################
# sub diffFiles
######################################################################################

sub diffFiles($$)
{
    my $filesDiffer = 0;
    open FILE_0, $_[0] or die "Unable to read \"$_[0]\"";
    open FILE_1, $_[1] or die "Unable to read \"$_[1]\"";
    my @file0 = <FILE_0>;
    my @file1 = <FILE_1>;
    close (FILE_0);
    close (FILE_1);

    if( scalar @file0 != scalar @file1)
    {
        $filesDiffer = 1;
    }
    else # both files have identical length
    {
        for my $lineNo (0 .. ( (scalar @file1)-1))
        {
            if( $file0[$lineNo] ne $file1[$lineNo] )
            {
                $filesDiffer = 1;
            }
        }
    }
    return $filesDiffer;
}

######################################################################################
# sub createPath
######################################################################################

sub createPath($)
{
    my $path=shift;
    my $fileName = File::Basename::basename($path);

    my $dirname;
    if( $fileName =~ /\./) {
        $dirname = File::Basename::dirname($path);
    } else {
        $dirname = $path;
    }
    $dirname =~ s|\\|/|g; # exchange '\' by '/'

    if (($dirname =~ m/\w/) and (!-d $dirname)) {
        return(1 == mkdir($dirname)); # return 1 if mkdir returned 1, otherwise return 0
    } else {
        return 1; # directory already exists or is empty -> nothing to be created
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
# Parse command line and get invocation file paths
######################################################################################

while( my $arg = shift )
{
    my $val = "";

    if (($val) = $arg =~ /-UserCfg=(.*)/)
    {
        open (INVOKATION_FILE, "$val") or die "error: could not locate user invokation file '$val.'";
        my $currentLine;
        while ($currentLine = <INVOKATION_FILE>)
        {
            &ParseParam($currentLine, $val);
        }
        $systemNo = 0;
        close (INVOKATION_FILE);
    }
    elsif (($val) = $arg =~ /-OsCfg=(.*)/)
    {
        $osCfgFile = $val;
    }
    elsif (($val) = $arg =~ /-Cfg=(.*)/)
    {
        open (INVOKATION_FILE, "$val") or die "error: could not locate config invokation file '$val.'";
        my $currentLine;
        while ($currentLine = <INVOKATION_FILE>)
        {
            &ParseParam($currentLine, $val);
        }
        $systemNo = 0;
        close (INVOKATION_FILE);
    }
    elsif( $arg eq "-I" )
    {
        if( $arg = shift and -d $arg )
        {
            push @includeDirs, (rel2abs($arg));
        }
    }
    elsif( $arg =~ /^-I(.*)$/ )
    {
        if( -d $1 )
        {
            push @includeDirs, (rel2abs($1));
        }
    }
    elsif (($val) = $arg =~ /-OsPm=(.*)/)  # use appropriate OS-module
    {
        if( $val  =~ /T1_Microsar/)
        {
            require T1_Microsar;
            import T1_Microsar;
        }
        elsif( $val =~ /T1_ProOsek/)
        {
            require T1_ProOsek;
            import T1_ProOsek;
        }
        elsif( $val =~ /T1_Tresos/)
        {
            require T1_Tresos;
            import T1_Tresos;
        }
        elsif( $val =~ /T1_SafeOs/)
        {
            require T1_SafeOs;
            import T1_SafeOs;
        }
        elsif( $val =~ /T1_RtaOs/)
        {
            require T1_RtaOs;
            import T1_RtaOs;
        }
        elsif( $val =~ /T1_gliwOS/)
        {
            require T1_gliwOS;
            import T1_gliwOS;
        }
        elsif( $val =~ /T1_dummyOS/)
        {
            require T1_dummyOS;
            import T1_dummyOS;
        }
        else
        {
            if( $val eq "")
            {
                die "no OS-specific Perl-module on command line specified! Eg: -OsPm=T1_Microsar\n"
            }
            else
            {
                die "incorrect OS-specific Perl-module via -OsPm specified on command line!\n"
            }
        }
    }
}

######################################################################################
# Process header files to be included / inlined
######################################################################################

foreach my $inlineHeader (@inlineHeaders)
{
    my $absPath = rel2abs($inlineHeader);

    open (INLINE_HEADER, "$absPath") or die "error: could not open file '$absPath' for input";

    $externDataAvailable = 1;

    while (my $currentLine = <INLINE_HEADER>)
    {
        chomp $currentLine;
        $currentLine=~ s/ö/oe/g;
        $currentLine=~ s/ü/ue/g;
        $currentLine=~ s/ä/ae/g;
        $currentLine=~ s/Ö/Oe/g;
        $currentLine=~ s/Ü/Ue/g;
        $currentLine=~ s/Ä/Ae/g;

        $externData .= $currentLine."\n";
    }
    close (INLINE_HEADER);
}

my $prjFilePath = File::Basename::dirname($projectFile);
$prjFilePath =~ s/\s//g;

foreach my $incFile (@includeHeaders)
{
    my $absPath = rel2abs($incFile);
    my $relPath = resolvePathRelToProjectFile($absPath, $prjFilePath, $copyIncludeHeader);
    $includeHeader  .= "      <HeaderInclude>$relPath</HeaderInclude>\n";
}

######################################################################################
# Read OS configuration, process Tasks, ISRs and Runnables
######################################################################################

OsReadOsConfiguration($osCfgFile, @includeDirs);

my $taskRef     = OsGetSysElementReference('Task');
my $isrRef      = OsGetSysElementReference('Interrupt');
my $runnableRef = OsGetSysElementReference('Runnable');
my $symGroupRef = OsGetSysElementReference('SymbolGroup');
my $osRef       = OsGetSysElementReference('OS');

# get general OS configurations
my $genSource = OsGetValue( $osRef, 'Info',  'GenSource' );
my $genDate = OsGetValue( $osRef, 'Info',  'GenDate' );
my $nofCores = OsGetValue( $osRef, 'Info',  'NofCores' );
my @isCoreUnused = ( 0, 0, 0 );
if( OsGetValue( $osRef, 'Info',  'UnusedCoreLookupTable' ) )    # get OS-coreID to phyisical CoreID mapping. -1 indicated that a core is unused.
{
    my $ref = OsGetValue( $osRef, 'Info',  'UnusedCoreLookupTable' );
    @isCoreUnused = @$ref;
}
if($taskRef ne 0)
{
    foreach my $task (sort { ${$taskRef}{$a}{"ID"} <=> ${$taskRef}{$b}{"ID"} } keys %{$taskRef})
    {
        my $taskPrio    = OsGetValue( $taskRef, $task,  'Priority' );
        my $taskName    = OsGetValue( $taskRef, $task,  'Name' );
        my $taskSymName = OsGetValue( $taskRef, $task,  'SymbolName' );
        my $taskId      = OsGetValue( $taskRef, $task,  'ID' );
        my $taskPeriod  = OsGetValue( $taskRef, $task,  'Period' );
        my $taskOffset  = OsGetValue( $taskRef, $task,  'Offset' );
        my $taskCore    = OsGetValue( $taskRef, $task,  'Core' );
        my $taskMaxAct  = OsGetValue( $taskRef, $task,  'MaxActivations' );
        my $taskComment = OsGetValue( $taskRef, $task,  'Comment' );
        my $taskType    = OsGetValue( $taskRef, $task,  'Type' );

        my $taskDesc = $taskName;
        my $exclFromCpuLoadStr = "";
        if( $taskComment ne "" )
        {
            $taskDesc .= ": $taskComment";
            $taskComment = "/* $taskComment */";
        }
        if( $taskCore eq "all")
        {
            for my $system (0 .. ($nofCores-1))
            {
                if( $osBackgroundTaskName[$system] eq $taskName)
                {
                    $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
                }
                if($taskId > $numberOfTasks[$system]) # find highest scope ID of all tasks from OS-specific Perl-module
                {
                   $numberOfTasks[$system] = $taskId;
                }
                $sysElems[$system] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"$taskSymName\"/>\n";
            }
        }
        else
        {
            if( $osBackgroundTaskName[$taskCore] eq $taskName)
            {
                $exclFromCpuLoadStr= " ExcludeFromCpuLoad=\"true\"";
            }
            if($taskId > $numberOfTasks[$taskCore]) # find highest scope ID of all tasks from OS-specific Perl-module
            {
               $numberOfTasks[$taskCore] = $taskId;
            }
            $sysElems[$taskCore] .= "      <SystemElement Name=\"$taskDesc\" Priority=\"$taskPrio\" ID=\"$taskId\" Type=\"$taskType\" MaxActivations=\"$taskMaxAct\"$exclFromCpuLoadStr SymbolRef=\"$taskSymName\"/>\n";
        }
        $t1ConfigHIds .= sprintf "#define %-45s(%2uu)%s\n", "T1_${taskName}_ID", $taskId, $taskComment;
    }
}

# Get application ISRs
if($isrRef ne 0)
{
    foreach my $isr (sort { ${$isrRef}{$a}{"ID"} <=> ${$isrRef}{$b}{"ID"} } keys %{$isrRef})
    {
        my $start;
        my $stop;
        my $isrPrio    = OsGetValue( $isrRef, $isr,  'Priority' );
        my $isrName    = OsGetValue( $isrRef, $isr,  'Name' );
        my $isrSymName = OsGetValue( $isrRef, $isr,  'SymbolName' );
        my $isrId      = OsGetValue( $isrRef, $isr,  'ID' );
        my $isrCore    = OsGetValue( $isrRef, $isr,  'Core' );
        my $isrComment = OsGetValue( $isrRef, $isr,  'Comment' );
        my $isrCategory= OsGetValue( $isrRef, $isr,  'Category' );
        my $isrType    = OsGetValue( $isrRef, $isr,  'Type' );
        my $irsContext = OsGetValue( $isrRef, $isr,  'Context' );
        my $isrDesc    = $isrName;

        if( $isrComment ne "" )
        {
            $isrDesc .= ": $isrComment";
            $isrComment = "/* $isrComment */";
        }

        if( $isrCore eq "all")  # ISR is to be assigned to all systems
        {
            $start = 0;
            $stop = $nofCores-1;
        }
        else    # ISR is to be assigned to a specific system
        {
            $start = $isrCore;
            $stop = $isrCore;
        }

        # now get the task ID offsets (required for some OS trace interfaces
        # the script requires to have the scope IDs arranged in following order (starting from 0):
        #   - tasks from OS-specific Perl-module
        #   - CAT2 ISRs from OS-specific Perl-module
        #   - CAT1 ISRs from OS-specific Perl-module
        #   - external CAT1 ISRs (not from OS-specific Perl-module)

        for my $system ($start .. $stop)
        {
            if($isrId > $numberOfTasks[$system]) # find highest scope ID of all tasks from OS-specific Perl-module
            {
               $numberOfTasks[$system] = $isrId;
            }
            if($isrId < $cat1IsrIdOffset[$system] && $isrCategory == 1) # find lowest cat1 ISR ID from OS-specific Perl-module
            {
               $cat1IsrIdOffset[$system] = $isrId;
            }
            if($isrId < $cat2IsrIdOffset[$system] && $isrCategory == 2) # find lowest cat2 ISR ID from OS-specific Perl-module
            {
               $cat2IsrIdOffset[$system] = $isrId;
            }
            if($isrId < $externalIsrIdOffset[$system] && $irsContext eq "External") # find lowest external ISR ID from OS-specific Perl-module
            {
                $externalIsrIdOffset[$system] = $isrId;
            }
            if($isrId > $highestIsrIdCat2[$system] && $isrCategory == 2) # find highest cat2 ISR ID from OS-specific Perl-module
            {
               $highestIsrIdCat2[$system] = $isrId;
            }
            if($isrId > $highestIsrIdCat1[$system] && $isrCategory == 1) # find highest cat1 ISR ID from OS-specific Perl-module
            {
                $highestIsrIdCat1[$system] = $isrId;
            }
            $sysElems[$system] .= "      <SystemElement Name=\"$isrDesc\" Priority=\"$isrPrio\" ID=\"$isrId\" Type=\"$isrType\" SymbolRef=\"$isrSymName\" />\n";
        }

        $t1ConfigHIds .= sprintf "#define %-45s(%2uu)\n", "T1_${isrName}_ID", $isrId, $isrComment;
    }
}

# verify and modify task and ISR IDs and get the overall number of tasks (required by T1.cont)
for my $system (0 .. ($nofCores-1))
{
    my $coreSuffix ="";
    my $cat1IsrsAvailable = 1;

    my $nofTasksFromOsModule = $numberOfTasks[$system] + 1;  # add one as the number represents the highest ID so far
    my $nofTasksWithExternalTasks;

    if( $additionalCat1IsrIdOffset[$system]) # external ISRs do have a fixed offset. Just add the number of external ISRs in order to get the overall numbr of tasks
    {
        $nofTasksWithExternalTasks = $additionalCat1IsrIdOffset[$system] + $nofAdditionalCat1Isrs[$system];
    }
    else # IDs are assigned in order with scope IDs from OS-specific module
    {
        $nofTasksWithExternalTasks = $numberOfTasks[$system] + 1 + $nofAdditionalCat1Isrs[$system];
    }

    $coreSuffix ="_CORE".$system;

    if( $highestIsrIdCat2[$system] == 0 )  # no cat2 ISR received from OS specific module
    {
        $highestIsrIdCat2[$system] = $nofTasksFromOsModule - 1;  # set number of tasks -1 instead
    }
    if( $cat2IsrIdOffset[$system] == 1000) # if initial value -> no cat2 ISRs received from OS-specific module
    {
        $cat2IsrIdOffset[$system] = $nofTasksFromOsModule;  # set number of tasks instead
    }
    if( $cat1IsrIdOffset[$system] == 1000) # if initial value -> no cat1 ISRs received from OS-specific module
    {
        $cat1IsrIdOffset[$system] = $highestIsrIdCat2[$system] + 1;  # set highest cat2 level instead
    }
    if( $highestIsrIdCat1[$system] == 0) # if initial value -> no cat1 ISRs received from OS-specific module
    {
        $cat1IsrsAvailable = 0;
        $highestIsrIdCat1[$system] = $cat1IsrIdOffset[$system];  # set highestIsrIdCat2 instead
    }
    if( $additionalCat1IsrIdOffset[$system]) # external CAT1 ISRs are at fixed offset in this system
    {
        $externalIsrIdOffset[$system] = $additionalCat1IsrIdOffset[$system];  # set fixed offset
    }
    elsif( $externalIsrIdOffset[$system] == 1000) # if initial value -> no addidtional ISRs configured via -externalIsrIdOffset
    {
        $externalIsrIdOffset[$system] = $highestIsrIdCat1[$system] + $cat1IsrsAvailable;
    }

    if( $isCoreUnused[$system] ne "1")
    {
        $numberOfTasks[$system] = $nofTasksWithExternalTasks;
    }
    else # this core is unused. Reduce TraceBuffer entry allocation to minimum
    {
        $numberOfTasks[$system] = 1;
        $cat1IsrIdOffset[$system] = 0;
        $cat2IsrIdOffset[$system] = 0;
        $externalIsrIdOffset[$system] = 0;
    }

    $t1ConfigHIds  .= "/* Core $system: */\n";
    $t1ConfigHIds  .= sprintf "#define %-45s(%2uu)\n", "T1_NOF_TASKS".$coreSuffix, $numberOfTasks[$system];
    $t1ConfigHIds  .= sprintf "#define %-45s(%2uu)\n", "T1_CAT1_ISR_ID_OFFSET".$coreSuffix, $cat1IsrIdOffset[$system];
    $t1ConfigHIds  .= sprintf "#define %-45s(%2uu)\n", "T1_CAT2_ISR_ID_OFFSET".$coreSuffix, $cat2IsrIdOffset[$system];
    $t1ConfigHIds  .= sprintf "#define %-45s(%2uu)\n", "T1_EXT_ISR_ID_OFFSET".$coreSuffix, $externalIsrIdOffset[$system];
    $t1ConfigHIds  .= sprintf "#define %-45s(%s)\n", "T1_CAT1_TO_TRACE_ID".$coreSuffix."(id_)", "T1_CAT1_ISR_ID_OFFSET".$coreSuffix." + id_";
    $t1ConfigHIds  .= sprintf "#define %-45s(%s)\n", "T1_CAT2_TO_TRACE_ID".$coreSuffix."(id_)", "T1_CAT2_ISR_ID_OFFSET".$coreSuffix." + id_";
    $t1ConfigHIds  .= sprintf "#define %-45s(%s)\n", "T1_EXT_ISR_TO_TRACE_ID".$coreSuffix."(id_)", "T1_EXT_ISR_ID_OFFSET".$coreSuffix." + id_";
}


# Get application runnables
if($runnableRef ne 0)
{
    foreach my $runnable (sort { ${$runnableRef}{$a}{"ID"} <=> ${$runnableRef}{$b}{"ID"} } keys %{$runnableRef})
    {
        my $runnablePosInTask = OsGetValue( $runnableRef, $runnable,  'PosInTask' );
        my $runnableName      = OsGetValue( $runnableRef, $runnable,  'Name' );
        my $runnableSymName   = OsGetValue( $runnableRef, $runnable,  'SymbolName' );
        my $runnableId        = OsGetValue( $runnableRef, $runnable,  'ID' );
        my $runnableCore      = OsGetValue( $runnableRef, $runnable,  'Core' );
        my $runnableComment   = OsGetValue( $runnableRef, $runnable,  'Comment' );
        my $runnableType      = OsGetValue( $runnableRef, $runnable,  'Type' );
        my $runnableTaskRef   = OsGetValue( $runnableRef, $runnable,  'TaskRef' );

        my $runnableDesc = $runnableName;
        if( $runnableComment ne "" )
        {
            $runnableDesc .= ": $runnableComment";
            $runnableComment = "/* $runnableComment */";
        }
        if ($runnableHeader ne "") # optionally create header for redefintion of start/stop macros and add corresponding system elemts to t1p:
        {
            $sysElems[$runnableCore] .= "      <SystemElement Name=\"$runnableDesc\" ID=\"$runnableId\" Type=\"$runnableType\" />\n";
            $t1runnableIds .= sprintf "#define %-45s(%2uu)\n", "T1_${runnableName}_ID", $runnableId;
        }
    }
}

# append ISR wrapper macros from OS-Module
$t1IsrWrapper .= OsGetIsrWrapper();


#  Perform OS instrumentation
    OsPerformInstrumentation();




######################################################################################
# Routine for resolving Tasks names to Task IDs
######################################################################################
sub resolveTaskOrIsrName($)
{
    my $taskRef         = OsGetSysElementReference('Task');
    my $isrRef          = OsGetSysElementReference('Interrupt');
    my $toSeachFor      = $_[0];

    foreach my $task (keys %{$taskRef})
    {
        my $taskId      = OsGetValue( $taskRef, $task,  'ID' );
        my $taskName    = OsGetValue( $taskRef, $task,  'Name' );

        if( $taskName eq  $toSeachFor )
        {
            return $taskId;
        }
    }
    foreach my $isr (keys %{$isrRef})
    {
        my $isrId      = OsGetValue( $isrRef, $isr,  'ID' );
        my $isrName    = OsGetValue( $isrRef, $isr,  'Name' );

        if( $isrName eq  $toSeachFor )
        {
            return $isrId;
        }
    }

    return 0;
}

######################################################################################
# Routine for resolving Tasks names to Task IDs
######################################################################################
sub resolveTaskOrIsrId($)
{
    my $taskRef         = OsGetSysElementReference('Task');
    my $isrRef          = OsGetSysElementReference('Interrupt');
    my $toSeachFor      = $_[0];

    foreach my $task (keys %{$taskRef})
    {
        my $taskId      = OsGetValue( $taskRef, $task,  'ID' );
        my $taskName    = OsGetValue( $taskRef, $task,  'Name' );

        if( $taskId eq  $toSeachFor )
        {
            return $taskName;
        }
    }
    foreach my $isr (keys %{$isrRef})
    {
        my $isrId      = OsGetValue( $isrRef, $isr,  'ID' );
        my $isrName    = OsGetValue( $isrRef, $isr,  'Name' );

        if( $isrId eq  $toSeachFor )
        {
            return $isrName;
        }
    }

    return 0;
}


######################################################################################
# Create T1 project file
######################################################################################

my $t1pDoesNotExist = 0;
my @reportConfigFromPrevT1p = ( "", "", "" );;
my %symGroupsFromPrevT1p = qw();
my %tasksIsrsNameByIdFromPrevT1p = qw();
my %symGroupsFromOsModule = ();
my %evtChainsFromPrevT1p = qw();

if( $generateBuildId eq "true" )
{
    $buildId = int(rand(4294967295));
    if( $buildId > 4294967295)
    {
        print "error: Build ID out of uint32_t range\n";
    }
}

if(-e $projectFile && $readPreviousT1p eq "true") # check if project file exists and if user-configured parts shall be copied to new t1p
{
    # extract user-configurable information from previous t1p:
    my $sysIdx = -1;
    my $extractReportCfg = 0;
    my $extractSymGroup = 0;
    my $extractEvtChain = 0;
    my $curLine = "";
    my $curSymGroupName = "";
    my $curEvtChainName = "";

    open PREV_T1P, $projectFile or die "Unable to read \"$projectFile\"";
    while( $curLine = <PREV_T1P> )
    {
        if( $curLine =~ /\<System Name/ )
        {
            $sysIdx ++;
        }

        # extract report configuration:
        if( $curLine =~ /\<ReportConfiguration\>/ )
        {
            $extractReportCfg = 1;
        }
        if( $extractReportCfg )
        {
            $reportConfigFromPrevT1p[$sysIdx] .= $curLine;
        }
        if( $curLine =~ /\<\/ReportConfiguration\>/ )
        {
            $extractReportCfg = 0;
        }

        # extract Symbol Groups:
        if( $curLine =~ /\<SymbolGroup Name=\"(.*)\" IsCode/ )
        {
            $extractSymGroup = 1;
            $curSymGroupName = $1."_$sysIdx";
        }
        if( $extractSymGroup )
        {
            $symGroupsFromPrevT1p{$curSymGroupName} .= $curLine;
        }
        if( $curLine =~ /\<\/SymbolGroup\>/ )
        {
            $extractSymGroup = 0;
        }

        #extract Tasks and Interrupts and their IDs in order to check EventChains for consistency before adding EventChains to newly generated t1p:
        if( $curLine =~ /\<SystemElement Name=\"(.*)\" Priority=\"(.*)\" ID=\"(.*)\" Type/ )
        {
            $tasksIsrsNameByIdFromPrevT1p{$3} = $1;
        }

        # preserve Event Chains:
        if( $curLine =~ /\<EventChainSystemElement Name=\"(.*)\" ID=\"([0-9]+)\"/ )
        {
            $extractEvtChain = 1;
            $curEvtChainName = $1."_$sysIdx"; # append system ID in order to re-assign EventChains to systems
        }
        if( $extractEvtChain )
        {
            if( $curLine =~ /SystemElementID=\"([0-9]+)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
            {
                if( $2 eq "Task" || $2 eq "Interrupt")  # only Interrupts and Tasks can be verified
                {
                    #replace Task and Interrupt IDs by their names and add pattern for identification in t1p generation process:
                    my $replacedId = "\$\$\$".$tasksIsrsNameByIdFromPrevT1p{$1};
                    $curLine =~ s/ SystemElementID=\"([0-9]+)\"/ SystemElementID=\"$replacedId\"/;
                }
            }
            $evtChainsFromPrevT1p{$curEvtChainName} .= $curLine;
        }
        if( $curLine =~ /\<\/EventChainSystemElement\>/ )
        {
            $extractEvtChain = 0;
        }
    }
    close PREV_T1P;
}
else # project file does not exist
{
    $t1pDoesNotExist = 1;
}

#project specific part:
$t1p .="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
$t1p .="<T1 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" Version=\"2.0\">\n";

$t1p  .= "  <Project Name=\"$projectName\" ";
($t1p .= "MainTickDuration=\"$mainTickDuration\" ") if $mainTickDuration;
($t1p .= "SyncTimeBitLength=\"$syncTimeBitLength\" ") if$syncTimeBitLength;
$t1p  .= "T1targetVersion=\"2\">\n";
$t1p  .= "    <Comment> Project file \"$projectFile\" auto-generated from file \"$genSource\" on $genDate</Comment>\n";

#system specific part:

#process each system and create corresponding systems elements
for my $sysNo (0 .. ($nofCores-1))
{
    if( $isCoreUnused[$sysNo] ne 1)
    {
        my $measOvhdHalf = $t1ScopeOverheadNs[$sysNo] /2;
        my $storeTimInfoStr = "";
        my $flexAnaCapStr = "";
        my $traceTimerDownCountingStr = "";
        my $bsfSysElemType = "SystemElementType=\"Task\"";
        if( $storeTimingInformation eq "true" ) {$storeTimInfoStr = "StoreTimingInformation=\"true\"";}
        if( $flexAnalysisCapacity[$sysNo] ne 0 )   { $flexAnaCapStr = "T1flexAnalysisCapacity=\"$flexAnalysisCapacity[$sysNo]\"";}
        if($traceTimerDownCounting[$sysNo] eq "true") {$traceTimerDownCountingStr = "TimerCountsDown=\"true\"";}

        $t1p  .= "    <System Name=\"$systemName[$sysNo]\" TickDuration=\"$tickDurationNs[$sysNo]\" $traceTimerDownCountingStr MaxAbsTime=\"65535\" KernelPriority=\"255\" MinPreempPrio=\"1\" SystemType=\"$systemType[$sysNo]\" T1HandlerPeriod=\"$t1HandlerPeriodMs[$sysNo]\" $storeTimInfoStr SID=\"$sid[$sysNo]\" BID=\"$buildId\">\n";
        $t1p  .= "      <Comment>$systemComment[$sysNo]</Comment>\n";
        ($t1p .= "      <TargetSpecifics UseNcaAnalysis=\"true\" />\n") if($cortexM eq 'true');
        ($t1p .= "      <TargetSpecifics BigEndian=\"true\" />\n") if($bigEndian eq 'true');
        ($t1p .= "      <TargetAnalysis T1contAnalysisCapacity=\"$analysisCapacity[$sysNo]\" $flexAnaCapStr />\n") if($analysisCapacity[$sysNo] );
        ($t1p .= "      <TraceMergeAttributes TraceTimerIsMainTimer=\"$traceTimerIsMainTimer[$sysNo]\" />\n") if($traceTimerIsMainTimer[$sysNo] eq 'true');
        if($osBasicSchedFrameName[$sysNo]) # only for tasks
        {
            if( my $taskID = resolveTaskOrIsrName($osBasicSchedFrameName[$sysNo]) )
            {
                $osBasicSchedFrameId[$sysNo] = $taskID;
            }
            else
            {
                die "Could not resolve task name $osBasicSchedFrameName[$sysNo] !";
            }

            $t1p .= "      <BasicSchedulingFrameEvent Type=\"$osBasicSchedFrameEventId[$sysNo]\" SystemElementID=\"$osBasicSchedFrameId[$sysNo]\" $bsfSysElemType ID=\"4294967295\" />\n";
        }
        elsif($osBasicSchedFrameId[$sysNo])
        {
            if( $osBasicSchedFrameEventId[$sysNo] eq "T1_USEREVENT")
            {
                $bsfSysElemType = "SystemElementType=\"UserEvent\""; # not required for UserEvents
            }
            $t1p .= "      <BasicSchedulingFrameEvent Type=\"$osBasicSchedFrameEventId[$sysNo]\" SystemElementID=\"$osBasicSchedFrameId[$sysNo]\" $bsfSysElemType ID=\"4294967295\" />\n";
        }
        else
        {
            print "Warning: No Basic Scheduling Frame Name configured for System $sysNo !\n";
        }
        ($t1p .= $includeHeader) if $includeHeader;
        if($sysElems[$sysNo])
        {
            $t1p  .= $sysElems[$sysNo];
        }

        # check and append all valid Event Chains from previous t1p. Hint: Only Tasks and Interrupt IDs can be verified!
        foreach my $evtChainName (keys %evtChainsFromPrevT1p) # get Event Chains extracted from prevoius t1p one by one
        {
            my $evtChainSysNo    = substr($evtChainName,length($evtChainName)-1,1); # get system number of current Event Chain
            my $evtChainOrigName = substr($evtChainName,0,length($evtChainName)-2);

            if( $evtChainSysNo == $sysNo ) # is system number of Event Chain equal to current sysNo?
            {
                if( $evtChainsFromPrevT1p{$evtChainName} =~ /SystemElementID=\"(.*)\" SystemElementType=\"(.*)\" ID=\"([0-9]+)\"/ )
                {
                    my $discardEvtChain = 0;
                    my $newEvtChain = "";
                    my @evtChainEntry = split /\n+/, $evtChainsFromPrevT1p{$evtChainName}; # buffer current Event Chain in array
                    my $idx = 0;

                    foreach my $line (@evtChainEntry)
                    {
                        if( $line =~ /\"\$\$\$(.*)\" S(.*)/) # check for pattern indicating Task/Interrupt name from previous t1p
                        {
                            my $newTaskId = resolveTaskOrIsrName( $1); # try to resolve ID of Task/Interrupt by name
                            if( $newTaskId ) # check if Task/Interrupt name still exists
                            {
                                $line =~ s/\"\$\$\$(.*)\" S(.*)/\"$newTaskId\" S$2/ ; # replace pattern and Tas/Interrupt name by actual ID
                            }
                            else # Task/Interrupt name could not be resolved and thus does not exist any longer in the new configuration
                            {
                                $discardEvtChain = 1;
                                print "could not resolve Task name $1 from previous configuration. Event Chain $evtChainOrigName will be discarded!\n";
                            }
                        }
                        $newEvtChain .= $line."\n";
                        $idx ++;
                    }
                    if( $discardEvtChain == 0)
                    {
                        $t1p  .= $newEvtChain;
                    }
                }
            }
        }
        if($symbolFile ne "")
        {
            $symbolFile = getNewestFileMatchingWildcard($symbolFile);
        }
        my $relSymPath = resolvePathRelToProjectFile( rel2abs($symbolFile), $prjFilePath, $copySymbolFile);
        
        # symbol part:
        $t1p  .= "      <Symbols>\n";
        if($symbolFile ne "")
            {$t1p  .= "         <SymbolFilePath>$relSymPath</SymbolFilePath>\n";}
        else
            {$t1p  .= "         <SymbolFilePath>notSpecified.elf</SymbolFilePath>\n";}
        if(@t1pSymbolIncludeFiles)
        {
            foreach my $t1pSymbolIncludeFile (@t1pSymbolIncludeFiles)
            {
                my $t1pSymbolInclude = resolvePathRelToProjectFile( rel2abs($t1pSymbolIncludeFile), $prjFilePath, 'false');
                $t1p  .= "         <Include>$t1pSymbolInclude</Include>\n";
            }
        }

        # symbol groups from OS-module
        if($symGroupRef ne 0)
        {
            foreach my $symGroup (keys %{$symGroupRef})
            {
                my $symGroupName        = OsGetValue( $symGroupRef, $symGroup,  'Name' );
                my $symGroupIsCode      = OsGetValue( $symGroupRef, $symGroup,  'IsCode' );
                my $symGroupDuration    = OsGetValue( $symGroupRef, $symGroup,  'MeasureDuration' );
                my $symGroupIntervalCnt = OsGetValue( $symGroupRef, $symGroup,  'FocusIntervalCount' );
                my $symGroupTraceCount  = OsGetValue( $symGroupRef, $symGroup,  'TraceCount' );
                my $symGroupCore        = OsGetValue( $symGroupRef, $symGroup,  'Core' );
                my $symGroupElementRef  = OsGetValue( $symGroupRef, $symGroup,  'SymbolGroupElemRef');

                if( $symGroupCore eq "all" || $symGroupCore == $sysNo )
                {
                    my $catName = $symGroupName."_".$sysNo;
                    $symGroupsFromOsModule{ $catName } = $symGroupName;

                    $t1p .= "         <SymbolGroups Name=\"$symGroupName\" IsCode=\"$symGroupIsCode\" MeasureDuration=\"$symGroupDuration\" FocusIntervalCount=\"$symGroupIntervalCnt\" TraceCount=\"$symGroupTraceCount\">\n";
                    foreach my $symbol (@$symGroupElementRef)
                    {
                        $t1p .= "            <Symbol>$symbol</Symbol>\n";
                    }
                    $t1p .= "         </SymbolGroups>\n";

                }
            }
        }
        # then append all user-configured Symbol Groups:
        foreach my $userSymbGroupName (keys %symGroupsFromPrevT1p) # get all Symbol Groups from previous t1p
        {
            my $symGroupSysNo = substr($userSymbGroupName,length($userSymbGroupName)-1,1); # get system number of current Symbol Group

            if( $symGroupSysNo == $sysNo ) # is system number of user-defined Symbol Group equal current sysNo?
            {
                if (not exists $symGroupsFromOsModule{$userSymbGroupName} ) # check if Symbol Group has already been added by OS-module
                {
                    $t1p .= $symGroupsFromPrevT1p{$userSymbGroupName}; # add Symbol Group if not yet present
                }
            }
        }
        $t1p  .= "      </Symbols>\n";

        # measure overhead part
        $t1p  .= "      <MeasureOverheads Extended=\"true\">\n";
        $t1p  .= "         <MainMeasureOverhead>\n";
        $t1p  .= "            <T1>$measOvhdHalf</T1>\n";
        $t1p  .= "            <T2>$measOvhdHalf</T2>\n";
        $t1p  .= "         </MainMeasureOverhead>\n";
        $t1p  .= "         <T1flexMeasureOverhead>\n";
        $t1p  .= "            <T1>$t1FlexOverheadNs[$sysNo]</T1>\n";
        $t1p  .= "         </T1flexMeasureOverhead>\n";
        $t1p  .= "      </MeasureOverheads>\n";
        # Report configuration part:

        if( $t1pDoesNotExist ) # Check if t1p does already exist: Only add the report configuration the first time the t1p is generated! Otherwise retain the user-configured settings!
        {
            $t1p  .= "      <ReportConfiguration>\n";
            $t1p  .= "          <CsvConfig TimeBase=\"formatted\">\n";
            $t1p  .= "            <SelectedTimingInformation>\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "            </SelectedTimingInformation>\n";
            $t1p  .= "          </CsvConfig>\n";
            $t1p  .= "          <HtmlConfig>\n";
            $t1p  .= "            <SelectedTimingInformation>\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CpuLoad\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Max\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"CoreExecTime\" SubType=\"Average\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Min\" />\n";
            $t1p  .= "              <TimingInformation Type=\"DeltaTime\" SubType=\"Average\" />\n";
            $t1p  .= "            </SelectedTimingInformation>\n";
            $t1p  .= "          </HtmlConfig>\n";
            $t1p  .= "        </ReportConfiguration>\n";
        }
        else
        {
            $t1p  .= $reportConfigFromPrevT1p[$sysNo];
        }

        if($externDataAvailable)
        {
            $t1p  .= "    <ExternalData>\n";
            $t1p  .= "       <HeaderContent><![CDATA[\n";
            $t1p  .= $externData."\n";
            $t1p  .= "       ]]></HeaderContent>\n";
            $t1p  .= "     </ExternalData>\n";
        }

        my $conSysNo                    = 0; # if useSameConnectionForAllSystems is declared false in *.inv the settings at index 0 are used for all systems
        if( $useSameConnectionForAllSystems eq 'false' )
        {
            $conSysNo = $sysNo;
        }
        my $targetId                    = $sid[$sysNo] % 32;
        my $intCanRxId                  = hex($canRxID[$conSysNo]);
        my $intCanTxId                  = hex($canTxID[$conSysNo]);
        my $intDiagSourceAddr           = hex($diagSourceAddr[$conSysNo]);
        my $intDiagTargetAddr           = hex($diagTargetAddr[$conSysNo]);
        my $intDiagT1Identifier         = hex($diagT1Identifier[$conSysNo]);
        my $intDiagLocalIdentifier      = hex($diagLocalIdentifier[$conSysNo]);

        $t1p  .= "    <CommunicationConfig UseSameRxTxChannel=\"$useSameRxTxChannel[$conSysNo]\">\n";
        $t1p  .= "        <RxChannel>\n";
        $t1p  .= "          <LayerConfig>\n";
        $t1p  .= "            <Name>$connectionType[$conSysNo]</Name>\n";
        $t1p  .= "            <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
        $t1p  .= "              <AppId>0</AppId>\n";
        $t1p  .= "              <TargetId>$targetId</TargetId>\n";
        $t1p  .= "            </RoutingParameters>\n";
        if( $connectionType[$conSysNo] eq 'Diagnosis' )
        {
            $t1p  .= "            <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
            $t1p  .= "              <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
            $t1p  .= "              <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
            $t1p  .= "              <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
            $t1p  .= "              <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
            $t1p  .= "              <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
            $t1p  .= "              <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
            $t1p  .= "              <RxDataSize>$diagRxDataSize[$conSysNo]</RxDataSize>\n";
            $t1p  .= "              <TxDataSize>$diagTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "              <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
            $t1p  .= "            </RoutingParameters>\n";
        }
        $t1p  .= "            <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
        $t1p  .= "              <CanId>\n";
        $t1p  .= "                <Id>$intCanRxId</Id>\n";
        $t1p  .= "                <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
        $t1p  .= "              </CanId>\n";
        $t1p  .= "            </BusRoutingParameter>\n";
        $t1p  .= "          </LayerConfig>\n";
        $t1p  .= "          <BusRef>\n";
        $t1p  .= "            <Name>CAN1</Name>\n";
        $t1p  .= "            <BusType>CAN</BusType>\n";
        $t1p  .= "          </BusRef>\n";
        $t1p  .= "          <Direction>RX</Direction>\n";
        $t1p  .= "        </RxChannel>\n";

        $t1p  .= "        <TxChannel>\n";
        $t1p  .= "          <LayerConfig>\n";
        $t1p  .= "            <Name>$connectionType[$conSysNo]</Name>\n";
        $t1p  .= "            <RoutingParameters xmlns:q1=\"Gliwa-CommunicationConfig\" xsi:type=\"q1:GcpRoutingParameterType\">\n";
        $t1p  .= "              <AppId>0</AppId>\n";
        $t1p  .= "              <TargetId>$targetId</TargetId>\n";
        $t1p  .= "            </RoutingParameters>\n";
        if( $connectionType[$conSysNo] eq 'Diagnosis' )
        {
            $t1p  .= "            <RoutingParameters xmlns:q2=\"Gliwa-CommunicationConfig\" xsi:type=\"q2:DgnRoutingParameterType\">\n";
            $t1p  .= "              <AddressingMode>$diagAddressingMode[$conSysNo]</AddressingMode>\n";
            $t1p  .= "              <SouceAddress>$intDiagSourceAddr</SouceAddress>\n";
            $t1p  .= "              <TargetAddress>$intDiagTargetAddr</TargetAddress>\n";
            $t1p  .= "              <UseServicesByLocId>$diagUseServiceByLocalId[$conSysNo]</UseServicesByLocId>\n";
            $t1p  .= "              <T1Identifier>$intDiagT1Identifier</T1Identifier>\n";
            $t1p  .= "              <T1LocalIdentifier>$intDiagLocalIdentifier</T1LocalIdentifier>\n";
            $t1p  .= "              <RxDataSize>$diagRxDataSize[$conSysNo]</RxDataSize>\n";
            $t1p  .= "              <TxDataSize>$diagTxDataSize[$conSysNo]</TxDataSize>\n";
            $t1p  .= "              <minTxDataSize>$diagMinTxDataSize[$conSysNo]</minTxDataSize>\n";
            $t1p  .= "            </RoutingParameters>\n";
        }
        $t1p  .= "            <BusRoutingParameter xmlns:q3=\"Gliwa-CommunicationConfig\" xsi:type=\"q3:CanRoutingParameterType\">\n";
        $t1p  .= "              <CanId>\n";
        $t1p  .= "                <Id>$intCanTxId</Id>\n";
        $t1p  .= "                <isExtended>$canExtendedIds[$conSysNo]</isExtended>\n";
        $t1p  .= "              </CanId>\n";
        $t1p  .= "            </BusRoutingParameter>\n";
        $t1p  .= "          </LayerConfig>\n";
        $t1p  .= "          <BusRef>\n";
        $t1p  .= "            <Name>CAN1</Name>\n";
        $t1p  .= "            <BusType>CAN</BusType>\n";
        $t1p  .= "          </BusRef>\n";
        $t1p  .= "          <Direction>TX</Direction>\n";
        $t1p  .= "        </TxChannel>\n";
        $t1p  .= "      </CommunicationConfig>\n";

        $t1p  .= "    </System>\n";
    }
}
$t1p  .= "    <Buses FixedBlocksize=\"$canUseFixedBlockSize\">\n";
$t1p  .= "      <Name>CAN1</Name>\n";
$t1p  .= "      <Type>CAN</Type>\n";
if( $canHardware eq 'VECTOR' )
{
$t1p  .= "      <HwIdentifier>\n";
$t1p  .= "        <Name>CANcaseXL Channel 1</Name>\n";
$t1p  .= "        <HwType>VECTOR</HwType>\n";
$t1p  .= "      </HwIdentifier>\n";
$t1p  .= "      <TxCycleMs>$txCycle</TxCycleMs>\n";
$t1p  .= "      <BusConfig xmlns:q7=\"Gliwa-CommunicationConfig\" xsi:type=\"q7:CanBusConfigType\">\n";
    if( $canBitrate == 500000)
    {
    $t1p  .= "        <Bitrate>500000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>1</Brp>\n";
    $t1p  .= "          <Prop>5</Prop>\n";
    $t1p  .= "          <Phase1>10</Phase1>\n";
    $t1p  .= "          <Phase2>5</Phase2>\n";
    $t1p  .= "          <Sjw>4</Sjw>\n";
    $t1p  .= "          <Sam>1</Sam>\n";
    $t1p  .= "          </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 250000)
    {
    $t1p  .= "        <Bitrate>250000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>2</Brp>\n";
    $t1p  .= "          <Prop>0</Prop>\n";
    $t1p  .= "          <Phase1>10</Phase1>\n";
    $t1p  .= "          <Phase2>5</Phase2>\n";
    $t1p  .= "          <Sjw>4</Sjw>\n";
    $t1p  .= "          <Sam>1</Sam>\n";
    $t1p  .= "          </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 1000000)
    {
    $t1p  .= "        <Bitrate>1000000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>1</Brp>\n";
    $t1p  .= "          <Prop>5</Prop>\n";
    $t1p  .= "          <Phase1>4</Phase1>\n";
    $t1p  .= "          <Phase2>3</Phase2>\n";
    $t1p  .= "          <Sjw>4</Sjw>\n";
    $t1p  .= "          <Sam>1</Sam>\n";
    $t1p  .= "          </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in GUI!\n";
    }
}
else  # U2C
{
$t1p  .= "      <HwIdentifier>\n";
$t1p  .= "        <Name>U2C_</Name>\n";
$t1p  .= "        <HwType>U2C</HwType>\n";
$t1p  .= "      </HwIdentifier>\n";
$t1p  .= "      <TxCycleMs>$txCycle</TxCycleMs>\n";
$t1p  .= "      <BusConfig xmlns:q7=\"Gliwa-CommunicationConfig\" xsi:type=\"q7:CanBusConfigType\">\n";
if( $canBitrate == 500000)
    {
    $t1p  .= "        <Bitrate>500000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>1</Brp>\n";
    $t1p  .= "          <Prop>1</Prop>\n";
    $t1p  .= "          <Phase1>6</Phase1>\n";
    $t1p  .= "          <Phase2>4</Phase2>\n";
    $t1p  .= "          <Sjw>1</Sjw>\n";
    $t1p  .= "          <Sam>3</Sam>\n";
    $t1p  .= "          </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 250000)
    {
    $t1p  .= "        <Bitrate>250000</Bitrate>\n";
    $t1p  .= "        <BitTiming>\n";
    $t1p  .= "          <Brp>1</Brp>\n";
    $t1p  .= "          <Prop>7</Prop>\n";
    $t1p  .= "          <Phase1>8</Phase1>\n";
    $t1p  .= "          <Phase2>8</Phase2>\n";
    $t1p  .= "          <Sjw>1</Sjw>\n";
    $t1p  .= "          <Sam>3</Sam>\n";
    $t1p  .= "          </BitTiming>\n";
    $t1p  .= "      </BusConfig>\n";
    }
    elsif( $canBitrate == 1000000)
    {
        print "Bitrate not supported by U2C. Please contact Gliwa!\n";
    }
    else
    {
        print "Bitrate not supported by script. Please configure manually in GUI!\n";
    }
}

$t1p  .= "    </Buses>\n";
$t1p  .= "  </Project>\n";
$t1p  .= "</T1>\n";

if( createPath($projectFile) == 0 )
{
    die "Unable to create path for file $projectFile";
}
open T1P, ">$projectFile" or die "Unable to write to \"$projectFile\"";
print T1P $t1p;
close T1P;

######################################################################################
# Create T1_config.h
######################################################################################
if( ($usingMulticoreLibs eq 'true') || ($nofCores > 1) )
{
    $t1ConfigHDefs .= sprintf "#define %-45s%s\n", "T1_NOF_CORES",$nofCores;
}

$t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_SID", $sid[0];
if( $bidHeader eq "") # no BID-header specified. write BID into ConfigH
{
    $t1ConfigHDefs .= sprintf "#define %-45s%s\n", "T1_BUILD_ID", $buildId;
}
else
{
    $t1BidHDefs .= sprintf "#define %-45s%s\n", "T1_BUILD_ID", $buildId;
}

if( $useSameConnectionForAllSystems )
{
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CAN_PC_TO_ECU_ID", $canTxID[0];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CAN_ECU_TO_PC_ID", $canRxID[0];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MIN_RX_FRAME_SIZE", $diagMinTxDataSize[0];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE", $diagTxDataSize[0];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE", $diagRxDataSize[0];
}
($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TIMEOUT_RX", $timeoutRx)   if($timeoutRx ne "") ;
($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TIMEOUT_TX", $timeoutTx)   if($timeoutTx ne "") ;
($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TIMEOUT_RESPONSE", $timeoutResponse)   if($timeoutResponse ne "") ;
($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_INIT_FEATURE_MASK", $initFeatureMask)   if($initFeatureMask ne "") ;


for my $sysNo (0 .. ($nofCores-1))
{
    my $BgTask = "";
    my $coreSuffix ="";

    $coreSuffix ="_CORE".$sysNo;

    # perform some value checks:
    if($cpuLoadAvgSamples[$sysNo] && $cpuLoadAvgSamples[$sysNo])
    {
        if( ! ($cpuLoadTxPeriod[$sysNo] == 1 || $cpuLoadAvgSamples[$sysNo] == $cpuLoadTxPeriod[$sysNo] ) )
        {
            die "error: cpuLoadAvgSamples must either be 1 or equal to cpuLoadTxPeriod!";
        }
    }
    if($nofFlexStopwatches[$sysNo] > $nofFlexAddrs[$sysNo])
    {
        die "error: nofFlexAddrs must be >= nofFlexStopwatches!";
    }

    $t1ConfigHDefs .= "\n/* Core specific configuration: Core $sysNo*/\n";
    
    if( $osBasicSchedFrameEventId[$sysNo] eq "T1_USEREVENT")
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BSF_EVENT_ID".$coreSuffix, $osBasicSchedFrameId[$sysNo];
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BSF_EVENT_INFO".$coreSuffix, "0u"; # event info must be statically 0
    }
    else # T1_ACTIVATION, T1_START, T1_STOP
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BSF_EVENT_ID".$coreSuffix, $osBasicSchedFrameEventId[$sysNo];
        if($osBasicSchedFrameName[$sysNo])
        {
            $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BSF_EVENT_INFO".$coreSuffix, "T1_".$osBasicSchedFrameName[$sysNo]."_ID";
        }
        else # only ID is specified
        {
            if( $osBasicSchedFrameId[$sysNo] ) # leave out if not specified
            {
                $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BSF_EVENT_INFO".$coreSuffix, "$osBasicSchedFrameId[$sysNo]";
            }
        }
    }
    
    if($osBackgroundTaskName[$sysNo])
    {
        $BgTask = "T1_".$osBackgroundTaskName[$sysNo]."_ID";
    }
    elsif($osBackgroundTaskId[$sysNo] != 1000 )
    {
         $BgTask = "$osBackgroundTaskId[$sysNo]";
    }
    else
    {
        $BgTask = "T1_INVALID_TASK_ID";
    }
    if( $useSameConnectionForAllSystems eq 'false' )
    {
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CAN_PC_TO_ECU_ID".$coreSuffix, $canTxID[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CAN_ECU_TO_PC_ID".$coreSuffix, $canRxID[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MIN_RX_FRAME_SIZE".$coreSuffix, $diagMinTxDataSize[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MAX_RX_FRAME_SIZE".$coreSuffix, $diagTxDataSize[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_GCP_MAX_TX_FRAME_SIZE".$coreSuffix, $diagRxDataSize[$sysNo];
    }
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_BACKGROUND_TASK_ID".$coreSuffix, $BgTask;
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TICK_DURATION".$coreSuffix."_NS", $tickDurationNs[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_OVERHEAD".$coreSuffix."_NS", $t1ScopeOverheadNs[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_FLEX_OVERHEAD".$coreSuffix."_NS", $t1FlexOverheadNs[$sysNo];
    $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CPULOAD_CALLBACK".$coreSuffix, $cpuLoadCallback[$sysNo];

    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CPULOAD_THRESHOLD_PERCENT".$coreSuffix, $cpuLoadThreshold[$sysNo])    if($cpuLoadThreshold[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TRACEBUFFER_ENTRIES".$coreSuffix, $traceBufferEntries[$sysNo])        if($traceBufferEntries[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_CSRNS".$coreSuffix, $numberOfConstraints[$sysNo])                 if($numberOfConstraints[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_USER_STPWS".$coreSuffix, $numberOfUserStpws[$sysNo])              if($numberOfUserStpws[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_FLEX_STPWS".$coreSuffix, $nofFlexStopwatches[$sysNo])             if($nofFlexStopwatches[$sysNo]) ;
     $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_STPWS".$coreSuffix,"T1_NOF_USER_STPWS".$coreSuffix." + "."T1_NOF_FLEX_STPWS".$coreSuffix;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_FLEX_ADDRS".$coreSuffix, $nofFlexAddrs[$sysNo])                   if($nofFlexAddrs[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_PTIMER".$coreSuffix, $pTimer[$sysNo])                                 if($pTimer[$sysNo]) ;
    if($traceTimerDownCounting[$sysNo] eq "true")
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TRACE_TIMER_COUNTS_DOWN".$coreSuffix, "T1_TRUE";
        $t1ConfigHDefs .= "#define T1_CONT_SYS_TIME_DOWNCOUNTING\n";
    }
    else
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_TRACE_TIMER_COUNTS_DOWN".$coreSuffix, "T1_FALSE";
    }
    if($Is32BitCpuWithSmallerTimer[$sysNo] eq "true")
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_32BIT_CPU_SMALLER_TIMER".$coreSuffix, "T1_TRUE";
    }
    else
    {
        $t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_32BIT_CPU_SMALLER_TIMER".$coreSuffix, "T1_FALSE";
    }
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CPULOAD_TX_PERIOD".$coreSuffix, $cpuLoadTxPeriod[$sysNo])             if($cpuLoadTxPeriod[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CPULOAD_SAMPLES".$coreSuffix, $cpuLoadAvgSamples[$sysNo])             if($cpuLoadAvgSamples[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_CONT_ANALYSIS_CAPACITY".$coreSuffix, $analysisCapacity[$sysNo])       if($analysisCapacity[$sysNo]) ;
    ($t1ConfigHDefs .= sprintf "#define %-45s(%s)\n", "T1_NOF_DELAYS".$coreSuffix, $nofDelays[$sysNo])                          if($nofDelays[$sysNo]) ;
     $t1ConfigHDefs  .= sprintf "#define %-45s(%s)\n","T1_CET_EVT_CHAIN_TO_IDX".$coreSuffix."(id_)", "T1_NOF_STPWS".$coreSuffix." + 2u*id_ + 0u";
     $t1ConfigHDefs  .= sprintf "#define %-45s(%s)\n","T1_GET_EVT_CHAIN_TO_IDX".$coreSuffix."(id_)", "T1_NOF_STPWS".$coreSuffix." + 2u*id_ + 1u";

}

#----------------------------------------------------------------------------------
my $traceTaskMacro = "#define T1_TRACE_TASK( TASK_ID ) \\\n(  1 \\\n";

foreach my $exclName (@targetExcludeFromTraceByName)
{
    $traceTaskMacro .= " && (TASK_ID != T1_".$exclName."_ID) \\\n";
}
foreach my $exclId (@targetExcludeFromTraceById)
{
   $traceTaskMacro .= " && (TASK_ID != $exclId) \\\n";
}
$traceTaskMacro .= ")\n";

#----------------------------------------------------------------------------------

if ($idHeader ne "")
{
    my $tempIdHeader = $idHeader."_";
    my $idHeaderBaseName = "";

    if( createPath($tempIdHeader) == 0 )
    {
        die "Unable to create path for file $tempIdHeader";
    }
    open (TEMP_ID_HEADER, ">$tempIdHeader") or die "error: could not open file '$tempIdHeader' for output";

    $idHeaderBaseName = File::Basename::basename($idHeader);
    $idHeaderBaseName =~ s/\s//g;

    my $idHeaderMacro = uc($idHeaderBaseName);
    $idHeaderMacro =~ s/\./_/g;
    $idHeaderMacro = "_" . $idHeaderMacro;

    my $idHeaderIncl ="";

    foreach my $inc (@idHeaderIncludes)
    {

        ($idHeaderIncl .= "#include $inc\n") if($inc ne "");
    }

    my $t1idHIds = $t1ConfigHIds;  # copy all task ID macros to ID-header
    $t1ConfigHIds = "";            # delete all task ID macros from config header

    print TEMP_ID_HEADER <<EOF;
/**************************************************************************************************
 *  FILE:           $idHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_preBuild.pl
 *
 *  AUTHOR:         Gliwa GmbH
 *
 *  COPYRIGHT:      gliwa GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 *************************************************************************************************
*/

#ifndef $idHeaderMacro
#define $idHeaderMacro

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$idHeaderIncl
/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1idHIds
/*----------------------------------------------------------------------------------*/
/*--- Macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$traceTaskMacro
/*----------------------------------------------------------------------------------*/
/*--- Function wrapper -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
#ifdef T1_ENABLE
$t1IsrWrapper
#endif /* T1_ENABLE    */
/*----------------------------------------------------------------------------------*/

#endif /* $idHeaderMacro */
EOF

    close (TEMP_ID_HEADER);

    # now make sure that idHeader is only generated if required (idHeader might be included by OS-module and cause strong dependencies)

    if(-e $idHeader) # if idHeader already exists
    {

        if( diffFiles( $tempIdHeader, $idHeader ) ) # files differ. Write to file are equal
        {
            rename $tempIdHeader, $idHeader ;
        }
        else # files are equal
        {
            unlink $tempIdHeader; # remove tempIdHeader
        }
    }
    else # idHeader does not yet exist. Generate from temp file
    {
        rename $tempIdHeader, $idHeader ;
    }
}

#----------------------------------------------------------------------------------

if ($configHeader ne "")
{
    my $tempConfigHeader = $configHeader."_";
    my $configHeaderBaseName = "";
    my $t1config_IsrWrapper = "";
    
    if( createPath($tempConfigHeader) == 0 )
    {
        die "Unable to create path for file $tempConfigHeader";
    }
    open (TEMP_CONFIG_HEADER, ">$tempConfigHeader") or die "error: could not open file '$tempConfigHeader' for output";

    $configHeaderBaseName = File::Basename::basename($configHeader);
    $configHeaderBaseName =~ s/\s//g;

    my $configHeaderMacro = uc($configHeaderBaseName);
    $configHeaderMacro =~ s/\./_/g;
    $configHeaderMacro = "_" . $configHeaderMacro;

    my $configHeaderIncl ="";

    foreach my $inc (@configHeaderIncludes)
    {

        ($configHeaderIncl .= "#include $inc\n") if($inc ne "");
    }

    my $localTraceTaskMacro = "";
    if ($idHeader eq "") # only copy traceTaskMacro to config header if no ID header is generated
    {
        $localTraceTaskMacro = $traceTaskMacro;
        $t1config_IsrWrapper = $t1IsrWrapper;
    }

    print TEMP_CONFIG_HEADER <<EOF;
/**************************************************************************************************
 *  FILE:           $configHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_preBuild.pl
 *
 *  AUTHOR:         Gliwa GmbH
 *
 *  COPYRIGHT:      gliwa GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 *************************************************************************************************
*/

#ifndef $configHeaderMacro
#define $configHeaderMacro

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$configHeaderIncl
/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1ConfigHIds
/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1ConfigHDefs

$localTraceTaskMacro
/*----------------------------------------------------------------------------------*/
/*--- Function wrapper -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
#ifdef T1_ENABLE
$t1config_IsrWrapper
#endif /* T1_ENABLE    */
/*----------------------------------------------------------------------------------*/

#endif /* $configHeaderMacro */
EOF

    close (TEMP_CONFIG_HEADER);
     # now make sure that configHeader is only generated if required (configHeader might be included by OS-module and cause strong dependencies)

    if(-e $configHeader) # if configHeader already exists
    {

        if( diffFiles( $tempConfigHeader, $configHeader ) ) # files differ. Write to file are equal
        {
            rename $tempConfigHeader, $configHeader ;
        }
        else # files are equal
        {
            unlink $tempConfigHeader; # remove tempConfigHeader
        }
    }
    else # configHeader does not yet exist. Generate from temp file
    {
        rename $tempConfigHeader, $configHeader ;
    }
}

#----------------------------------------------------------------------------------

if ($bidHeader ne "")
{
    if( createPath($bidHeader) == 0 )
    {
        die "Unable to create path for file $bidHeader";
    }
    open (BID_HEADER, ">$bidHeader") or die "error: could not open file '$bidHeader' for output";

    $bidHeader = File::Basename::basename($bidHeader);
    $bidHeader =~ s/\s//g;

    my $bidHeaderMacro = uc($bidHeader);
    $bidHeaderMacro =~ s/\./_/g;
    $bidHeaderMacro = "_" . $bidHeaderMacro;

    print BID_HEADER <<EOF;
/**************************************************************************************************
 *  FILE:           $bidHeader
 *
 *  DESCRIPTION:    this header was generated by perl script T1_preBuild.pl
 *
 *  AUTHOR:         Gliwa GmbH
 *
 *  COPYRIGHT:      gliwa GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 *************************************************************************************************
*/

#ifndef $bidHeaderMacro
#define $bidHeaderMacro

/*----------------------------------------------------------------------------------*/
/*--- Config macros ----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1BidHDefs

/*----------------------------------------------------------------------------------*/

#endif /* $bidHeaderMacro */
EOF

    close (BID_HEADER);
}

#----------------------------------------------------------------------------------

if ($runnableHeader ne "")
{
    my $tempRunnableHeader = $runnableHeader."_";
    my $runnableHeaderBaseName = "";
    my $runnableDefnitions = "";

    eval { $runnableDefnitions = OsGetRunnableDefinitions()};

    if( createPath($tempRunnableHeader) == 0 )
    {
        die "Unable to create path for file $tempRunnableHeader";
    }
    open (TEMP_RUNNABLE_HEADER, ">$tempRunnableHeader") or die "error: could not open file '$tempRunnableHeader' for output";

    $runnableHeaderBaseName = File::Basename::basename($runnableHeader);
    $runnableHeaderBaseName =~ s/\s//g;

    my $runnableHeaderMacro = uc($runnableHeaderBaseName);
    $runnableHeaderMacro =~ s/\./_/g;
    $runnableHeaderMacro = "_" . $runnableHeaderMacro;

    my $runnableHeaderIncl ="";

    foreach my $inc (@runnableHeaderIncludes)
    {

        ($runnableHeaderIncl .= "#include $inc\n") if($inc ne "");
    }

    print TEMP_RUNNABLE_HEADER <<EOF;
/**************************************************************************************************
 *  FILE:           $runnableHeaderBaseName
 *
 *  DESCRIPTION:    this header was generated by perl script T1_preBuild.pl
 *
 *  AUTHOR:         Gliwa GmbH
 *
 *  COPYRIGHT:      gliwa GmbH | know-how in embedded software
 *                  Weilheim i.OB.
 *                  All rights reserved
 *************************************************************************************************
*/

#ifndef $runnableHeaderMacro
#define $runnableHeaderMacro

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$runnableHeaderIncl
/*----------------------------------------------------------------------------------*/
/*--- Task and ISR IDs -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
$t1runnableIds
/*----------------------------------------------------------------------------------*/
/*--- Macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
#ifdef T1_TRACE_RUNNABLES

$runnableDefnitions

#endif /* T1_TRACE_RUNNABLES    */
/*----------------------------------------------------------------------------------*/

#endif /* $runnableHeaderMacro */
EOF

    close (TEMP_RUNNABLE_HEADER);

    # now make sure that runnableHeader is only generated if required (runnableHeader might be included by OS-module and cause strong dependencies)

    if(-e $runnableHeader) # if runnableHeader already exists
    {

        if( diffFiles( $tempRunnableHeader, $runnableHeader ) ) # files differ. Write to file are equal
        {
            rename $tempRunnableHeader, $runnableHeader ;
        }
        else # files are equal
        {
            unlink $tempRunnableHeader; # remove tempRunnableHeader
        }
    }
    else # runnableHeader does not yet exist. Generate from temp file
    {
        rename $tempRunnableHeader, $runnableHeader ;
    }
}