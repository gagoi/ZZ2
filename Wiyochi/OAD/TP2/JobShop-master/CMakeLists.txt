cmake_minimum_required(VERSION 3.5)
project(JobShop)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -stdlib=libc++ ")

file(GLOB_RECURSE HPP_FILES *.hpp )
file(GLOB_RECURSE CPP_FILES *.cpp)
set(SOURCE_FILES ${HPP_FILES} ${CPP_FILES})

add_executable(JobShop ${SOURCE_FILES})