set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(CMAKE_C_COMPILER "/usr/bin/i686-elf-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/i686-elf-g++")
set(CMAKE_ASM_COMPILER "/usr/bin/nasm")
set(CMAKE_LINKER "/usr/bin/i686-elf-ld")
set(CMAKE_AR "/usr/bin/i686-elf-ar")

set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -m32" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-ffreestanding -nostdlib -m32 -fno-exceptions -fno-rtti" CACHE STRING "")
set(CMAKE_ASM_NASM_FLAGS "-f elf32" CACHE STRING "")