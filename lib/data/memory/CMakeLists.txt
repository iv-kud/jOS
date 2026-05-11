set(LIBRARY_NAME memory)

add_library(${LIBRARY_NAME} OBJECT
    memory.h
    memory.cpp
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/arch/x86/core
)
