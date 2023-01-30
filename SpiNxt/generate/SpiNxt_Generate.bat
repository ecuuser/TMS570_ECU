setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\SpiNxt\SpiNxt.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\SpiNxt\SpiNxt_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%


REM delete template files
REM   del %TARGETDIR%\*.arxml

goto end

:error
ECHO Error: SPINXT configuration validation failed

:end

endlocal
