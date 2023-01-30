@Echo Off
setlocal



set SWC=ReturnFirewall

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_RETURNFIREWALL=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_RETURNFIREWALL=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_RETURNFIREWALL%
mkdir %GENDEFDIR_RETURNFIREWALL%



copy ..\generate\Ap_ReturnFirewall_*.arxml	%BSWMDDIR_RETURNFIREWALL%
copy ..\generate\Ap_ReturnFirewall_*.tt	%GENDEFDIR_RETURNFIREWALL%
copy ..\generate\Ap_ReturnFirewall_*.bat	%GENDEFDIR_RETURNFIREWALL%


pause
:end

endlocal

