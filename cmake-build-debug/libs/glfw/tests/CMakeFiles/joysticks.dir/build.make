# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\birdi\CLionProjects\Daybreak

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

# Include any dependencies generated for this target.
include libs/glfw/tests/CMakeFiles/joysticks.dir/depend.make

# Include the progress variables for this target.
include libs/glfw/tests/CMakeFiles/joysticks.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glfw/tests/CMakeFiles/joysticks.dir/flags.make

libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.obj: libs/glfw/tests/CMakeFiles/joysticks.dir/flags.make
libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.obj: libs/glfw/tests/CMakeFiles/joysticks.dir/includes_C.rsp
libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.obj: ../libs/glfw/tests/joysticks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.obj"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\joysticks.dir\joysticks.c.obj   -c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\joysticks.c

libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/joysticks.c.i"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\joysticks.c > CMakeFiles\joysticks.dir\joysticks.c.i

libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/joysticks.c.s"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\joysticks.c -o CMakeFiles\joysticks.dir\joysticks.c.s

libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.obj: libs/glfw/tests/CMakeFiles/joysticks.dir/flags.make
libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.obj: libs/glfw/tests/CMakeFiles/joysticks.dir/includes_C.rsp
libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.obj: ../libs/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.obj"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\joysticks.dir\__\deps\glad.c.obj   -c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad.c

libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/joysticks.dir/__/deps/glad.c.i"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad.c > CMakeFiles\joysticks.dir\__\deps\glad.c.i

libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/joysticks.dir/__/deps/glad.c.s"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad.c -o CMakeFiles\joysticks.dir\__\deps\glad.c.s

# Object files for target joysticks
joysticks_OBJECTS = \
"CMakeFiles/joysticks.dir/joysticks.c.obj" \
"CMakeFiles/joysticks.dir/__/deps/glad.c.obj"

# External object files for target joysticks
joysticks_EXTERNAL_OBJECTS =

libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/joysticks.c.obj
libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/__/deps/glad.c.obj
libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/build.make
libs/glfw/tests/joysticks.exe: libs/glfw/src/libglfw3.a
libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/linklibs.rsp
libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/objects1.rsp
libs/glfw/tests/joysticks.exe: libs/glfw/tests/CMakeFiles/joysticks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable joysticks.exe"
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\joysticks.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glfw/tests/CMakeFiles/joysticks.dir/build: libs/glfw/tests/joysticks.exe

.PHONY : libs/glfw/tests/CMakeFiles/joysticks.dir/build

libs/glfw/tests/CMakeFiles/joysticks.dir/clean:
	cd /d C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests && $(CMAKE_COMMAND) -P CMakeFiles\joysticks.dir\cmake_clean.cmake
.PHONY : libs/glfw/tests/CMakeFiles/joysticks.dir/clean

libs/glfw/tests/CMakeFiles/joysticks.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\birdi\CLionProjects\Daybreak C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests\CMakeFiles\joysticks.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glfw/tests/CMakeFiles/joysticks.dir/depend

