project(exceptionSafeInvoke_library)

set(LIB_SRC
    exceptionSafeInvoke.cpp
)

add_library(exceptionSafeInvoke_lib STATIC ${LIB_SRC})


message(STATUS ${CMAKE_SOURCE_DIR})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(exceptionSafeInvoke_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

