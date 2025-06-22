cmake_minimum_required(VERSION 3.16)
project(jOS LANGUAGES C CXX ASM_NASM)
set(CMAKE_VERBOSE_MAKEFILE ON)
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

set(CMAKE_CXX_LINK_EXECUTABLE 
    "<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
)

target_include_directories(kernel PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

execute_process(
    COMMAND sh -c "i686-elf-gcc -print-libgcc-file-name"
    OUTPUT_VARIABLE LIBGCC_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(LIBGCC_DIR ${LIBGCC_PATH} DIRECTORY)
target_compile_options(kernel PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++20>
    $<$<COMPILE_LANGUAGE:CXX>:-m32>
    $<$<COMPILE_LANGUAGE:CXX>:-ffreestanding>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-nostdlib>
    $<$<COMPILE_LANGUAGE:CXX>:-g>
)

target_link_options(kernel PRIVATE
    -T${CMAKE_SOURCE_DIR}/kernel/linker.ld
    -nostdlib
    -static
    --nmagic
    -m elf_i386
)

target_link_libraries(kernel -L${LIBGCC_DIR} -lgcc)

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