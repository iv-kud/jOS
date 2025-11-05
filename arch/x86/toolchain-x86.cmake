set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(CMAKE_C_COMPILER "i686-elf-gcc")
set(CMAKE_CXX_COMPILER "i686-elf-g++")
set(CMAKE_ASM_COMPILER "nasm")
set(CMAKE_LINKER "i686-elf-ld")

set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_LINKER} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_LINKER} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_CXX_FLAGS "-std=c++20 -m32 -Wall -ffreestanding -nostdinc -nostdlib -fno-rtti -mgeneral-regs-only")
set(CMAKE_C_FLAGS "-m32 -Wall -ffreestanding -nostdinc -nostdlib")
set(CMAKE_ASM_NASM_FLAGS "-f elf32")

set(OS_LINKER_FLAGS
    "-T${CMAKE_SOURCE_DIR}/kernel/linker.ld"
    "-m" "elf_i386"
    "-nostdlib"
    "-static"
    "--nmagic"
)

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)

if(BUILD_TYPE_UPPER STREQUAL "DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -g")
elseif(BUILD_TYPE_UPPER STREQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
endif()
