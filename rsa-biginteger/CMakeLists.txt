cmake_minimum_required(VERSION 3.6)
project(rsa_biginteger)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(rsa_biginteger ${SOURCE_FILES})