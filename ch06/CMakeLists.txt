﻿# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#
add_executable(ch06 "ch06.cpp" )


# Set path to include files.
target_include_directories(ch06 PRIVATE ${INCLUDE_DIR})


# Add static library.
target_link_libraries(ch06 HittableList)


# Used to output files into the correct directory.
add_compile_definitions(IMAGE_FILEPATH_AND_NAME="${CMAKE_CURRENT_BINARY_DIR}/RTIOW.png")