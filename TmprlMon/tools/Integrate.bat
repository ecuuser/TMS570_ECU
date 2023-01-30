@Echo Off
setlocal



set SWC=TmprlMon

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_TMPRLMON=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_TMPRLMON=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_TMPRLMON%
mkdir %GENDEFDIR_TMPRLMON%



copy ..\generate\Sa_TmprlMon_*.arxml	%BSWMDDIR_TMPRLMON%
copy ..\generate\Sa_TmprlMon_*.tt	%GENDEFDIR_TMPRLMON%
copy ..\generate\Sa_TmprlMon_*.bat	%GENDEFDIR_TMPRLMON%



set SWC=TmprlMon2

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_TMPRLMON2=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_TMPRLMON2=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_TMPRLMON2%
mkdir %GENDEFDIR_TMPRLMON2%



copy ..\generate\Sa_TmprlMon2_*.arxml	%BSWMDDIR_TMPRLMON2%
copy ..\generate\Sa_TmprlMon2_*.tt	%GENDEFDIR_TMPRLMON2%
copy ..\generate\Sa_TmprlMon2_*.bat	%GENDEFDIR_TMPRLMON2%


pause
:end

endlocal

