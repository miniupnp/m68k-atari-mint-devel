/* Default linker script, for normal executables */
/* Copyright (C) 2014-2016 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */
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
