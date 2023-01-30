setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set SERVICESWCFOLDER=%3

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\BatteryVoltage\BatteryVoltage.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

.\artt.exe -d=%ECUCFILE% -t=..\BatteryVoltage\Ap_BatteryVoltage_Cfg.h.tt                   -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\BatteryVoltage\Ap_BatteryVoltage_Cfg.arxml.tt				  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%SERVICESWCFOLDER%


goto end

:error
ECHO Error: BatteryVoltage configuration validation failed

:end

endlocal
