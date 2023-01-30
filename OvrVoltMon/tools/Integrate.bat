@Echo Off
setlocal



set SWC=OvrVoltMon

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_OVRVOLTMON=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_OVRVOLTMON=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_OVRVOLTMON%
mkdir %GENDEFDIR_OVRVOLTMON%



copy ..\generate\Sa_OvrVoltMon_*.arxml	%BSWMDDIR_OVRVOLTMON%
copy ..\generate\Sa_OvrVoltMon_*.tt	%GENDEFDIR_OVRVOLTMON%
copy ..\generate\Sa_OvrVoltMon_*.bat	%GENDEFDIR_OVRVOLTMON%


pause
:end

endlocal

