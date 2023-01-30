@Echo Off
setlocal

REM *** This project is made up of 2 BSW's, the standard FlsTst and the CDD uDiag ***
set SWC_FLSTST=FlsTst
set SWC_UDIAG=uDiag

REM *** Assume the integration project follows the standard naming convention and has an "_EPS_" string in it ***
FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

set BSWMDDIR_FLSTST=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC_FLSTST%\bswmd
set GENDEFDIR_FLSTST=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC_FLSTST%

set BSWMDDIR_UDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC_UDIAG%\bswmd
set GENDEFDIR_UDIAG=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC_UDIAG%

mkdir %BSWMDDIR_FLSTST%
mkdir %GENDEFDIR_FLSTST%

mkdir %BSWMDDIR_UDIAG%
mkdir %GENDEFDIR_UDIAG%

copy ..\generate\FlsTst_*.arxml		%BSWMDDIR_FLSTST%
copy ..\generate\FlsTst_*.tt		%GENDEFDIR_FLSTST%
copy ..\generate\FlsTst_*.bat		%GENDEFDIR_FLSTST%

copy ..\generate\uDiag*.arxml		%BSWMDDIR_UDIAG%
copy ..\generate\Cd_uDiag*.tt			%GENDEFDIR_UDIAG%
copy ..\generate\uDiag*.tt			%GENDEFDIR_UDIAG%
copy ..\generate\uDiag*.bat			%GENDEFDIR_UDIAG%

pause
:end

endlocal

