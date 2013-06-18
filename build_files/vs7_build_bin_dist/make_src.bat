@echo OFF

REM =========================================================
REM Creates the source directory of pircbotcpp

REM Call the enviornment variables script to setup the environment variables.
call environment_variables.cmd

REM Copy the common files that are the same between this batch file and build_dist batch file
set PIRCBOTCPP_COMMON_ROOT=%PIRCBOTCPP_SOURCE_DIR%
call copy_common_files.bat

REM Copy the remaining root files for a source distribution release
xcopy %PIRCBOTCPP_ROOT%\INSTALL.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\pircbotcpp.spec %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\dev-todo.txt %PIRCBOTCPP_COMMON_ROOT% /y

REM Copy the WindowsINSTALL.txt and the LinuxInstall.txt files
xcopy %PIRCBOTCPP_ROOT%\doc\*.txt %PIRCBOTCPP_COMMON_ROOT%\doc /y

REM Copy the remainder of the doxygen files
mkdir %PIRCBOTCPP_COMMON_ROOT%\doc\doxygen
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\*.bat %PIRCBOTCPP_COMMON_ROOT%\doc\doxygen /y
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\Doxyfile_* %PIRCBOTCPP_COMMON_ROOT%\doc\doxygen /y
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\README.txt %PIRCBOTCPP_COMMON_ROOT%\doc\doxygen /y 

REM Copy all the build_files since they will be needed for a source distribution
mkdir %PIRCBOTCPP_COMMON_ROOT%\build_files
xcopy %PIRCBOTCPP_ROOT%\build_files %PIRCBOTCPP_COMMON_ROOT%\build_files /y /E /exclude:excluded_files.txt

REM Copy implementation header files
mkdir %PIRCBOTCPP_COMMON_ROOT%\include\pircbot\impl
mkdir %PIRCBOTCPP_COMMON_ROOT%\include\asio
xcopy %PIRCBOTCPP_ROOT%\include\asio %PIRCBOTCPP_COMMON_ROOT%\include\asio /y /E
xcopy %PIRCBOTCPP_ROOT%\include\pircbot\impl\*.h %PIRCBOTCPP_COMMON_ROOT%\include\pircbot\impl /y
xcopy %PIRCBOTCPP_ROOT%\include\asio.hpp %PIRCBOTCPP_COMMON_ROOT%\include /y

REM Copy remainder of the source files
mkdir %PIRCBOTCPP_COMMON_ROOT%\src\pircbotcpp
xcopy %PIRCBOTCPP_ROOT%\src\pircbotcpp %PIRCBOTCPP_COMMON_ROOT%\src\pircbotcpp /y /E /exclude:excluded_files.txt

REM Dos2unix the autoconf files so they will build on Linux systems
for /r %PIRCBOTCPP_COMMON_ROOT%\build_files\autoconf %%i in (*.*) do %DOS_TO_UNIX_BIN% "%%i"


REM Finally let us zip everything up with 7zip
%SEVEN_ZIP_BIN% a -tzip %PIRCBOTCPP_COMMON_ROOT%.zip %PIRCBOTCPP_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -ttar %PIRCBOTCPP_COMMON_ROOT%.tar %PIRCBOTCPP_COMMON_ROOT%
%SEVEN_ZIP_BIN% a -tgzip %PIRCBOTCPP_COMMON_ROOT%.tar.gz %PIRCBOTCPP_COMMON_ROOT%.tar
del %PIRCBOTCPP_COMMON_ROOT%.tar


