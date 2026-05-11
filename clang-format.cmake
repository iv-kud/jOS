
if (ENABLE_CLANG_FORMATTING)
    find_program(CLANG_FORMAT_EXECUTABLE clang-format REQUIRED)

    file(GLOB_RECURSE ALL_SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/arch/*.cpp
            ${CMAKE_SOURCE_DIR}/arch/*.h
            ${CMAKE_SOURCE_DIR}/kernel/*.hpp
            ${CMAKE_SOURCE_DIR}/kernel/*.cpp
            ${CMAKE_SOURCE_DIR}/lib/*.h
            ${CMAKE_SOURCE_DIR}/lib/*.hpp
            ${CMAKE_SOURCE_DIR}/lib/*.cpp
    )

    if (ALL_SOURCE_FILES)
        add_custom_target(
                clangformat
                ALL
                COMMAND ${CLANG_FORMAT_EXECUTABLE}
                -style=file
                -i
                ${ALL_SOURCE_FILES}
                COMMENT "Running clang-format"
                VERBATIM
        )
    endif()
endif()
