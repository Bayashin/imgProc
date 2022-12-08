cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11) 
project(main) 

find_package(OpenCV 4.4.0 REQUIRED) 

include_directories(${OpenCV_INCLUDE_DIRS}) 

file(GLOB SOURCES *.cpp) 

add_executable (main ${SOURCES}) 
target_link_libraries (main
   PRIVATE ${OpenCV_LIBS}
)