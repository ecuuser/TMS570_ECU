@Echo Off
setlocal



set SWC=MtrVel

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_MTRVEL=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_MTRVEL=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_MTRVEL%
mkdir %GENDEFDIR_MTRVEL%



copy ..\generate\Sa_MtrVel_*.arxml	%BSWMDDIR_MTRVEL%
copy ..\generate\Sa_MtrVel_*.tt	%GENDEFDIR_MTRVEL%
copy ..\generate\Sa_MtrVel_*.bat	%GENDEFDIR_MTRVEL%



set SWC=MtrVel2

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_MTRVEL2=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_MTRVEL2=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_MTRVEL2%
mkdir %GENDEFDIR_MTRVEL2%



copy ..\generate\Sa_MtrVel2_*.arxml	%BSWMDDIR_MTRVEL2%
copy ..\generate\Sa_MtrVel2_*.tt	%GENDEFDIR_MTRVEL2%
copy ..\generate\Sa_MtrVel2_*.bat	%GENDEFDIR_MTRVEL2%


pause
:end

endlocal

