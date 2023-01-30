setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\NvMProxy\NvMProxy.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\NvMProxy\Cd_NvMProxy_Cfg.h.tt					-i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\NvMProxy\Cd_NvMProxy_PBcfg.c.tt					-i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\NvMProxy\Cd_NvMProxy_swc.arxml.tt				-i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%SERVICESWCFOLDER%


goto end

:error
ECHO Error: NvMProxy configuration validation failed

:end

endlocal
