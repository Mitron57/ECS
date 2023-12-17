cmake_minimum_required(VERSION 3.20)
project(ECS)

add_library(ECS INTERFACE)
target_include_directories(ECS INTERFACE include src)
