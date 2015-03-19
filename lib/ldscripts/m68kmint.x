/* Default linker script, for normal executables */
OUTPUT_FORMAT(a.out-mintprg)
SEARCH_DIR("/home/mikro/gnu-tools/m68000/m68k-atari-mint/lib");
SECTIONS
{
  /* The VMA of the .text section is 0xe4 instead of 0
     because the extended MiNT header is just before,
     at the beginning of the TEXT segment.  */
  .text 0xe4:
  {
    CREATE_OBJECT_SYMBOLS
    *(.text)
    CONSTRUCTORS
    _etext = .;
    __etext = .;
  }
  .data :
  {
    *(.data)
    _edata = .;
    __edata = .;
  }
  .bss :
  {
    __bss_start = .;
    *(.bss)
    *(COMMON)
    _end = .;
    __end = .;
  }
}
