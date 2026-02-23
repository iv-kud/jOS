set(LIBRARY_NAME bitset)
FILE(GLOB_RECURSE BITSET_SRC *.cpp *.c)
FILE(GLOB_RECURSE BITSET_HDR *.h *.hpp)

if(BITSET_SRC)
    add_library(${LIBRARY_NAME} STATIC ${BITSET_SRC} ${BITSET_HDR})
    target_include_directories(${LIBRARY_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    message(STATUS "No bitset library sources found")
endif()
