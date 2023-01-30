@Echo Off
setlocal



set SWC=AvgFricLrn

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_AVGFRICLRN=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_AVGFRICLRN=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_AVGFRICLRN%
mkdir %GENDEFDIR_AVGFRICLRN%



copy ..\generate\Ap_AvgFricLrn_*.arxml	%BSWMDDIR_AVGFRICLRN%
copy ..\generate\Ap_AvgFricLrn_*.tt	%GENDEFDIR_AVGFRICLRN%
copy ..\generate\Ap_AvgFricLrn_*.bat	%GENDEFDIR_AVGFRICLRN%


pause
:end

endlocal

