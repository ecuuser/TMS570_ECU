@echo off
REM **The -v2 command is for use only with N2HET devies
REM **N2HET device is used on the 65nm Gladiator TMS570

set SRC_DIR=..\src

hetp -hc32 -n0 -v2 %SRC_DIR%\Nhet_SENT_Prog.het
hetp -hc32 -n1 -v2 %SRC_DIR%\Nhet2_ePWM_Prog.het

REM **Move the output header files to the component include directory
move %SRC_DIR%\Nhet_SENT_Prog.h ..\include
move %SRC_DIR%\Nhet2_ePWM_Prog.h ..\include
pause
