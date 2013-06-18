@echo OFF

REM =========================================================
REM Makes a distribution from pircbotcpp source files.

REM Prereq's:
REM Make sure you have installed BOOST 
REM as well as defined environment variables for them.
REM See [doc\windowsInstall.txt] for details of this.

REM Also, you will need doxygen installed and in your path
REM for the doxygen'ation to work
REM =========================================================

REM Call the enviornment variables script to setup the environment variables.
call environment_variables.cmd

REM Copy the common files that are the same between this batch file and build_dist batch file
set PIRCBOTCPP_COMMON_ROOT=%PIRCBOTCPP_DIST_DIR%
call copy_common_files.bat

echo compiling pircbot source code and samples This takes a while please be patient
%DOT_NET_HOME%\devenv.exe ..\vs7_dll\pircbotcpp.sln /rebuild release
%DOT_NET_HOME%\devenv.exe ..\..\src\samples\simple\simple.sln /rebuild release

echo copying all binaries to distro
xcopy %LIBS_BIN_DIR%\simple.exe %PIRCBOTCPP_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\pircbotcpp-mt.dll %PIRCBOTCPP_DIST_DIR%\bin\release /y
xcopy %LIBS_BIN_DIR%\pircbotcpp-mt.lib %PIRCBOTCPP_DIST_DIR%\bin\release /y

xcopy %MSVCRT71_DLL% %PIRCBOTCPP_DIST_DIR%\bin\release /y

REM Finally let us zip everything up with 7zip
%SEVEN_ZIP_BIN% a -tzip %PIRCBOTCPP_COMMON_ROOT%.zip %PIRCBOTCPP_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -ttar %PIRCBOTCPP_COMMON_ROOT%.tar %PIRCBOTCPP_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -tgzip %PIRCBOTCPP_COMMON_ROOT%.tar.gz %PIRCBOTCPP_COMMON_ROOT%.tar
del %PIRCBOTCPP_COMMON_ROOT%.tar

