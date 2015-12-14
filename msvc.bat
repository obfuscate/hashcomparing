@echo off

rem %1 - version of vs: vc2008, vc2010, vc2012, etc.

set "Version=vs2013"

if not "%1" == "" (
  set "Version=%1"
)

"build%Version%/HashComparing.sln"
