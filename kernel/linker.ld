ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5);    /* R-X (Read + Execute) */
    rodata PT_LOAD FLAGS(4);  /* R-- (Read-only) */
    bss PT_LOAD FLAGS(6);     /* RW- (Read + Write) */
}

SECTIONS {
    . = 1M;

    .text : ALIGN(4K) {
        . = ALIGN(8);
        *(.text)
        KEEP(*(.multiboot))
    } :text

    .rodata : ALIGN(4K) {
        *(.rodata)
    } :rodata

    .data : ALIGN(4K) {
        *(.data)
    } :rodata

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.stack)
    } :bss

    /DISCARD/ : {
        *(.eh_frame)
        *(.note.gnu.property)
    }
}
