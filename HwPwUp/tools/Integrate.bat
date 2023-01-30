@Echo Off
setlocal



set SWC=HwPwUp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_HWPWUP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_HWPWUP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_HWPWUP%
mkdir %GENDEFDIR_HWPWUP%



copy ..\generate\Ap_HwPwUp_*.arxml	%BSWMDDIR_HWPWUP%
copy ..\generate\Ap_HwPwUp_*.tt	%GENDEFDIR_HWPWUP%
copy ..\generate\Ap_HwPwUp_*.bat	%GENDEFDIR_HWPWUP%


pause
:end

endlocal

