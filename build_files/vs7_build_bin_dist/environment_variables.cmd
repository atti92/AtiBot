@echo OFF

REM =========================================================
REM These are the common enviornment variables of pircbotcpp
REM All dos scripts in this directory should call this first to get the environment variables.
REM Change these to your likeing and to where all your appropriate tools and libraries are.

REM =====================================================================================================================================================================================
REM Change these to the right variables

REM Version of pircbotcpp you are creating
set PIRCBOTCPP_VER=1.4.4.1

REM Where you want the distribution and source code to be prodcued at
set PIRCBOTCPP_DIST_LOC=C:

REM Location of the Microsoft compiler
set DOT_NET_HOME="C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE"

REM Location of the msvcr71.dll to copy
set MSVCRT71_DLL="C:\Program Files\Microsoft Visual Studio .NET 2003\Visual Studio .NET Enterprise Architect 2003 - English\msvcr71.dll"

REM Location of the free zip program, 7Zip
set SEVEN_ZIP_BIN="C:\Program Files\7-Zip\7z"

REM Location of the dos2unix program needed for converting the autoconf files
set DOS_TO_UNIX_BIN="C:\Program Files\uddu\dos2unix.exe"

REM Probably don't need to change these.  These are hardcoded to what the current pircbotcpp directory structure is 
set PIRCBOTCPP_ROOT=..\..
set PIRCBOTCPP_DIST_DIR=%PIRCBOTCPP_DIST_LOC%\pircbotcpp-%PIRCBOTCPP_VER%
set PIRCBOTCPP_SOURCE_DIR=%PIRCBOTCPP_DIST_LOC%\pircbotcpp-src-%PIRCBOTCPP_VER%
set LIBS_BIN_DIR=%PIRCBOTCPP_ROOT%\bin\release



REM End of variables
REM =====================================================================================================================================================================================

echo.
echo environment variables
echo ====================
echo PIRCBOTCPP_ROOT:
echo %PIRCBOTCPP_ROOT%
echo.
echo LIBS_BIN_DIR:
echo %LIBS_BIN_DIR%
echo.
echo DOT_NET_HOME: 
echo %DOT_NET_HOME%
echo.
echo PIRCBOTCPP_VER:
echo %PIRCBOTCPP_VER%
echo.
echo BOOST_INCLUDE:
echo %BOOST_INCLUDE%
echo.
echo BOOST_LIB:
echo %BOOST_LIB%
echo.
echo BOOST_LIBD:
echo %BOOST_LIBD%
echo.
echo PIRCBOTCPP_DIST_LOC
echo %PIRCBOTCPP_DIST_LOC%
echo ====================
echo.
