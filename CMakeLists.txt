cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(jOS LANGUAGES C CXX ASM_NASM)
include(toolchain.cmake)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)

enable_language(ASM_NASM)
add_library(boot OBJECT boot/boot.asm)

add_subdirectory(arch/x86/src/core/types)
add_subdirectory(arch/x86/src/VGADisplay)

add_executable(kernel 
    kernel/kernel.cpp
    $<TARGET_OBJECTS:boot>
)

target_link_libraries(kernel PRIVATE core_types vga_display)

target_include_directories(kernel PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(kernel PRIVATE
    -m32
    -ffreestanding
    -fno-exceptions
    -fno-rtti
    -nostdlib
)

target_link_options(kernel PRIVATE
    -T${CMAKE_SOURCE_DIR}/kernel/linker.ld
    -nostdlib
    -Wl,-m,elf_i386
    -Wl,--nmagic
)

add_custom_target(iso ALL
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp ${CMAKE_BINARY_DIR}/kernel isodir/boot/kernel.bin
    COMMAND cp ${CMAKE_SOURCE_DIR}/grub.cfg isodir/boot/grub/
    COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/JustOS.iso isodir
    COMMENT "Creating bootable ISO image"
    DEPENDS kernel
)

add_custom_target(run
    COMMAND qemu-system-i386 -cdrom ${CMAKE_BINARY_DIR}/JustOS.iso -vga std
    COMMENT "Starting QEMU emulator"
    DEPENDS iso
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)