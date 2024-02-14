# Top-level CMake project file
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


# Project settings.
# ... Create project and set language.
project ("RT_Weekend" LANGUAGES C CXX)
# ... Set language standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Fetch content.
include(FetchContent)

# ... Get STB
FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git)

# ... Complete all fetches.
FetchContent_MakeAvailable(stb)

# Finalize STB ... Only need 1 stb file, copied to include folder (avoids polluting include space).
file(COPY "${FETCHCONTENT_BASE_DIR}/stb-src/stb_image_write.h" DESTINATION "${CMAKE_BINARY_DIR}/inc")


# Set include directory.
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/common" "${CMAKE_BINARY_DIR}/inc")


# Create static library.
add_subdirectory("common")


# Include sub-projects.
add_subdirectory ("ch02")
add_subdirectory ("ch03")
add_subdirectory ("ch04")
add_subdirectory ("ch05")
add_subdirectory ("ch06")
add_subdirectory ("ch07")
add_subdirectory ("ch08")
add_subdirectory ("ch09")


# Make most recent the default project.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ch09)