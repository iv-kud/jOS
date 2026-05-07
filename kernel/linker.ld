ENTRY(_start)

PHDRS {
    text   PT_LOAD FLAGS(5); /* R + X */
    rodata PT_LOAD FLAGS(4); /* R */
    data   PT_LOAD FLAGS(6); /* R + W */
}

SECTIONS {
    . = 1M;

    .text : ALIGN(4K) {
        . = ALIGN(8);
        KEEP(*(.multiboot))
        *(.text)
        *(.text.*)
    } :text

    .rodata : ALIGN(4K) {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    .data : ALIGN(4K) {
        *(.data)
        *(.data.*)
    } :data

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.bss.*)
        *(.stack)
    } :data

    /DISCARD/ : {
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.note.gnu.property)
        *(.comment)
    }
}
