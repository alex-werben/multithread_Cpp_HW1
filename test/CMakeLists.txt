project(test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_run test.cpp)

target_link_libraries(test_run exceptionSafeInvoke_lib)
target_link_libraries(test_run gtest gtest_main)