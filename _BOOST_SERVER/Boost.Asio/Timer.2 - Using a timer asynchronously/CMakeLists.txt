# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ExampleProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost libraries
find_package(Boost REQUIRED)

# Add the executable
add_executable(main main.cpp)

# Link Boost libraries
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(main ${Boost_LIBRARIES})
endif()
