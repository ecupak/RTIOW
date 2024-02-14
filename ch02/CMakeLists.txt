# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#
add_executable(ch02 "ch02.cpp" "ch02.h")


# Set path to include files.
target_include_directories(ch02 PRIVATE ${INCLUDE_DIR})


# Used to output files into the correct directory.
add_compile_definitions(IMAGE_FILEPATH_AND_NAME="${CMAKE_CURRENT_BINARY_DIR}/RTIOW.png")