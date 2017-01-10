# m68k-atari-mint sysroot

This is basically the set of libraries and includes I use everytime I setup a new development machine for my Atari projects.

Most interesting is the presence of `libc.a` (MiNTLib) and `libm.a` (PML). Basic usage:

`cd /usr`

`sudo git pull https://github.com/mikrosk/m68k-atari-mint-devel.git m68k-atari-mint`

This will create so called sysroot in `/usr/m68k-atari-mint`, with C includes being present in `/usr/m68k-atari-mint/include` and libraries in `/usr/m68k-atari-mint/lib`.
Then (or before) you want to configure `binutils` and `gcc` for m68k-atari-mint target with `--prefix=/usr` and `--with-sysroot=/usr/m68k-atari-mint`. See https://github.com/mikrosk/m68k-atari-mint-build for help with that.

You can use any prefix you like but then don't forget to add `<PREFIX>/bin` into your `PATH`.
