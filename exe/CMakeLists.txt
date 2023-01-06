project(exceptionSafeInvoke_app)

set(EXE_SOURCES
        main.cpp
)

add_executable(invoke ${EXE_SOURCES})

target_link_libraries(invoke PRIVATE exceptionSafeInvoke_lib)
set_target_properties(invoke PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
