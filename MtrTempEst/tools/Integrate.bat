@Echo Off
setlocal



set SWC=MtrTempEst

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_MTRTEMPEST=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_MTRTEMPEST=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_MTRTEMPEST%
mkdir %GENDEFDIR_MTRTEMPEST%



copy ..\generate\Ap_MtrTempEst_*.arxml	%BSWMDDIR_MTRTEMPEST%
copy ..\generate\Ap_MtrTempEst_*.tt	%GENDEFDIR_MTRTEMPEST%
copy ..\generate\Ap_MtrTempEst_*.bat	%GENDEFDIR_MTRTEMPEST%


pause
:end

endlocal

