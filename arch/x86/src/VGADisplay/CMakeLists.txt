add_library(vga_display STATIC Display.cpp)

target_include_directories(vga_display PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

install(FILES ${CMAKE_SOURCE_DIR}/include/arch/x86/VGADisplay/Display.hpp
    DESTINATION include/arch/x86/VGADisplay
)

install(TARGETS vga_display
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

target_compile_options(vga_display PRIVATE
    -ffreestanding
    -nostdlib
    -m32
    -fno-exceptions
)