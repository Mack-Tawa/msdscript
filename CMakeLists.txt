cmake_minimum_required(VERSION 3.24)
project(clion_bull)

set(CMAKE_CXX_STANDARD 17)

add_executable(clion_bull main.cpp cmdline.cpp Expr.cpp expTest.cpp Parse.cpp val.cpp pointer.h Env.h)
