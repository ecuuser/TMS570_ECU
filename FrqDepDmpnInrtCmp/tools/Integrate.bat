@Echo Off
setlocal



set SWC=FrqDepDmpnInrtCmp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_FRQDEPDMPNINRTCMP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_FRQDEPDMPNINRTCMP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_FRQDEPDMPNINRTCMP%
mkdir %GENDEFDIR_FRQDEPDMPNINRTCMP%



copy ..\generate\Ap_FrqDepDmpnInrtCmp_*.arxml	%BSWMDDIR_FRQDEPDMPNINRTCMP%
copy ..\generate\Ap_FrqDepDmpnInrtCmp_*.tt	%GENDEFDIR_FRQDEPDMPNINRTCMP%
copy ..\generate\Ap_FrqDepDmpnInrtCmp_*.bat	%GENDEFDIR_FRQDEPDMPNINRTCMP%


pause
:end

endlocal

