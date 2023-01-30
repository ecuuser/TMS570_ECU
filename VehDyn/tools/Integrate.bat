@Echo Off
setlocal



set SWC=VehDyn

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_VEHDYN=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_VEHDYN=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_VEHDYN%
mkdir %GENDEFDIR_VEHDYN%



copy ..\generate\Ap_VehDyn_*.arxml	%BSWMDDIR_VEHDYN%
copy ..\generate\Ap_VehDyn_*.tt	        %GENDEFDIR_VEHDYN%
copy ..\generate\Ap_VehDyn_*.bat	%GENDEFDIR_VEHDYN%


pause
:end

endlocal

