@Echo Off
setlocal

REM *** Assume the component name is the name of the directory 1 level up from this directory ***
REM *** To avoid namespace conflicts with the Autosar BSW Xcp, "Ap" is prefixed to the name.  This is not a standard Nexteer naming convention and should be cleaned up when time permits by renaming this entire module.
for %%* in (..) do set SWC=%%~n*
set SWC=Ap%SWC%
echo SWC name is: %SWC%

REM *** Assume the integration project follows the standard naming convention and has an "_EPS_" string in it ***
FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%


set BSWMDDIR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%

mkdir %BSWMDDIR%
mkdir %GENDEFDIR%

copy ..\generate\*.arxml	%BSWMDDIR%
copy ..\generate\*.tt		%GENDEFDIR%
copy ..\generate\*.bat		%GENDEFDIR%
pause
:end

endlocal

