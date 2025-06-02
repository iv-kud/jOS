cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(jOS LANGUAGES C CXX ASM_NASM)
include(toolchain.cmake)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)

enable_language(ASM_NASM)
add_library(boot OBJECT boot/boot.asm)

file(GLOB_RECURSE CXX_SOURCES 
    "*.cpp"
)

add_executable(kernel 
    kernel/kernel.cpp
    $<TARGET_OBJECTS:boot>
    ${CXX_SOURCES}
)

target_include_directories(kernel PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(kernel PRIVATE
    -m32
    -ffreestanding
    -fno-exceptions
    -fno-rtti
    -nostdlib
    -g
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
    COMMENT "Creating ISO image"
    DEPENDS kernel
)

add_custom_target(run
    COMMAND qemu-system-i386 -cdrom ${CMAKE_BINARY_DIR}/JustOS.iso -vga std
    COMMENT "Starting QEMU emulator"
    DEPENDS iso
)

add_custom_target(debug
    COMMAND qemu-system-i386 -cdrom ${CMAKE_BINARY_DIR}/JustOS.iso -vga std -S -gdb tcp::1234
    COMMENT "Starting QEMU in debug mode (GDB server: 1234)"
    DEPENDS iso
)

add_custom_target(gdb
    COMMAND gdb -ex "target remote :1234" -ex "break kernel_main" ${CMAKE_BINARY_DIR}/kernel
    COMMENT "Connecting GDB to QEMU"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)