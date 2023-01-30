@echo off
REM ********************************************************************************************************************
REM *  Description:    CBD RTE generation for SWC Update and contract phase generation for use with unit testing
REM *  Created By:     Nexteer
REM *  Prerequisites:  The Rte Generator of choice must be located in a Folder named RteGen in the UnitTestEnv subproject
REM *                  located at the same folder level of the SWC project folder
REM *
REM ********************************************************************************************************************
 REM ** Change file permissions to writable to all update of the file by rtegen

DEL logfile.txt
attrib -r "..\src\*.c" >>logfile.txt
attrib -r "..\utp\contract\*.h" >>logfile.txt

 set dcf=MotorControl_IM


set SWC=Ap_CurrCmd


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_CurrCmd" >>logfile.txt

set SWC=Ap_CurrParamComp


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_CurrParamComp" >>logfile.txt

set SWC=Ap_PeakCurrEst


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_PeakCurrEst" >>logfile.txt

set SWC=Ap_QuadDet


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_QuadDet" >>logfile.txt

set SWC=Ap_TrqCanc


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_TrqCanc" >>logfile.txt

set SWC=Ap_TrqCmdScl


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_TrqCmdScl" >>logfile.txt


set SWC=Ap_PICurrCntrl


..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g i -o "..\src" >>logfile.txt
..\..\Autosar3Tools\RteGen\dvrtegen -d "..\autosar\%dcf%.dcf" -m %SWC% -g c -o "..\utp\contract\Ap_PICurrCntrl" >>logfile.txt