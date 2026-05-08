## Just Operating System

---

# Install dependencies

## Arch Linux

1. Install the basic build tools and dependencies:
```bash
sudo pacman -Syu
```
```bash
sudo pacman -S --needed base-devel git cmake nasm clang
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
    gdb \
    unzip \
    clang-format
```

2. Install the i686-elf cross compiler.
Ubuntu repositories usually do not provide `i686-elf-gcc`, so you need to build the cross-compiler manually.

```bash
mkdir -p ~/opt

cd ~/opt

git clone https://github.com/lordmilko/i686-elf-tools.git

cd i686-elf-tools

chmod +x i686-elf-tools.sh

./i686-elf-tools.sh linux
```
Or download the release immediately (But first, сheck the system requirements for the compiler.)
```bash
mkdir -p ~/opt/i686-elf-tools
cd ~/opt/i686-elf-tools

wget https://github.com/lordmilko/i686-elf-tools/releases/download/15.2.0/i686-elf-tools-linux.zip

unzip i686-elf-tools-linux.zip
```
3. Add the toolchain to your PATH:
```bash
echo 'export PATH="$HOME/opt/i686-elf-tools/bin:$PATH"' >> ~/.bashrc

source ~/.bashrc
```
4. Check the compiler
```bash
i686-elf-gcc --version
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