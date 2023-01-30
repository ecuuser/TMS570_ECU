@Echo Off
setlocal



set SWC=EOTActuatorMng

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_EOTACTUATORMNG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_EOTACTUATORMNG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_EOTACTUATORMNG%
mkdir %GENDEFDIR_EOTACTUATORMNG%



copy ..\generate\Ap_EOTActuatorMng_*.arxml	%BSWMDDIR_EOTACTUATORMNG%
copy ..\generate\Ap_EOTActuatorMng_*.tt	%GENDEFDIR_EOTACTUATORMNG%
copy ..\generate\Ap_EOTActuatorMng_*.bat	%GENDEFDIR_EOTACTUATORMNG%


pause
:end

endlocal

