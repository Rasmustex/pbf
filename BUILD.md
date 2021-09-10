# Building pbf

## Prerequisites
### Clone the github repo
In order to build pbf, you need to get the source code onto your machine. This is done using the github repository:
```sh
git clone https://github.com/Rasmustex/pbf.git
cd pbf
```

### Install build dependencies
You will need `clang`(or gcc, but you'd have to change the CC variable in the makefile), as well as `make`, which is used for invoking the build system:

#### Arch Linux
```sh
$ sudo pacman -S clang make 
```
#### Debian/Ubuntu
```sh
$ sudo apt install clang make 
```
### Fedora
```sh
$ sudo dnf install clang make 
```
## Building 
Simply type the command `make release`.

The binary will be in `bin/pbf`. 

## Installation
After building, you can install pbf to your `/usr/bin` with the command:
```sh
$ sudo make install 
```
You should now be able to invoke the program using the `pbf` command.

Otherwise, if you don't want pbf to install into that directory, you can simply change the `installdir` variable in the top of the makefile.