setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\VehDyn\VehDyn.verify.tt-i=..\artt\include  -u="http://autosar.org/3.0.2"-o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\VehDyn\Ap_VehDyn_Cfg.h.tt -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE%  -t=..\VehDyn\Ap_VehDyn_Cfg.arxml.tt				  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%SERVICESWCFOLDER%


goto end

:error
ECHO Error: VehDyn configuration validation failed

:end

endlocal
