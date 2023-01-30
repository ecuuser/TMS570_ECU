@Echo Off
setlocal



set SWC=Sweep

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_SWEEP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_SWEEP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_SWEEP%
mkdir %GENDEFDIR_SWEEP%



copy ..\generate\Ap_Sweep_*.arxml	%BSWMDDIR_SWEEP%
copy ..\generate\Ap_Sweep_*.tt	%GENDEFDIR_SWEEP%
copy ..\generate\Ap_Sweep_*.bat	%GENDEFDIR_SWEEP%



set SWC=Sweep2

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_SWEEP2=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_SWEEP2=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_SWEEP2%
mkdir %GENDEFDIR_SWEEP2%



copy ..\generate\Ap_Sweep2_*.arxml	%BSWMDDIR_SWEEP2%
copy ..\generate\Ap_Sweep2_*.tt	%GENDEFDIR_SWEEP2%
copy ..\generate\Ap_Sweep2_*.bat	%GENDEFDIR_SWEEP2%


pause
:end

endlocal

