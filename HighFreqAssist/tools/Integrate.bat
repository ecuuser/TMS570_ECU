@Echo Off
setlocal



set SWC=HighFreqAssist

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_HIGHFREQASSIST=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_HIGHFREQASSIST=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_HIGHFREQASSIST%
mkdir %GENDEFDIR_HIGHFREQASSIST%



copy ..\generate\Ap_HighFreqAssist_*.arxml	%BSWMDDIR_HIGHFREQASSIST%
copy ..\generate\Ap_HighFreqAssist_*.tt	%GENDEFDIR_HIGHFREQASSIST%
copy ..\generate\Ap_HighFreqAssist_*.bat	%GENDEFDIR_HIGHFREQASSIST%


pause
:end

endlocal

