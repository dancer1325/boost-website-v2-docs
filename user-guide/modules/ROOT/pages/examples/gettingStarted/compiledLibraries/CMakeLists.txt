cmake_minimum_required(VERSION 3.8...3.31)
project(MyProject)

find_package(Boost REQUIRED COMPONENTS json)
add_executable(MyProject example.cpp)

target_link_libraries(MyProject Boost::json)
# Reason:
#   Boost::json       compiled library    -> you need to link