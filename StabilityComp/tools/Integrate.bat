@Echo Off
setlocal



set SWC=StabilityComp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_STABILITYCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_STABILITYCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_STABILITYCOMP%
mkdir %GENDEFDIR_STABILITYCOMP%



copy ..\generate\Ap_StabilityComp_*.arxml	%BSWMDDIR_STABILITYCOMP%
copy ..\generate\Ap_StabilityComp_*.tt	%GENDEFDIR_STABILITYCOMP%
copy ..\generate\Ap_StabilityComp_*.bat	%GENDEFDIR_STABILITYCOMP%



set SWC=StabilityComp2

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_STABILITYCOMP2=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_STABILITYCOMP2=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_STABILITYCOMP2%
mkdir %GENDEFDIR_STABILITYCOMP2%



copy ..\generate\Ap_StabilityComp2_*.arxml	%BSWMDDIR_STABILITYCOMP2%
copy ..\generate\Ap_StabilityComp2_*.tt	%GENDEFDIR_STABILITYCOMP2%
copy ..\generate\Ap_StabilityComp2_*.bat	%GENDEFDIR_STABILITYCOMP2%


pause
:end

endlocal

