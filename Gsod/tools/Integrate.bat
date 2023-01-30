@Echo Off
setlocal

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%



set SWC=Gsod
 

set BSWMDDIR_GSOD=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_GSOD=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_GSOD%
mkdir %GENDEFDIR_GSOD%



copy ..\generate\Ap_Gsod_*.arxml	%BSWMDDIR_GSOD%
copy ..\generate\Ap_Gsod_*.tt	%GENDEFDIR_GSOD%
copy ..\generate\Ap_Gsod_*.bat	%GENDEFDIR_GSOD%


pause
:end

endlocal

