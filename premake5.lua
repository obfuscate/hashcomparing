-- premakefile.lua
-- TODO : Rewrite prebuild commands
local action				= _ACTION or ""
local BuildFolder			= "build" .. action
local SourceFolder			= "Source"

-- Setup names of solution and projects
local SlnName					= "HashComparing"
local BaseProjName				= SlnName

-- Setup solution
solution (SlnName)
	configurations { "Debug", "Release", "DebugLib", "ReleaseLib", "DebugDLL", "ReleaseDLL"}
	platforms { "x32", "x64" }
	location(BuildFolder)
	toolset "v120"
	startproject (BaseProjName)

project (BaseProjName)
	targetname (BaseProjName)
	language "C++"
	flags {"Unicode"}
	kind "ConsoleApp"
	
	includedirs
	{
		(SourceFolder)
	}


	files
	{
		(SourceFolder .. "/**.h"),
		(SourceFolder .. "/**.cpp")
	}

	pchheader("Stdafx.h")
	pchsource(SourceFolder .. "/Stdafx.cpp")

	configuration "x32"
		targetdir ("Win32")
		debugdir  ("Win32")

	configuration "x64"
		targetdir ("Win64")
		debugdir  ("Win64")

	configuration "Debug"
		targetsuffix "_d"
		defines "_DEBUG"
		flags {"Symbols"}

	configuration "Release"
		defines "NDEBUG"
		flags {"OptimizeSize"}

if _ACTION == "clean" then
	os.rmdir(BuildFolder)
end