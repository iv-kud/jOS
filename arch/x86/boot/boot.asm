section .multiboot
header_start:
    dd 0xE85250D6                ; magic number 
    dd 0                         ; architecture 0 = x86
    dd header_end - header_start ; header length
    dd 0x100000000 - (0xE85250D6 + 0 +(header_end - header_start)) ; magic + architecture + header_length + checksum = 0 =>
                                                                   ;checksum = -(magic + architecture + header_length)
    ;tags
    dw 0    ; type tag
    dw 0    ; flags
    dd 8    ; size tag 
header_end:

section .text
global _start
extern kernel_main ; main func from kernel.cpp 

_start:
    cli
    mov esp, stack_top
    call kernel_main
    hlt

section .bss
stack_bottom:
    resb 16384      ; 16 Kb stack
stack_top:
