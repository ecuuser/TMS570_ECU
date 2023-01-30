@Echo Off
setlocal



set SWC=LmtCod

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_LMTCOD=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_LMTCOD=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_LMTCOD%
mkdir %GENDEFDIR_LMTCOD%



copy ..\generate\Ap_LmtCod_*.arxml	%BSWMDDIR_LMTCOD%
copy ..\generate\Ap_LmtCod_*.tt	%GENDEFDIR_LMTCOD%
copy ..\generate\Ap_LmtCod_*.bat	%GENDEFDIR_LMTCOD%


pause
:end

endlocal

