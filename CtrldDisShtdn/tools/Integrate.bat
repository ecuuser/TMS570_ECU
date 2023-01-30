@Echo Off
setlocal



set SWC=CtrldDisShtdn

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_CTRLDDISSHTDN=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_CTRLDDISSHTDN=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_CTRLDDISSHTDN%
mkdir %GENDEFDIR_CTRLDDISSHTDN%



copy ..\generate\Ap_CtrldDisShtdn_*.arxml	%BSWMDDIR_CTRLDDISSHTDN%
copy ..\generate\Ap_CtrldDisShtdn_*.tt	%GENDEFDIR_CTRLDDISSHTDN%
copy ..\generate\Ap_CtrldDisShtdn_*.bat	%GENDEFDIR_CTRLDDISSHTDN%


pause
:end

endlocal

