project(exceptionSafeInvoke_test)

set(EXE_SOURCES
        test.cpp
        )

add_executable(exceptionSafeInvoke_test ${EXE_SOURCES})

target_link_libraries(exceptionSafeInvoke_test PRIVATE sum_lib)
set_target_properties(exceptionSafeInvoke_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#message(STATUS ${CMAKE_SOURCE_DIR} ${SOME_VAL})
#message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(sum_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

#SET(SOME_VAL2 dfjkdsfjk)
