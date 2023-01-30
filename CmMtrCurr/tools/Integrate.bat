@Echo Off
setlocal



set SWC=CmMtrCurr

FOR /D %%G in ("..\..\*_EPS_*") DO set INTPJTDIR=%%G
echo Integration project relative path is: %INTPJTDIR%

 

set BSWMDDIR_CMMTRCURR=%INTPJTDIR%\Tools\AsrProject\Generators\Components\_Schemes\%SWC%\bswmd
set GENDEFDIR_CMMTRCURR=%INTPJTDIR%\Tools\AsrProject\Generators\Artt\%SWC%


mkdir %BSWMDDIR_CMMTRCURR%
mkdir %GENDEFDIR_CMMTRCURR%



copy ..\generate\Sa_CmMtrCurr_*.arxml	%BSWMDDIR_CMMTRCURR%
copy ..\generate\Sa_CmMtrCurr_*.tt	%GENDEFDIR_CMMTRCURR%
copy ..\generate\Sa_CmMtrCurr_*.bat	%GENDEFDIR_CMMTRCURR%


pause
:end

endlocal

