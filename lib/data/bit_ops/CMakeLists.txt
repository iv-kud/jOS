set(LIBRARY_NAME bitset)

add_library(${LIBRARY_NAME} OBJECT
    bitset.hpp
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC
        memory
)
