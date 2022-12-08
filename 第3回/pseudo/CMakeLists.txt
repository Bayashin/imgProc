cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(03_02_pseudo_k21099)

find_package(OpenCV 4.5.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (03_02_pseudo_k21099 ${SOURCES})
target_link_libraries (03_02_pseudo_k21099
	PRIVATE ${OpenCV_LIBS}
)

