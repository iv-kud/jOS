## Just Operating System

----
## Install dependencies
#### Arch Linux
1. Installing the basic build tools and the cross-compiler:
```bash
sudo pacman -S --needed base-devel git cmake nasm
```
2. Installing the i686-elf cross compiler and tools:
```bash
yay -S i686-elf-gcc i686-elf-binutils
```
3. Installing QEMU for testing:
```bash
sudo pacman -S qemu-full
```
4. Installing GRUB to create a bootable image:
```bash
sudo pacman -S grub xorriso mtools
```
5. Additional debugging tools:
```bash
sudo pacman -S gdb
```
## Build and run
#### Arch Linux
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
make
make run
```
