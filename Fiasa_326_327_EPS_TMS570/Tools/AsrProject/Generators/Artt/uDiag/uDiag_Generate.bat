setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\uDiag\uDiag.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\uDiag\uDiag_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\uDiag\uDiag_Cfg.c.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\uDiag\Cd_uDiag_Cfg.arxml.tt				  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%SERVICESWCFOLDER%


REM delete template files
REM   del %TARGETDIR%\*.arxml

goto end

:error
ECHO Error: UDIAG configuration validation failed

:end

endlocal
