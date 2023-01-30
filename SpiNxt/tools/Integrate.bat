@Echo Off
setlocal

REM *** This project is made up of 1 BSW, the CDD SpiNxt ***
set SWC_SPINXT=SpiNxt

REM *** Assume the integration project follows the standard naming convention and has an "_EPS_" string in it ***
FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

set BSWMDDIR_SPINXT=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC_SPINXT%\bswmd
set GENDEFDIR_SPINXT=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC_SPINXT%

mkdir %BSWMDDIR_SPINXT%
mkdir %GENDEFDIR_SPINXT%

copy ..\generate\SpiNxt*.arxml			%BSWMDDIR_SPINXT%
copy ..\generate\SpiNxt*.tt			%GENDEFDIR_SPINXT%
copy ..\generate\SpiNxt*.bat			%GENDEFDIR_SPINXT%

pause
:end

endlocal

