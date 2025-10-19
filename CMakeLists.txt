cmake_minimum_required(VERSION 3.10)

project(Prototype)

set(CMAKE_CXX_STANDARD 23)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
include(dependencies.cmake)

# Projects
add_subdirectory(src)
