section .text

global flush_gdt
global flush_idt

flush_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
    jmp 0x08:.reloadCS
.reloadCS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

flush_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret
