: *******************************************************************
: *** Batch file for calling MICROSARGen from a make environment ***
: *******************************************************************
: *** MICROSAR_DIR must be set to the installation path       ***
: *** MICROSAR_FLAGS must contain the parameter options       ***
: *** Parameter of the batch file is a valid project file with    ***
: *** absolute path                                               ***
: *** ***************************************************************
: *** further details can be found in the help file               ***
: *******************************************************************

cd /d %MICROSAR_DIR%
MicrosarGen.exe %MICROSAR_FLAGS% %1%
