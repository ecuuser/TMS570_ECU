@Echo Off
setlocal



set SWC=ElePwr

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_ELEPWR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_ELEPWR=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_ELEPWR%
mkdir %GENDEFDIR_ELEPWR%



copy ..\generate\Ap_ElePwr_*.arxml	%BSWMDDIR_ELEPWR%
copy ..\generate\Ap_ElePwr_*.tt	%GENDEFDIR_ELEPWR%
copy ..\generate\Ap_ElePwr_*.bat	%GENDEFDIR_ELEPWR%


pause
:end

endlocal

