project(CompressiveTracking)

cmake_minimum_required(VERSION 2.6)

find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH bin)

INCLUDE_DIRECTORIES (${OpenCV_INCLUDE_DIRS})

add_executable(main
	CompressiveTracker.h
	CompressiveTracker.cpp
	main.cpp
	)

target_link_libraries(main ${OpenCV_LIBS})
