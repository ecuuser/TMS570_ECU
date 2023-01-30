@Echo Off
setlocal



set SWC=TqRsDg

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_TQRSDG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_TQRSDG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_TQRSDG%
mkdir %GENDEFDIR_TQRSDG%



copy ..\generate\Ap_TqRsDg_*.arxml	%BSWMDDIR_TQRSDG%
copy ..\generate\Ap_TqRsDg_*.tt	%GENDEFDIR_TQRSDG%
copy ..\generate\Ap_TqRsDg_*.bat	%GENDEFDIR_TQRSDG%


pause
:end

endlocal

