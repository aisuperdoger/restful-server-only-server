# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/projects/restful-server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/projects/restful-server/build

# Include any dependencies generated for this target.
include CMakeFiles/pro.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pro.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pro.dir/flags.make

CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o: /home/ubuntu/projects/restful-server/src/http/FormDataParser.cpp
CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o -MF CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o.d -o CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o -c /home/ubuntu/projects/restful-server/src/http/FormDataParser.cpp

CMakeFiles/pro.dir/src/http/FormDataParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/http/FormDataParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/FormDataParser.cpp > CMakeFiles/pro.dir/src/http/FormDataParser.cpp.i

CMakeFiles/pro.dir/src/http/FormDataParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/http/FormDataParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/FormDataParser.cpp -o CMakeFiles/pro.dir/src/http/FormDataParser.cpp.s

CMakeFiles/pro.dir/src/http/binary_io.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/binary_io.cpp.o: /home/ubuntu/projects/restful-server/src/http/binary_io.cpp
CMakeFiles/pro.dir/src/http/binary_io.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pro.dir/src/http/binary_io.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/binary_io.cpp.o -MF CMakeFiles/pro.dir/src/http/binary_io.cpp.o.d -o CMakeFiles/pro.dir/src/http/binary_io.cpp.o -c /home/ubuntu/projects/restful-server/src/http/binary_io.cpp

CMakeFiles/pro.dir/src/http/binary_io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/http/binary_io.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/binary_io.cpp > CMakeFiles/pro.dir/src/http/binary_io.cpp.i

CMakeFiles/pro.dir/src/http/binary_io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/http/binary_io.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/binary_io.cpp -o CMakeFiles/pro.dir/src/http/binary_io.cpp.s

CMakeFiles/pro.dir/src/http/http_server.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/http_server.cpp.o: /home/ubuntu/projects/restful-server/src/http/http_server.cpp
CMakeFiles/pro.dir/src/http/http_server.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pro.dir/src/http/http_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/http_server.cpp.o -MF CMakeFiles/pro.dir/src/http/http_server.cpp.o.d -o CMakeFiles/pro.dir/src/http/http_server.cpp.o -c /home/ubuntu/projects/restful-server/src/http/http_server.cpp

CMakeFiles/pro.dir/src/http/http_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/http/http_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/http_server.cpp > CMakeFiles/pro.dir/src/http/http_server.cpp.i

CMakeFiles/pro.dir/src/http/http_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/http/http_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/http_server.cpp -o CMakeFiles/pro.dir/src/http/http_server.cpp.s

CMakeFiles/pro.dir/src/http/ilogger.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/ilogger.cpp.o: /home/ubuntu/projects/restful-server/src/http/ilogger.cpp
CMakeFiles/pro.dir/src/http/ilogger.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pro.dir/src/http/ilogger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/ilogger.cpp.o -MF CMakeFiles/pro.dir/src/http/ilogger.cpp.o.d -o CMakeFiles/pro.dir/src/http/ilogger.cpp.o -c /home/ubuntu/projects/restful-server/src/http/ilogger.cpp

CMakeFiles/pro.dir/src/http/ilogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/http/ilogger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/ilogger.cpp > CMakeFiles/pro.dir/src/http/ilogger.cpp.i

CMakeFiles/pro.dir/src/http/ilogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/http/ilogger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/ilogger.cpp -o CMakeFiles/pro.dir/src/http/ilogger.cpp.s

CMakeFiles/pro.dir/src/http/json.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/json.cpp.o: /home/ubuntu/projects/restful-server/src/http/json.cpp
CMakeFiles/pro.dir/src/http/json.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/pro.dir/src/http/json.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/json.cpp.o -MF CMakeFiles/pro.dir/src/http/json.cpp.o.d -o CMakeFiles/pro.dir/src/http/json.cpp.o -c /home/ubuntu/projects/restful-server/src/http/json.cpp

CMakeFiles/pro.dir/src/http/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/http/json.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/json.cpp > CMakeFiles/pro.dir/src/http/json.cpp.i

CMakeFiles/pro.dir/src/http/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/http/json.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/json.cpp -o CMakeFiles/pro.dir/src/http/json.cpp.s

CMakeFiles/pro.dir/src/main.cpp.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/main.cpp.o: /home/ubuntu/projects/restful-server/src/main.cpp
CMakeFiles/pro.dir/src/main.cpp.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/pro.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pro.dir/src/main.cpp.o -MF CMakeFiles/pro.dir/src/main.cpp.o.d -o CMakeFiles/pro.dir/src/main.cpp.o -c /home/ubuntu/projects/restful-server/src/main.cpp

CMakeFiles/pro.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pro.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/projects/restful-server/src/main.cpp > CMakeFiles/pro.dir/src/main.cpp.i

CMakeFiles/pro.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pro.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/projects/restful-server/src/main.cpp -o CMakeFiles/pro.dir/src/main.cpp.s

CMakeFiles/pro.dir/src/http/mongoose.c.o: CMakeFiles/pro.dir/flags.make
CMakeFiles/pro.dir/src/http/mongoose.c.o: /home/ubuntu/projects/restful-server/src/http/mongoose.c
CMakeFiles/pro.dir/src/http/mongoose.c.o: CMakeFiles/pro.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/pro.dir/src/http/mongoose.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/pro.dir/src/http/mongoose.c.o -MF CMakeFiles/pro.dir/src/http/mongoose.c.o.d -o CMakeFiles/pro.dir/src/http/mongoose.c.o -c /home/ubuntu/projects/restful-server/src/http/mongoose.c

CMakeFiles/pro.dir/src/http/mongoose.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pro.dir/src/http/mongoose.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/projects/restful-server/src/http/mongoose.c > CMakeFiles/pro.dir/src/http/mongoose.c.i

CMakeFiles/pro.dir/src/http/mongoose.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pro.dir/src/http/mongoose.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/projects/restful-server/src/http/mongoose.c -o CMakeFiles/pro.dir/src/http/mongoose.c.s

# Object files for target pro
pro_OBJECTS = \
"CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o" \
"CMakeFiles/pro.dir/src/http/binary_io.cpp.o" \
"CMakeFiles/pro.dir/src/http/http_server.cpp.o" \
"CMakeFiles/pro.dir/src/http/ilogger.cpp.o" \
"CMakeFiles/pro.dir/src/http/json.cpp.o" \
"CMakeFiles/pro.dir/src/main.cpp.o" \
"CMakeFiles/pro.dir/src/http/mongoose.c.o"

# External object files for target pro
pro_EXTERNAL_OBJECTS =

/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/FormDataParser.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/binary_io.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/http_server.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/ilogger.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/json.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/main.cpp.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/src/http/mongoose.c.o
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/build.make
/home/ubuntu/projects/restful-server/workspace/pro: CMakeFiles/pro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/projects/restful-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable /home/ubuntu/projects/restful-server/workspace/pro"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pro.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pro.dir/build: /home/ubuntu/projects/restful-server/workspace/pro
.PHONY : CMakeFiles/pro.dir/build

CMakeFiles/pro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pro.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pro.dir/clean

CMakeFiles/pro.dir/depend:
	cd /home/ubuntu/projects/restful-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/projects/restful-server /home/ubuntu/projects/restful-server /home/ubuntu/projects/restful-server/build /home/ubuntu/projects/restful-server/build /home/ubuntu/projects/restful-server/build/CMakeFiles/pro.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pro.dir/depend

