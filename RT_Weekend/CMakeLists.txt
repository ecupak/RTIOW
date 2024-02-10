# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#

# Setup the include directory.
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

# Get external libraries.
include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${INCLUDE_DIR})

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_MakeAvailable(stb)


# Add source to this project's executable.
add_executable(RT_Weekend "RT_Weekend.cpp" "RT_Weekend.h" "vec3.h" "color.h" "ray.h")


# Include external headers / files.
target_include_directories(RT_Weekend PRIVATE "${INCLUDE_DIR}/stb-src")