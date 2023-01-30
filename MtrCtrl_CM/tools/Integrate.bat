@Echo Off
setlocal



set SWC=CurrCmd

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_CURRCMD=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_CURRCMD=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_CURRCMD%
mkdir %GENDEFDIR_CURRCMD%



copy ..\generate\Ap_CurrCmd_*.arxml	%BSWMDDIR_CURRCMD%
copy ..\generate\Ap_CurrCmd_*.tt	%GENDEFDIR_CURRCMD%
copy ..\generate\Ap_CurrCmd_*.bat	%GENDEFDIR_CURRCMD%



set SWC=CurrParamComp

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_CURRPARAMCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_CURRPARAMCOMP=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_CURRPARAMCOMP%
mkdir %GENDEFDIR_CURRPARAMCOMP%



copy ..\generate\Ap_CurrParamComp_*.arxml	%BSWMDDIR_CURRPARAMCOMP%
copy ..\generate\Ap_CurrParamComp_*.tt	%GENDEFDIR_CURRPARAMCOMP%
copy ..\generate\Ap_CurrParamComp_*.bat	%GENDEFDIR_CURRPARAMCOMP%



set SWC=PeakCurrEst

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_PEAKCURREST=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_PEAKCURREST=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_PEAKCURREST%
mkdir %GENDEFDIR_PEAKCURREST%



copy ..\generate\Ap_PeakCurrEst_*.arxml	%BSWMDDIR_PEAKCURREST%
copy ..\generate\Ap_PeakCurrEst_*.tt	%GENDEFDIR_PEAKCURREST%
copy ..\generate\Ap_PeakCurrEst_*.bat	%GENDEFDIR_PEAKCURREST%



set SWC=QuadDet

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_QUADDET=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_QUADDET=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_QUADDET%
mkdir %GENDEFDIR_QUADDET%



copy ..\generate\Ap_QuadDet_*.arxml	%BSWMDDIR_QUADDET%
copy ..\generate\Ap_QuadDet_*.tt	%GENDEFDIR_QUADDET%
copy ..\generate\Ap_QuadDet_*.bat	%GENDEFDIR_QUADDET%



set SWC=TrqCanc

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_TRQCANC=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_TRQCANC=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_TRQCANC%
mkdir %GENDEFDIR_TRQCANC%



copy ..\generate\Ap_TrqCanc_*.arxml	%BSWMDDIR_TRQCANC%
copy ..\generate\Ap_TrqCanc_*.tt	%GENDEFDIR_TRQCANC%
copy ..\generate\Ap_TrqCanc_*.bat	%GENDEFDIR_TRQCANC%



set SWC=TrqCmdScl

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_TRQCMDSCL=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_TRQCMDSCL=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_TRQCMDSCL%
mkdir %GENDEFDIR_TRQCMDSCL%



copy ..\generate\Ap_TrqCmdScl_*.arxml	%BSWMDDIR_TRQCMDSCL%
copy ..\generate\Ap_TrqCmdScl_*.tt	%GENDEFDIR_TRQCMDSCL%
copy ..\generate\Ap_TrqCmdScl_*.bat	%GENDEFDIR_TRQCMDSCL%


pause
:end

endlocal

