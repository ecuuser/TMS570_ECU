@Echo Off
setlocal



set SWC=PwrLmtFuncCr

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_PWRLMTFUNCCR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_PWRLMTFUNCCR=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_PWRLMTFUNCCR%
mkdir %GENDEFDIR_PWRLMTFUNCCR%



copy ..\generate\Ap_PwrLmtFuncCr_*.arxml	%BSWMDDIR_PWRLMTFUNCCR%
copy ..\generate\Ap_PwrLmtFuncCr_*.tt	%GENDEFDIR_PWRLMTFUNCCR%
copy ..\generate\Ap_PwrLmtFuncCr_*.bat	%GENDEFDIR_PWRLMTFUNCCR%


pause
:end

endlocal

