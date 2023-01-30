@Echo Off
setlocal



set SWC=SignlCondn

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_SIGNLCONDN=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_SIGNLCONDN=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_SIGNLCONDN%
mkdir %GENDEFDIR_SIGNLCONDN%



copy ..\generate\Ap_SignlCondn_*.arxml	%BSWMDDIR_SIGNLCONDN%
copy ..\generate\Ap_SignlCondn_*.tt	%GENDEFDIR_SIGNLCONDN%
copy ..\generate\Ap_SignlCondn_*.bat	%GENDEFDIR_SIGNLCONDN%


pause
:end

endlocal

