@Echo Off
setlocal



set SWC=Assist

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_ASSIST=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_ASSIST=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_ASSIST%
mkdir %GENDEFDIR_ASSIST%



copy ..\generate\Ap_Assist_*.arxml	%BSWMDDIR_ASSIST%
copy ..\generate\Ap_Assist_*.tt	%GENDEFDIR_ASSIST%
copy ..\generate\Ap_Assist_*.bat	%GENDEFDIR_ASSIST%


pause
:end

endlocal

