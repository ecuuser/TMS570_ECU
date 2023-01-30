setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\NvMMgr\NvMMgr.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\NvMMgr\Cd_NvMMgr_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%

goto end

:error
ECHO Error: NvMMgr configuration validation failed

:end

endlocal
