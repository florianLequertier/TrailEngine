# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\programmation\repo_git\TrailEngine\trailEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\programmation\repo_git\TrailEngine\trailEngine-build

# Include any dependencies generated for this target.
include TP_template/CMakeFiles/TP_template_SDLtemplate.dir/depend.make

# Include the progress variables for this target.
include TP_template/CMakeFiles/TP_template_SDLtemplate.dir/progress.make

# Include the compile flags for this target's objects.
include TP_template/CMakeFiles/TP_template_SDLtemplate.dir/flags.make

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/flags.make
TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/includes_CXX.rsp
TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj: D:/programmation/repo_git/TrailEngine/trailEngine/TP_template/SDLtemplate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\programmation\repo_git\TrailEngine\trailEngine-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj"
	cd /d D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template && D:\Qt\Tools\mingw492_32\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TP_template_SDLtemplate.dir\SDLtemplate.cpp.obj -c D:\programmation\repo_git\TrailEngine\trailEngine\TP_template\SDLtemplate.cpp

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.i"
	cd /d D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template && D:\Qt\Tools\mingw492_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\programmation\repo_git\TrailEngine\trailEngine\TP_template\SDLtemplate.cpp > CMakeFiles\TP_template_SDLtemplate.dir\SDLtemplate.cpp.i

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.s"
	cd /d D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template && D:\Qt\Tools\mingw492_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\programmation\repo_git\TrailEngine\trailEngine\TP_template\SDLtemplate.cpp -o CMakeFiles\TP_template_SDLtemplate.dir\SDLtemplate.cpp.s

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.requires:

.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.requires

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.provides: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.requires
	$(MAKE) -f TP_template\CMakeFiles\TP_template_SDLtemplate.dir\build.make TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.provides.build
.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.provides

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.provides.build: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj


# Object files for target TP_template_SDLtemplate
TP_template_SDLtemplate_OBJECTS = \
"CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj"

# External object files for target TP_template_SDLtemplate
TP_template_SDLtemplate_EXTERNAL_OBJECTS =

TP_template/TP_template_SDLtemplate.exe: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj
TP_template/TP_template_SDLtemplate.exe: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/build.make
TP_template/TP_template_SDLtemplate.exe: glimac/libglimac.a
TP_template/TP_template_SDLtemplate.exe: D:/programmation/repo_git/TrailEngine/trailEngine/third-party/lib/x86/libSDLmain.a
TP_template/TP_template_SDLtemplate.exe: D:/programmation/repo_git/TrailEngine/trailEngine/third-party/lib/x86/libSDL.dll.a
TP_template/TP_template_SDLtemplate.exe: D:/programmation/repo_git/TrailEngine/trailEngine/third-party/lib/x86/libglew32.dll.a
TP_template/TP_template_SDLtemplate.exe: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/linklibs.rsp
TP_template/TP_template_SDLtemplate.exe: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/objects1.rsp
TP_template/TP_template_SDLtemplate.exe: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\programmation\repo_git\TrailEngine\trailEngine-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP_template_SDLtemplate.exe"
	cd /d D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TP_template_SDLtemplate.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_template/CMakeFiles/TP_template_SDLtemplate.dir/build: TP_template/TP_template_SDLtemplate.exe

.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/build

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/requires: TP_template/CMakeFiles/TP_template_SDLtemplate.dir/SDLtemplate.cpp.obj.requires

.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/requires

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/clean:
	cd /d D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template && $(CMAKE_COMMAND) -P CMakeFiles\TP_template_SDLtemplate.dir\cmake_clean.cmake
.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/clean

TP_template/CMakeFiles/TP_template_SDLtemplate.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\programmation\repo_git\TrailEngine\trailEngine D:\programmation\repo_git\TrailEngine\trailEngine\TP_template D:\programmation\repo_git\TrailEngine\trailEngine-build D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template D:\programmation\repo_git\TrailEngine\trailEngine-build\TP_template\CMakeFiles\TP_template_SDLtemplate.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : TP_template/CMakeFiles/TP_template_SDLtemplate.dir/depend

