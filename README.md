# cOS, an OS made in C


## Dependencies

### make
Make is used to automate the build process. It is used to compile the kernel, and to build the bootloader.

### nasm
Compiles assembly code into machine code.

### mtools
A collection of utilities for manipulating MS-DOS filesystems.

### Install on Manjaro / Arch	
```
sudo pacman -S make nasm qemu mtools
```

### Install on Ubuntu
```
sudo apt-get install make nasm qemu mtools 
```

### Install on Fedora / CentOS
```
sudo dnf install make nasm qemu mtools
```

---
### Building the cross compiler

To build the cross compiler, you can use a script inside the `scripts` folder. The credit for the script goes to [mell-o-tron](https://github.com/mell-o-tron). If no script are available for your distro, you can refer to [this table](https://wiki.osdev.org/GCC_Cross-Compiler#Installing_Dependencies) from the osdev wiki and install the dependencies yourself.

## Repository structure
```
.
├── build
│   ├── bootloader.bin
│   ├── kernel.bin
│   └── os.bin
├── Docs
│   ├── assets
│   │   └── drive.png
│   ├── build.md
│   ├── Links.md
│   ├── schematics.drawio
│   └── TODO.md
├── LICENSE
├── Makefile
├── qemu.log
├── README.md
├── scripts
│   ├── setup-gcc-arch.sh
│   └── setup-gcc-ubuntu.sh
└── src
    ├── bootloader
    │   ├── bootsector.asm
    │   └── Makefile
    └── kernel
        ├── build
        │   ├── ata.o
        │   ├── color.o
        │   ├── cursor.o
        │   ├── interrupts.o
        │   ├── kernel_entry.o
        │   ├── kernel.o
        │   ├── keyboard.o
        │   ├── ports.o
        │   ├── print.o
        │   ├── stdlib.o
        │   ├── string.o
        │   └── timer.o
        ├── drivers
        │   ├── disk
        │   │   └── ata
        │   │       ├── ata.c
        │   │       └── ata.h
        │   ├── keyboard
        │   │   ├── ch-fr_keymap.h
        │   │   ├── keyboard.c
        │   │   └── keyboard.h
        │   ├── ports
        │   │   ├── ports.c
        │   │   └── ports.h
        │   └── screen
        │       ├── color
        │       │   ├── color.c
        │       │   └── color.h
        │       ├── cursor
        │       │   ├── cursor.c
        │       │   └── cursor.h
        │       └── print
        │           ├── print.c
        │           └── print.h
        ├── interrupts
        │   ├── interrupts.c
        │   └── interrupts.h
        ├── kernel.c
        ├── kernel_entry.asm
        ├── Makefile
        └── stdlibs
            ├── stdlib.c
            ├── stdlib.h
            ├── string.c
            └── string.h
```