cmake_minimum_required(VERSION 3.21)
project(MyBNOT)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(geogram)
include(glm)

add_executable(MyBNOT main.cpp)
target_link_libraries(MyBNOT geogram exploragram)

add_executable(myRank1 myRank1.cpp)
target_link_libraries(myRank1 glm)

