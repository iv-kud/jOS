## Just Operating System

---

# Install dependencies

## Arch Linux

1. Install the basic build tools and dependencies:
```bash
sudo pacman -S --needed base-devel git cmake nasm
```

2. Install the i686-elf cross compiler and binutils:
```bash
yay -S i686-elf-gcc i686-elf-binutils
```

3. Install QEMU for testing:
```bash
sudo pacman -S qemu-full
```

4. Install GRUB and ISO tools:
```bash
sudo pacman -S grub xorriso mtools
```

5. Install debugging tools:
```bash
sudo pacman -S gdb
```

---

## Ubuntu

1. Install the required packages:
```bash
sudo apt update

sudo apt install -y \
    build-essential \
    git \
    cmake \
    nasm \
    qemu-system-x86 \
    grub-pc-bin \
    xorriso \
    mtools \
    gdb
```

2. Install the i686-elf cross compiler.

Ubuntu repositories usually do not provide `i686-elf-gcc`,
so you need to build the cross-compiler manually.

Example dependencies for building GCC and Binutils:
```bash
sudo apt install -y \
    bison \
    flex \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo
```

---

# Build and run

## Arch Linux / Ubuntu

```bash
mkdir build && cd build

cmake -DCMAKE_TOOLCHAIN_FILE=../arch/x86/toolchain-x86.cmake ..

make
make run
```