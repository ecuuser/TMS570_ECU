setlocal

set ECUCFILE=%1
set TARGETDIR=%2

cd ..\artt

.\artt.exe -d=%ECUCFILE% -t=..\ApXcp\Ap_ApXcp_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\ApXcp\Ap_ApXcp_Cfg.c.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%

goto end

:error
ECHO Error: StaMd configuration validation failed

:end

endlocal
