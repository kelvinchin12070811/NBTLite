cmake_minimum_required(VERSION 2.8)
project(NBTLite)

set(CMAKE_CXX_STANDARD 17)
set(SDK_DIR "" CACHE FILEPATH "Path to root of additional dependencies.")
add_subdirectory(NBTLite)
add_subdirectory(Tester)