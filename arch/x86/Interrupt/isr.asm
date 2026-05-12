section .text

%macro ISR_NOERROR 1
    global isr%1

    isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERROR 1
    global isr%1

    isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

extern isr_handler

isr_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    iret

ISR_NOERROR 0
ISR_NOERROR 1
ISR_NOERROR 2
ISR_NOERROR 3
ISR_NOERROR 4
ISR_NOERROR 5
ISR_NOERROR 6
ISR_NOERROR 7

ISR_ERROR   8

ISR_NOERROR 9

ISR_ERROR   10
ISR_ERROR   11
ISR_ERROR   12
ISR_ERROR   13
ISR_ERROR   14

ISR_NOERROR 15
ISR_NOERROR 16

ISR_ERROR   17

ISR_NOERROR 18
ISR_NOERROR 19
ISR_NOERROR 20

ISR_ERROR   21

ISR_NOERROR 22
ISR_NOERROR 23
ISR_NOERROR 24
ISR_NOERROR 25
ISR_NOERROR 26
ISR_NOERROR 27
ISR_NOERROR 28

ISR_ERROR   29
ISR_ERROR   30

ISR_NOERROR 31
