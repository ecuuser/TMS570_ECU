@echo off
REM ********************************************************************************************************************
REM *  Description:    CBD RTE generation for SWC Update and contract phase generation for use with unit testing
REM *  Created By:     Nexteer
REM *  Prerequisites:  The Rte Generator of choice must be located in a Folder named RteGen in the Autosar3Tools subproject
REM *                  located at the same folder level of the SWC project folder
REM *
REM ********************************************************************************************************************
 REM ** Change file permissions to writable to all update of the file by rtegen

DEL logfile.txt
attrib -r "..\src\*.c" >>logfile.txt
attrib -r "..\utp\contract\*.h" >>logfile.txt

 set dcf=Ap_ePWM


set SWC=Ap_ePWM2


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_ePWM2" >>logfile.txt

set SWC=Cd_Nhet1


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Cd_Nhet1" >>logfile.txt