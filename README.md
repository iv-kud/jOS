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

### Debug build

Configure the project:

```bash
cmake --preset x86-debug
```

Build the kernel and ISO image:

```bash
cmake --build --preset x86-debug
```

Run the OS in QEMU:

```bash
cmake --build build/debug --target run
```

### Release build

Configure the project:

```bash
cmake --preset x86-release
```

Build the kernel and ISO image:

```bash
cmake --build --preset x86-release
```

Run the release build in QEMU:

```bash
cmake --build build/release --target run
```

### Debug with GDB

Start QEMU in debug mode:

```bash
cmake --build build/debug --target debug
```

Then, in another terminal, connect GDB:

```bash
cmake --build build/debug --target gdb
```
