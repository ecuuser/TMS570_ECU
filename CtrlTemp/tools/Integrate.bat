@Echo Off
setlocal



set SWC=CtrlTemp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_CTRLTEMP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_CTRLTEMP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_CTRLTEMP%
mkdir %GENDEFDIR_CTRLTEMP%



copy ..\generate\Sa_CtrlTemp_*.arxml	%BSWMDDIR_CTRLTEMP%
copy ..\generate\Sa_CtrlTemp_*.tt	%GENDEFDIR_CTRLTEMP%
copy ..\generate\Sa_CtrlTemp_*.bat	%GENDEFDIR_CTRLTEMP%


pause
:end

endlocal

