@Echo Off
setlocal



set SWC=DigPhsReasDiag

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_DIGPHSREASDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_DIGPHSREASDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_DIGPHSREASDIAG%
mkdir %GENDEFDIR_DIGPHSREASDIAG%



copy ..\generate\Ap_DigPhsReasDiag_*.arxml	%BSWMDDIR_DIGPHSREASDIAG%
copy ..\generate\Ap_DigPhsReasDiag_*.tt	%GENDEFDIR_DIGPHSREASDIAG%
copy ..\generate\Ap_DigPhsReasDiag_*.bat	%GENDEFDIR_DIGPHSREASDIAG%



set SWC=MtrDrvDiag

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_MTRDRVDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_MTRDRVDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_MTRDRVDIAG%
mkdir %GENDEFDIR_MTRDRVDIAG%



copy ..\generate\Sa_MtrDrvDiag_*.arxml	%BSWMDDIR_MTRDRVDIAG%
copy ..\generate\Sa_MtrDrvDiag_*.tt	%GENDEFDIR_MTRDRVDIAG%
copy ..\generate\Sa_MtrDrvDiag_*.bat	%GENDEFDIR_MTRDRVDIAG%


pause
:end

endlocal

