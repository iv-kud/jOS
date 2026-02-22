section .text

global read_byte
global write_byte

read_byte:
    mov eax, [esp + 4]
    in al, dx
    ret

write_byte:
    mov   edx, [esp + 4]
    mov   al, [esp + 4 + 4]
    out   dx, al
    ret
