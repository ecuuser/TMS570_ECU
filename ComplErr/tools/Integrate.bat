@Echo Off
setlocal



set SWC=ComplErr

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_COMPLERR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_COMPLERR=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_COMPLERR%
mkdir %GENDEFDIR_COMPLERR%



copy ..\generate\Ap_ComplErr_*.arxml	%BSWMDDIR_COMPLERR%
copy ..\generate\Ap_ComplErr_*.tt	%GENDEFDIR_COMPLERR%
copy ..\generate\Ap_ComplErr_*.bat	%GENDEFDIR_COMPLERR%


pause
:end

endlocal

