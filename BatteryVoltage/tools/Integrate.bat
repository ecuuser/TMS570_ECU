@Echo Off
setlocal



set SWC=BatteryVoltage

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_BATTERYVOLTAGE=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_BATTERYVOLTAGE=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_BATTERYVOLTAGE%
mkdir %GENDEFDIR_BATTERYVOLTAGE%



copy ..\generate\Ap_BatteryVoltage_*.arxml	%BSWMDDIR_BATTERYVOLTAGE%
copy ..\generate\Ap_BatteryVoltage_*.tt	%GENDEFDIR_BATTERYVOLTAGE%
copy ..\generate\Ap_BatteryVoltage_*.bat	%GENDEFDIR_BATTERYVOLTAGE%


pause
:end

endlocal

