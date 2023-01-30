@Echo Off
setlocal



set SWC=DigColPs

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_DIGCOLPS=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_DIGCOLPS=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_DIGCOLPS%
mkdir %GENDEFDIR_DIGCOLPS%



copy ..\generate\Sa_DigColPs_*.arxml	%BSWMDDIR_DIGCOLPS%
copy ..\generate\Sa_DigColPs_*.tt	%GENDEFDIR_DIGCOLPS%
copy ..\generate\Sa_DigColPs_*.bat	%GENDEFDIR_DIGCOLPS%


pause
:end

endlocal

