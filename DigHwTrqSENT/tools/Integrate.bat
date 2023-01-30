@Echo Off
setlocal

REM *** This project is made up of 1 BSW, the SA DigHwTrqSENT ***
set SWC_DIGHWTRQSENT=DigHwTrqSENT

REM *** Assume the integration project follows the standard naming convention and has an "_EPS_" string in it ***
FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

set BSWMDDIR_DIGHWTRQSENT=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC_DIGHWTRQSENT%\bswmd
set GENDEFDIR_DIGHWTQRSENT=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC_DIGHWTRQSENT%

mkdir %BSWMDDIR_DIGHWTRQSENT%
mkdir %GENDEFDIR_DIGHWTQRSENT%

copy ..\generate\Sa_DigHwTrqSENT*.arxml			%BSWMDDIR_DIGHWTRQSENT%
copy ..\generate\Sa_DigHwTrqSENT*.tt			%GENDEFDIR_DIGHWTQRSENT%
copy ..\generate\Sa_DigHwTrqSENT*.bat			%GENDEFDIR_DIGHWTQRSENT%

pause
:end

endlocal

