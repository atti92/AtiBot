@echo off
REM =========================================================
REM Copies common files for both distribution and source 
REM Set the variable PIRCBOTCPP_COMMON_ROOT before calling this script

echo creating dist directory
mkdir %PIRCBOTCPP_COMMON_ROOT%

echo creating bin directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\bin

echo creating doc directories
mkdir %PIRCBOTCPP_COMMON_ROOT%\doc
mkdir %PIRCBOTCPP_COMMON_ROOT%\doc\api
mkdir %PIRCBOTCPP_COMMON_ROOT%\doc\api+samples

echo creating include directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\include

echo creating include\pircbot directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\include\pircbot

echo creating src directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\src

echo creating src\samples directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\src\samples

echo creating src\samples\simple directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\src\samples\simple

echo creating release directory
mkdir %PIRCBOTCPP_COMMON_ROOT%\bin\release

echo copying header files
xcopy %PIRCBOTCPP_ROOT%\include\pircbot\*.h %PIRCBOTCPP_COMMON_ROOT%\include\pircbot /y

echo creating doxygen of source code
cd %PIRCBOTCPP_ROOT%\doc\doxygen
call doxy_it.bat
cd %PIRCBOTCPP_ROOT%\build_files\vs7_build_bin_dist 

echo copying doxygen to distro
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\api %PIRCBOTCPP_COMMON_ROOT%\doc\api /y /E
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\api+samples %PIRCBOTCPP_COMMON_ROOT%\doc\api+samples /y /E

echo copying the Readme's and other relivant files
xcopy %PIRCBOTCPP_ROOT%\Authors.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\license.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\ASIO_LICENSE_1_0.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\README.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\ReleaseNotes.txt %PIRCBOTCPP_COMMON_ROOT% /y
xcopy %PIRCBOTCPP_ROOT%\bin\release\README.txt %PIRCBOTCPP_COMMON_ROOT%\bin\release /y
xcopy %PIRCBOTCPP_ROOT%\src\samples\README.txt %PIRCBOTCPP_COMMON_ROOT%\src\samples /y
xcopy %PIRCBOTCPP_ROOT%\src\samples\simple\README.txt %PIRCBOTCPP_COMMON_ROOT%\src\samples\simple /y
xcopy %PIRCBOTCPP_ROOT%\include\README.txt %PIRCBOTCPP_COMMON_ROOT%\include /y
xcopy %PIRCBOTCPP_ROOT%\doc\doxygen\README.txt %PIRCBOTCPP_COMMON_ROOT%\doc /y

echo copying simple sample
xcopy %PIRCBOTCPP_ROOT%\src\samples\simple\simple.cpp %PIRCBOTCPP_COMMON_ROOT%\src\samples\simple /y
xcopy %PIRCBOTCPP_ROOT%\src\samples\simple\simple.sln %PIRCBOTCPP_COMMON_ROOT%\src\samples\simple /y
xcopy %PIRCBOTCPP_ROOT%\src\samples\simple\simple.vcproj %PIRCBOTCPP_COMMON_ROOT%\src\samples\simple /y

