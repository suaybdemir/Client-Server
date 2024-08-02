cmake_minimum_required(VERSION 3.0)
project(main)

find_package(main REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main Boost::headers)
