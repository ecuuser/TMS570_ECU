@echo off

rem Command line script to register BMW SSWC signature with .NET Code Access Security to allow running signed applications
rem from remote locations.
rem 
rem Created 2008 by BMW AG

rem Adapt this path if your .NET 2.0 runtime resides in a different folder:
set NET20FOLDER=C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727
set CASPOL=%NET20FOLDER%\CasPol.exe

rem Switch interactive mode off:
%CASPOL% -pp off

rem Add certificates for artt:
%CASPOL% -machine -addgroup 1 -strong -file %~dp0%artt.exe -noname -noversion FullTrust -n BMW_Sswc_Strong_Name -description "Signed BMW system software components."

rem To remove certificate call this:
rem %CASPOL% -machine -rg BMW_Sswc_Strong_Name

rem Switch interactive mode on:
%CASPOL% -pp on
