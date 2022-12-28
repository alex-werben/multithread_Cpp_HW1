cmake_minimum_required(VERSION 3.24)
project(invoke)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/)
add_subdirectory(exe/)
add_subdirectory(Google_tests)
#add_executable(invoke exe/main.cpp include/exceptionSafeInvoke.h lib/exceptionSafeInvoke.cpp)
