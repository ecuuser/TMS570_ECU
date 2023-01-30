@Echo Off
setlocal



set SWC=BVDiag

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_BVDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_BVDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_BVDIAG%
mkdir %GENDEFDIR_BVDIAG%



copy ..\generate\Ap_BVDiag_*.arxml	%BSWMDDIR_BVDIAG%
copy ..\generate\Ap_BVDiag_*.tt	%GENDEFDIR_BVDIAG%
copy ..\generate\Ap_BVDiag_*.bat	%GENDEFDIR_BVDIAG%


pause
:end

endlocal

