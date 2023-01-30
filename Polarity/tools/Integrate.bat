@Echo Off
setlocal



set SWC=Polarity

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_POLARITY=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_POLARITY=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_POLARITY%
mkdir %GENDEFDIR_POLARITY%



copy ..\generate\Ap_Polarity_*.arxml	%BSWMDDIR_POLARITY%
copy ..\generate\Ap_Polarity_*.tt	%GENDEFDIR_POLARITY%
copy ..\generate\Ap_Polarity_*.bat	%GENDEFDIR_POLARITY%


pause
:end

endlocal

