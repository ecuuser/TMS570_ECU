@Echo Off
setlocal



set SWC=HystComp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_HYSTCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_HYSTCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_HYSTCOMP%
mkdir %GENDEFDIR_HYSTCOMP%



copy ..\generate\Ap_HystComp_*.arxml	%BSWMDDIR_HYSTCOMP%
copy ..\generate\Ap_HystComp_*.tt	%GENDEFDIR_HYSTCOMP%
copy ..\generate\Ap_HystComp_*.bat	%GENDEFDIR_HYSTCOMP%


pause
:end

endlocal

