@echo off
rem **********************************************************************************************************************
rem *  COPYRIGHT
rem *  -------------------------------------------------------------------------------------------------------------------
rem *  Copyright (c) by Vector Informatik GmbH.                                              All rights reserved.
rem *
rem *                This software is copyright protected and proprietary to Vector Informatik GmbH.
rem *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
rem *                All other rights remain with Vector Informatik GmbH.
rem *********************************************************************************************************************/
rem
rem *  this file is generated during setup creation
rem *********************************************************************************************************************/


rem #######################################################################
rem parameters
rem %1 XML file to be converted
rem %2 output path
rem #######################################################################
set XML_FILE=%1
rem delete all "
set XML_FILE=%XML_FILE:"=%
echo [Info] Os - ECU-C file = %XML_FILE%.
set OIL_FILE=%XML_FILE%.oil

rem #######################################################################
rem generator and converter path are local to this batch file
rem #######################################################################
rem change to directory this batch file is contained in
cd /d %0\..
set TA_PATH=..\Tools\TimingAnalyzer
set CONV_PATH=.
set INC_PATH=.
echo PATH = 

set CONV_NAME=AsrToOil.exe
set TA_NAME=TimingAnalyzer.exe

rem #######################################################################
rem first convert to xml file to an oil file
rem #######################################################################
echo [Info] Os - Start ECUC to OIL conversion.
echo "%CONV_PATH%\%CONV_NAME%" "%XML_FILE%" "%OIL_FILE%"
"%CONV_PATH%\%CONV_NAME%" "%XML_FILE%" "%OIL_FILE%"
if not exist "%OIL_FILE%" goto conversionerror
echo [Info] Os - Finished ECUC to OIL conversion successfully.

rem #######################################################################
rem now start the TimingAnalyzer
rem #######################################################################
"%TA_PATH%\%TA_NAME%" /i"%INC_PATH%" "%OIL_FILE%"

goto end

:conversionerror
echo [Error] Os - ECUC to OIL conversion failed.
exit 1

:end
   rem delete the intermediate files (if wanted)
   if exist "%OIL_FILE%" del "%OIL_FILE%"
