setlocal

set ECUCFILE=%1
set TARGETDIR=%2
set TEMPLATEDIR=%CD%

cd ..\artt

REM .\artt.exe -d=%ECUCFILE% -t=..\uDiag\uDiag.verify.tt                  -i=..\artt\include  -u="http://autosar.org/3.0.2"  -o=%TARGETDIR%
REM if %ERRORLEVEL% NEQ 0 goto error

..\..\SafeWdg\Wdg_Mgr_Cfg_Gen.exe %ECUCFILE% %TARGETDIR%
.\artt.exe -d=%ECUCFILE% -t=..\WdgM\WdgM_Graph.dot.tt                  -i=..\artt\include  -u="http://autosar.org/3.1.4"  -o=%TEMPLATEDIR%

REM Run GraphViz on generated .dot file
dot -Tpdf %TEMPLATEDIR%\WdgM_Graph.dot -o %TARGETDIR%\WdgM_Graph.pdf

goto end

:error
ECHO Error: WdgM Graph Generation failed

:end

endlocal
