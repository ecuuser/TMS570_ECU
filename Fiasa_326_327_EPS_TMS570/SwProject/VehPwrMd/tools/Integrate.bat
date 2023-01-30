@Echo Off
setlocal



set SWC=VehPwrMd

FOR /D %%G in ("..\..\..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%



set BSWMDDIR_VEHPWRMD=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_VEHPWRMD=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_VEHPWRMD%
mkdir %GENDEFDIR_VEHPWRMD%



copy ..\generate\Ap_VehPwrMd_*.arxml	%BSWMDDIR_VEHPWRMD%
copy ..\generate\Ap_VehPwrMd_*.tt	%GENDEFDIR_VEHPWRMD%
copy ..\generate\Ap_VehPwrMd_*.bat	%GENDEFDIR_VEHPWRMD%


pause
:end

endlocal

