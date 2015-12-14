@echo off

rem %1 - version of vs: vc2008, vc2010, vc2012, etc.
rem %2 - remove folders.
rem %3 - start solution 
set "Version=vs2013"

if not "%1" == "" (
  set "Version=%1"
)

if "%2" == "clean" (
  rmdir /S /Q "Win32"
  rmdir /S /Q "Win64"
  rmdir /S /Q "build%Version%"
)

premake5.exe %Version%

if "%3" == "start" (
  msvc.bat %Version%
)
