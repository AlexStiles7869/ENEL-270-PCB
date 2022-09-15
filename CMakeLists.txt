cmake_minimum_required(VERSION 3.23)
project(Software C)

set(CMAKE_C_STANDARD 99)

add_executable(Software main.c mosfet.c config.c config.h)
