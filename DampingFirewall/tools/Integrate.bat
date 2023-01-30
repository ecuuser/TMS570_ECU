@Echo Off
setlocal



set SWC=DampingFirewall

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_DAMPINGFIREWALL=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_DAMPINGFIREWALL=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_DAMPINGFIREWALL%
mkdir %GENDEFDIR_DAMPINGFIREWALL%



copy ..\generate\Ap_DampingFirewall_*.arxml	%BSWMDDIR_DAMPINGFIREWALL%
copy ..\generate\Ap_DampingFirewall_*.tt	%GENDEFDIR_DAMPINGFIREWALL%
copy ..\generate\Ap_DampingFirewall_*.bat	%GENDEFDIR_DAMPINGFIREWALL%


pause
:end

endlocal

