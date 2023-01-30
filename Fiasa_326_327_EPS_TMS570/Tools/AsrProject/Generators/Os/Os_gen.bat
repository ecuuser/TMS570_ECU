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
rem output path -> path for MICROSAR OS output files
set OUTPUT_PATH=%2
rem delete all "
set OUTPUT_PATH=%OUTPUT_PATH:"=%
rem if last character is a \ remove last character
if "%OUTPUT_PATH:~-1,1%" == "\" set OUTPUT_PATH=%OUTPUT_PATH:~0,-1%
rem add current working dir as base if output path only contains relative path
if not "%OUTPUT_PATH:~1,2%" == ":\" set OUTPUT_PATH=%CD%\%OUTPUT_PATH%
echo [Info] Os - Target path = %OUTPUT_PATH%.


rem #######################################################################
rem generator and converter path are local to this batch file
rem #######################################################################
rem change to directory this batch file is contained in
cd /d %0\..
set GEN_PATH=.
set CONV_PATH=.
echo PATH = 

rem generator and converter name
set GEN_NAME=genTMS570SafeCtxAS.exe
set CONV_NAME=AsrToOil.exe


rem #######################################################################
rem first convert to xml file to an oil file
rem #######################################################################
echo [Info] Os - Start ECUC to OIL conversion.
echo "%CONV_PATH%\%CONV_NAME%" "%XML_FILE%" "%OIL_FILE%"
"%CONV_PATH%\%CONV_NAME%" "%XML_FILE%" "%OIL_FILE%"
if not exist "%OIL_FILE%" goto conversionerror
echo [Info] Os - Finished ECUC to OIL conversion successfully.

rem #######################################################################
rem cleanup existing html and orti files
rem #######################################################################
for %%i in ("%OUTPUT_PATH%\*.HTM") do del "%%i"
for %%i in ("%OUTPUT_PATH%\*.ORT") do del "%%i"

rem #######################################################################
rem now do the generation
rem #######################################################################
rem if the pathes are too long it may be necessary to read the generation
rem options from an option file.
rem the generator must be invoked then %GEN_PATH%\%GEN_NAME% -f option_file_name
rem all option have to be put to the option file first
rem #######################################################################
echo "%GEN_PATH%\%GEN_NAME%" -x -d "%OUTPUT_PATH%" -g "%OIL_FILE%"
"%GEN_PATH%\%GEN_NAME%" -x -d "%OUTPUT_PATH%" -g "%OIL_FILE%"
if not exist "%OUTPUT_PATH%\tcb.c" goto generationerror
echo [Info] Os - Finished OIL generation successfully.

set HTML=%OIL_FILE:~,-3%htm
set ORTI=%OIL_FILE:~,-3%ort

if not exist "%HTML%" goto orti
copy "%HTML%" "%OUTPUT_PATH%"
for %%i in ("%OUTPUT_PATH%\*.HTM") do set HTML=%%i
echo [Info] HTML List file: '%HTML%'

:orti
if not exist "%ORTI%" goto end
copy "%ORTI%" "%OUTPUT_PATH%"
for %%i in ("%OUTPUT_PATH%\*.ORT") do set ORTI=%%i
echo [Info] ORTI Debug file: '%ORTI%'

goto end

:conversionerror
echo [Error] Os - ECUC to OIL conversion failed.
exit 1

:generationerror
echo [Error] Os - OIL generation failed.
exit 2

:end
   rem delete the intermediate files (if wanted)
   if exist "%OIL_FILE%" del "%OIL_FILE%"
