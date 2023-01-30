@Echo Off
setlocal



set SWC=Return

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_RETURN=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_RETURN=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_RETURN%
mkdir %GENDEFDIR_RETURN%



copy ..\generate\Ap_Return_*.arxml	%BSWMDDIR_RETURN%
copy ..\generate\Ap_Return_*.tt	%GENDEFDIR_RETURN%
copy ..\generate\Ap_Return_*.bat	%GENDEFDIR_RETURN%


pause
:end

endlocal

