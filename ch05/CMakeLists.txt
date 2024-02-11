# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#
project ("Chapter_05" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ch05 "ch05.cpp" "ch05.h")


# Set path to included files.
target_include_directories(ch05 PRIVATE ${INCLUDE_DIR})
target_include_directories(ch05 PRIVATE ${COMMON_DIR})


# Used to output files into the correct directory.
add_compile_definitions(IMAGE_FILEPATH_AND_NAME="${CMAKE_CURRENT_BINARY_DIR}/RTIOW.png")