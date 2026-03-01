add_library(bitset OBJECT)

target_include_directories(bitset
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB BITSET_HEADERS *.hpp)

target_sources(bitset
    PRIVATE
        ${BITSET_HEADERS}
)
