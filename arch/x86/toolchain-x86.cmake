set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_COMPILER "i686-elf-gcc")
set(CMAKE_CXX_COMPILER "i686-elf-g++")
set(CMAKE_ASM_NASM_COMPILER "nasm")
set(CMAKE_LINKER "i686-elf-ld")

set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_LINKER} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_LINKER} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_CXX_FLAGS_INIT "-std=c++20 -m32 -Wall -ffreestanding -nostdinc -nostdlib -fno-exceptions -fno-rtti -fno-threadsafe-statics -mgeneral-regs-only")
set(CMAKE_C_FLAGS_INIT "-m32 -Wall -ffreestanding -nostdinc -nostdlib")
set(CMAKE_ASM_NASM_FLAGS_INIT "-f elf32")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0")
set(CMAKE_ASM_NASM_FLAGS_DEBUG_INIT "-g")

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2 -DNDEBUG")

set(OS_LINKER_FLAGS
    "-T${CMAKE_SOURCE_DIR}/kernel/linker.ld"
    "-m" "elf_i386"
    "-nostdlib"
    "-static"
    "--nmagic"
)
