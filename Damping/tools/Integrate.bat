@Echo Off
setlocal



set SWC=Damping

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_DAMPING=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_DAMPING=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_DAMPING%
mkdir %GENDEFDIR_DAMPING%



copy ..\generate\Ap_Damping_*.arxml	%BSWMDDIR_DAMPING%
copy ..\generate\Ap_Damping_*.tt	%GENDEFDIR_DAMPING%
copy ..\generate\Ap_Damping_*.bat	%GENDEFDIR_DAMPING%


pause
:end

endlocal

