@Echo Off
setlocal



set SWC=AstLmt

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_ASTLMT=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_ASTLMT=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_ASTLMT%
mkdir %GENDEFDIR_ASTLMT%



copy ..\generate\Ap_AstLmt_*.arxml	%BSWMDDIR_ASTLMT%
copy ..\generate\Ap_AstLmt_*.tt	%GENDEFDIR_ASTLMT%
copy ..\generate\Ap_AstLmt_*.bat	%GENDEFDIR_ASTLMT%


pause
:end

endlocal

