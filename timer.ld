MEMORY {
  /*  OpenSBI jumps to 0x80200000 */
  kernel_space (rwx) : ORIGIN = 0x80200000, LENGTH = 2 * 1024 * 1024
}

SECTIONS {
  .text : {
    build/boot.o(.text)
    *(.text)
  } > kernel_space

  .data : {
    *(.data)
  } > kernel_space

  .rodata : {
    *(.rodata)
  } > kernel_space

  .bss : {
    *(.bss)
  } > kernel_space

  /* Align to 8 bytes for the stack */
  . = ALIGN(8);
  . = . + 4096;
  _STACK_PTR = .;
}
