cmake_minimum_required(VERSION 2.8.9)
project(ptracer)

include_directories(include)

file(GLOB SOURCES "source/*cpp")

add_executable(pathtracer ${SOURCES})
