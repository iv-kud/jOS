add_library(core_types STATIC
    base.cpp
)

target_include_directories(core_types PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

install(TARGETS core_types
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(FILES ${CMAKE_SOURCE_DIR}/include/core/types/base.hpp
    DESTINATION include/core/types
)

target_compile_options(core_types PRIVATE
    -ffreestanding
    -nostdlib
    -m32
    -fno-exceptions
)