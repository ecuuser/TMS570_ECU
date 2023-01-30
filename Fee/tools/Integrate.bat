@Echo Off
setlocal

REM *** Assume the integration project follows the standard naming convention and has an "_EPS_" string in it ***
FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

set SWC=Fee
set SCHEMESDIR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%

echo Deleting Old Directory
rmdir %SCHEMESDIR% /s /q
echo Copying New Directory
mkdir %SCHEMESDIR%

xcopy ..\generate\%SWC%	%SCHEMESDIR% /s


pause
:end

endlocal

