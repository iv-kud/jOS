cmake_minimum_required(VERSION 3.16)

set(ARCH "x86" CACHE STRING "Target architecture (x86, arm, etc)")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

string(TOLOWER "${ARCH}" ARCH_LOWER)

if(ARCH_LOWER STREQUAL "x86")
    set(TARGET_NAME "JustOS-X86")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arch/x86/toolchain-x86.cmake)
    message(STATUS "Building for x86 architecture")
elseif(ARCH_LOWER STREQUAL "arm")
    #TODO: Add build for ARM arch
else()
    message(FATAL_ERROR "Unknown architecture: ${ARCH_LOWER}. Supported: x86, arm")
endif()

project(JustOS VERSION 0.1 LANGUAGES C CXX)

enable_language(ASM_NASM)
add_executable(${TARGET_NAME})

execute_process(
    COMMAND i686-elf-gcc -print-libgcc-file-name
    OUTPUT_VARIABLE LIBGCC_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(LIBGCC_DIR ${LIBGCC_PATH} DIRECTORY)

target_sources(${TARGET_NAME} PUBLIC
    kernel/kernel.cpp
    arch/x86/boot/boot.asm
)

if(ARCH_LOWER STREQUAL "x86")
    message(STATUS "LibGCC directory: ${LIBGCC_DIR}")
    target_link_options(${TARGET_NAME} PRIVATE ${OS_LINKER_FLAGS})
    target_link_libraries(${TARGET_NAME} PRIVATE
        -L${LIBGCC_DIR}
        -lgcc
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
