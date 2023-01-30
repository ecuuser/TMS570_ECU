@Echo Off
setlocal



set SWC=AbsHwPos

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_ABSHWPOS=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_ABSHWPOS=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_ABSHWPOS%
mkdir %GENDEFDIR_ABSHWPOS%



copy ..\generate\Ap_AbsHwPos_*.arxml	%BSWMDDIR_ABSHWPOS%
copy ..\generate\Ap_AbsHwPos_*.tt	%GENDEFDIR_ABSHWPOS%
copy ..\generate\Ap_AbsHwPos_*.bat	%GENDEFDIR_ABSHWPOS%


pause
:end

endlocal

