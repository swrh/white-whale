# CMakeLists.txt

cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project (white-whale)

# Enable C++11
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Load Boost compilation parameters.
find_package (Boost 1.54.0 REQUIRED COMPONENTS
	unit_test_framework
	)

# Source files.
file (GLOB_RECURSE COMMON_SOURCES
	./include/*.hpp
	./src/*.cpp
	./src/*.hpp
	)

file (GLOB_RECURSE TEST_SOURCES
	./test/*.cpp
	)

# ww-test definitions
add_executable (ww-test
	${COMMON_SOURCES}
	${TEST_SOURCES}
	./test.cpp
	)

target_link_libraries (ww-test
	${Boost_LIBRARIES}
	)

target_include_directories(ww-test PUBLIC
	./include
	${Boost_INCLUDE_DIRS}
	)

target_compile_options(ww-test PUBLIC
	${Boost_CFLAGS_OTHER}
	)
