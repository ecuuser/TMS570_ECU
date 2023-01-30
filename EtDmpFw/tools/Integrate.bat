@Echo Off
setlocal



set SWC=EtDmpFw

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_ETDMPFW=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_ETDMPFW=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_ETDMPFW%
mkdir %GENDEFDIR_ETDMPFW%



copy ..\generate\Ap_EtDmpFw_*.arxml	%BSWMDDIR_ETDMPFW%
copy ..\generate\Ap_EtDmpFw_*.tt	%GENDEFDIR_ETDMPFW%
copy ..\generate\Ap_EtDmpFw_*.bat	%GENDEFDIR_ETDMPFW%


pause
:end

endlocal

