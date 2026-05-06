set(LIBRARY_NAME display)

set(DISPLAY_SRC
    display.cpp
)

set(DISPLAY_HDR
    display.h
    log_level.h
)

add_library(${LIBRARY_NAME} STATIC
    ${DISPLAY_SRC}
    ${DISPLAY_HDR}
)

target_include_directories(display
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/arch/x86
        ${CMAKE_SOURCE_DIR}/arch/x86/core
)
