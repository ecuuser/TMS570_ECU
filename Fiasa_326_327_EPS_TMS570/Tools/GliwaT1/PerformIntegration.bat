@echo **************Copying required files to run with Gliwa T1 enabled.**************
cscript.exe ..\..\..\GliwaT1\tools\OverlayAndBackup.vbs "..\..\..\" ".\Overlay" ".\OverlayBackup"
@echo **********************Generating OIL file for Perl scripts.*********************
..\OilTool\AsrToOil.exe ..\AsrProject\Config\ECUC\EPS.ecuc.arxml .\EPS.oil
@echo ********************Generating headers and T1 project file.*********************
perl -I..\..\..\GliwaT1\tools\Generator ^
	..\..\..\GliwaT1\tools\Generator\T1_projGen.pl ^
	-UserCfg=config\T1_UserCfg.inv ^
	-Cfg=config\T1_Cfg.inv ^
	-OsPm=..\..\..\GliwaT1\tools\Generator\T1_Microsar.pm ^
	-OsCfg=config\T1_OsCfg.inv
@echo *******************************Clean up OIL file.*******************************
del .\EPS.oil

pause