# CMakeList.txt : CMake project for RT_Weekend, include source and define
# project specific logic here.
#
add_executable(chapter "chapter.cpp" "sphere.h" "utility.h"
	"vec3.h" "ray.h" "interval.h"
	"camera.h" "camera.cpp" 
	"hittable.h" "hittable_list.h" "hittable_list.cpp" 
	"material.h" "color.h"
)

# Set path to include files.
target_include_directories(chapter PRIVATE ${INCLUDE_DIR})


# Used to output files into the correct directory.
add_compile_definitions(IMAGE_FILEPATH_AND_NAME="${CMAKE_CURRENT_BINARY_DIR}/RTIOW.png")