cmake_minimum_required(VERSION 3.5)

project(mems)

set(CMAKE_CXX_COMPILER clang++)

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -g -O2 -fno-omit-frame-pointer -Wno-unused-variable -fsanitize=address,undefined)

add_link_options(-fsanitize=address,undefined)

file(GLOB_RECURSE src src/mems/*.cpp)

add_executable(mems ${src} src/mems.cpp)
target_include_directories(mems PUBLIC src/)

add_executable(test ${src} src/test.cpp)
target_include_directories(test PUBLIC src/)
