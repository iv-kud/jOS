cmake_minimum_required(VERSION 3.16)
project(JustOS VERSION 0.1 LANGUAGES C CXX)

set(ARCH "x86" CACHE STRING "Target architecture (x86, arm, etc)")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

string(TOLOWER "${ARCH}" ARCH_LOWER)

if(ARCH_LOWER STREQUAL "x86")
    set(TARGET_NAME "${PROJECT_NAME}-x86")
    message(STATUS "Building for x86 architecture")
elseif(ARCH_LOWER STREQUAL "arm")
    #TODO: Add build for ARM arch
else()
    message(FATAL_ERROR "Unknown architecture: ${ARCH_LOWER}. Supported: x86, arm")
endif()

if (NOT DEFINED ENABLE_CLANG_FORMATTING)
    set(ENABLE_CLANG_FORMATTING ON)
endif()
include(clang-format.cmake)


add_subdirectory(lib/)

set(CPP_SOURCES
    kernel/kernel.cpp
    arch/x86/core/portIO/port.cpp
    arch/x86/table/GDT/global_descriptor.cpp
    arch/x86/VGA/vgadriver.cpp
)

set(ASM_SOURCES
    arch/x86/boot/boot.asm
    arch/x86/core/portIO/port.asm
    arch/x86/table/flush_table.asm
)

set(HEDER_SOURCES
    arch/x86/core/chars/chars_code.h
    arch/x86/core/chars/vga_modecolor.h
    arch/x86/core/portIO/port.h
    arch/x86/core/types/data_types.h
    arch/x86/table/segment_descriptor.h
    arch/x86/table/GDT/global_descriptor.h
    arch/x86/VGA/vgadriver.h
)

set(ALL_SOURCES
    ${CPP_SOURCES}
    ${ASM_SOURCES}
    ${HEDER_SOURCES}
)

if(ARCH_LOWER STREQUAL "x86")
    enable_language(ASM_NASM)
    add_executable(${TARGET_NAME}  ${ALL_SOURCES})
    execute_process(
        COMMAND i686-elf-gcc -print-libgcc-file-name
        OUTPUT_VARIABLE LIBGCC_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    get_filename_component(LIBGCC_DIR ${LIBGCC_PATH} DIRECTORY)
    message(STATUS "LibGCC directory: ${LIBGCC_DIR}")
    target_link_options(${TARGET_NAME} PRIVATE ${OS_LINKER_FLAGS})
    target_link_libraries(${TARGET_NAME} PRIVATE
        display
        bitset
        -L${LIBGCC_DIR}
        -lgcc
    )
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/arch/x86
    )

endif()


add_custom_target(iso
    DEPENDS ${TARGET_NAME}
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp ${TARGET_NAME} isodir/boot/${TARGET_NAME}
    COMMAND cp ${CMAKE_SOURCE_DIR}/grub.cfg isodir/boot/grub/
    COMMAND grub-mkrescue -o ${TARGET_NAME}.iso isodir
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Creating ISO image"
)

add_custom_target(run
    DEPENDS iso
    COMMAND qemu-system-i386 -cdrom ${TARGET_NAME}.iso
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Starting QEMU"
)

add_custom_target(debug
    COMMAND qemu-system-i386 -cdrom ${CMAKE_BINARY_DIR}/${TARGET_NAME}.iso -vga std -S -gdb tcp:127.0.0.1:1234
    COMMENT "Starting QEMU in debug mode (GDB server: 1234)"
    DEPENDS iso
)

add_custom_target(gdb
    COMMAND gdb -ex "target remote :1234" -ex "break main" -ex "c" ${CMAKE_BINARY_DIR}/JustOS-x86
    COMMENT "Connecting GDB to QEMU"
)
