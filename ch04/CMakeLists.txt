﻿# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#
add_executable(ch04 "ch04.cpp" "ch04.h")


# Set path to include files.
target_include_directories(ch04 PRIVATE ${INCLUDE_DIR})


# Used to output files into the correct directory.
add_compile_definitions(IMAGE_FILEPATH_AND_NAME="${CMAKE_CURRENT_BINARY_DIR}/RTIOW.png")