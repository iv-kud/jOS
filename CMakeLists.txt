cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(jOS LANGUAGES C CXX ASM_NASM)

enable_language(ASM_NASM)
add_library(boot OBJECT boot/boot.asm)
add_executable(kernel kernel/kernel.cpp $<TARGET_OBJECTS:boot>)

target_compile_options(kernel PRIVATE
    "-m32"
    "-ffreestanding"
    "-fno-exceptions"
    "-fno-rtti"
    "-nostdlib"
)

target_link_options(kernel PRIVATE
    "-T${CMAKE_SOURCE_DIR}/kernel/linker.ld"
    "-nostdlib"
    "-Wl,-m,elf_i386"  
    "-Wl,--nmagic"
    "-Wl,--build-id=none"
)

add_custom_target(iso ALL 
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp kernel isodir/boot/kernel.bin
    COMMAND cp ../grub.cfg isodir/boot/grub/
    COMMAND grub-mkrescue -o JustOS.iso isodir
    COMMENT "Create ISO image"
)

add_custom_target(run 
    COMMAND qemu-system-i386 -cdrom JustOS.iso -vga std
    COMMENT "Start QEMU"
)