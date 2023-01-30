@Echo Off
setlocal

REM *** Assume the component name is the name of the directory 1 level up from this directory ***
for %%* in (..) do set SWC=%%~n*
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

