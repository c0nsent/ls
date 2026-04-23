cmake_minimum_required(VERSION 4.3)
project(ls)

set(CMAKE_CXX_STANDARD 23)

add_executable(ls
        basic-types-aliases.hpp
        cli-parser.cc cli-parser.hpp
        main.cpp)
