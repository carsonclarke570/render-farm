# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
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
include libs\glfw\tests\CMakeFiles\gamma.dir\depend.make

# Include the progress variables for this target.
include libs\glfw\tests\CMakeFiles\gamma.dir\progress.make

# Include the compile flags for this target's objects.
include libs\glfw\tests\CMakeFiles\gamma.dir\flags.make

libs\glfw\tests\CMakeFiles\gamma.dir\gamma.c.obj: libs\glfw\tests\CMakeFiles\gamma.dir\flags.make
libs\glfw\tests\CMakeFiles\gamma.dir\gamma.c.obj: ..\libs\glfw\tests\gamma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/glfw/tests/CMakeFiles/gamma.dir/gamma.c.obj"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\gamma.dir\gamma.c.obj /FdCMakeFiles\gamma.dir\ /FS -c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\gamma.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

libs\glfw\tests\CMakeFiles\gamma.dir\gamma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/gamma.c.i"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe > CMakeFiles\gamma.dir\gamma.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\gamma.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

libs\glfw\tests\CMakeFiles\gamma.dir\gamma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/gamma.c.s"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\gamma.dir\gamma.c.s /c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests\gamma.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

libs\glfw\tests\CMakeFiles\gamma.dir\__\deps\glad_gl.c.obj: libs\glfw\tests\CMakeFiles\gamma.dir\flags.make
libs\glfw\tests\CMakeFiles\gamma.dir\__\deps\glad_gl.c.obj: ..\libs\glfw\deps\glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\gamma.dir\__\deps\glad_gl.c.obj /FdCMakeFiles\gamma.dir\ /FS -c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad_gl.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

libs\glfw\tests\CMakeFiles\gamma.dir\__\deps\glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/__/deps/glad_gl.c.i"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe > CMakeFiles\gamma.dir\__\deps\glad_gl.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad_gl.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

libs\glfw\tests\CMakeFiles\gamma.dir\__\deps\glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/__/deps/glad_gl.c.s"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\gamma.dir\__\deps\glad_gl.c.s /c C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\deps\glad_gl.c
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

# Object files for target gamma
gamma_OBJECTS = \
"CMakeFiles\gamma.dir\gamma.c.obj" \
"CMakeFiles\gamma.dir\__\deps\glad_gl.c.obj"

# External object files for target gamma
gamma_EXTERNAL_OBJECTS =

libs\glfw\tests\gamma.exe: libs\glfw\tests\CMakeFiles\gamma.dir\gamma.c.obj
libs\glfw\tests\gamma.exe: libs\glfw\tests\CMakeFiles\gamma.dir\__\deps\glad_gl.c.obj
libs\glfw\tests\gamma.exe: libs\glfw\tests\CMakeFiles\gamma.dir\build.make
libs\glfw\tests\gamma.exe: libs\glfw\src\glfw3d.lib
libs\glfw\tests\gamma.exe: libs\glfw\tests\CMakeFiles\gamma.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gamma.exe"
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	"C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\gamma.dir --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\gamma.dir\objects1.rsp @<<
 /out:gamma.exe /implib:gamma.lib /pdb:C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests\gamma.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:windows /ENTRY:mainCRTStartup ..\src\glfw3d.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug

# Rule to build all files generated by this target.
libs\glfw\tests\CMakeFiles\gamma.dir\build: libs\glfw\tests\gamma.exe

.PHONY : libs\glfw\tests\CMakeFiles\gamma.dir\build

libs\glfw\tests\CMakeFiles\gamma.dir\clean:
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests
	$(CMAKE_COMMAND) -P CMakeFiles\gamma.dir\cmake_clean.cmake
	cd C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug
.PHONY : libs\glfw\tests\CMakeFiles\gamma.dir\clean

libs\glfw\tests\CMakeFiles\gamma.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\birdi\CLionProjects\Daybreak C:\Users\birdi\CLionProjects\Daybreak\libs\glfw\tests C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests C:\Users\birdi\CLionProjects\Daybreak\cmake-build-debug\libs\glfw\tests\CMakeFiles\gamma.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : libs\glfw\tests\CMakeFiles\gamma.dir\depend

