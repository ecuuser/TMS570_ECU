setlocal

set ECUCFILE=%1
set TARGETDIR=%2

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\FlsTst\FlsTst.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\FlsTst\FlsTst_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\FlsTst\FlsTst_Cfg.c.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM .\artt.exe -d=%ECUCFILE% -t=..\FlsTst\FlsTst_swc_interface.arxml.tt     -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM .\artt.exe -d=%ECUCFILE% -t=..\FlsTst\FlsTst_swc_internal.arxml.tt      -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%

REM delete template files
REM   del %TARGETDIR%\*.arxml

goto end

:error
ECHO Error: FLSTST configuration validation failed

:end

endlocal
