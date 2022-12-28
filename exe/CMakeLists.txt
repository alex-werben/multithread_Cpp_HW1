project(exceptionSafeInvoke_app)

set(EXE_SOURCES
        main.cpp
)

add_executable(invoke ${EXE_SOURCES})

target_link_libraries(invoke PRIVATE exceptionSafeInvoke_lib)
set_target_properties(invoke PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#message(STATUS ${CMAKE_SOURCE_DIR} ${SOME_VAL})
#message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(sum_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

#SET(SOME_VAL2 dfjkdsfjk)
