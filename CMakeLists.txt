# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Create project.
project ("RT_Weekend" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Setup the include and common directories.
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(COMMON_DIR "${PROJECT_SOURCE_DIR}/common")


# Get stb library.
include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/stb")

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_MakeAvailable(stb)

# ... Move only required files to include directory (avoid polluting global include list).
file(COPY "${FETCHCONTENT_BASE_DIR}/stb-src/stb_image_write.h" DESTINATION ${INCLUDE_DIR})

# ... Remove remaining unused files.
file(REMOVE_RECURSE "${PROJECT_SOURCE_DIR}/stb")


# Include sub-projects.
add_subdirectory ("ch02")
add_subdirectory ("ch03")
add_subdirectory ("ch04")
add_subdirectory ("ch05")


# Make most recent the default project.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ch05)
