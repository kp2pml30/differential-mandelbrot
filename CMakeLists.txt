cmake_minimum_required(VERSION 3.18)

project(differential-mandelbrot)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXCompilerFlag)
unset(supports_fast_math CACHE)
check_cxx_compiler_flag(-ffast-math supports_fast_math)
if (supports_fast_math)
	add_compile_options(-ffast-math)
else()
	message("No fast math")
endif()

configure_file(vert.glsl ${CMAKE_BINARY_DIR}/vert.glsl COPYONLY)
configure_file(frag.glsl ${CMAKE_BINARY_DIR}/vert.glsl COPYONLY)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(diff-mandelbrot main.cpp sliderwindow.cpp sliderwindow.ui)
target_link_libraries(diff-mandelbrot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(diff-mandelbrot PRIVATE glfw GLU "${GLEW_LIBRARIES}" ${OPENGL_LIBRARIES} "stdc++fs")

find_library(PThread pthread)
if (PThread)
	target_link_libraries(diff-mandelbrot PRIVATE  ${PThread})
endif()
