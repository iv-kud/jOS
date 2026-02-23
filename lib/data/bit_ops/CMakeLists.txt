set(LIBRARY_NAME bitset)
FILE(GLOB_RECURSE DISPLAY_SRC *.cpp *.c)
FILE(GLOB_RECURSE DISPLAY_HDR *.h *.hpp)

if(DISPLAY_SRC)
    add_library(${LIBRARY_NAME} STATIC ${DISPLAY_SRC} ${DISPLAY_HDR})
    target_include_directories(${LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    message(STATUS "No display library sources found")
endif()
