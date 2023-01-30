@Echo Off
setlocal



set SWC=DigMSB

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_DIGMSB=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_DIGMSB=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_DIGMSB%
mkdir %GENDEFDIR_DIGMSB%



copy ..\generate\Sa_DigMSB_*.arxml	%BSWMDDIR_DIGMSB%
copy ..\generate\Sa_DigMSB_*.tt	%GENDEFDIR_DIGMSB%
copy ..\generate\Sa_DigMSB_*.bat	%GENDEFDIR_DIGMSB%


pause
:end

endlocal

