# Building pbf

## Prerequisites
### Clone the github repo
In order to build pbf, you need to get the source code onto your machine. This is done using the github repository:
```sh
git clone https://github.com/Rasmustex/pbf.git
cd pbf
```

### Install build dependencies
You will need the GNU C compiler (`gcc`), as well as `make`, which is used for using the build system:

#### Arch Linux
```sh
$ sudo pacman -S gcc make 
```
#### Debian/Ubuntu
```sh
$ sudo apt install gcc make 
```
### Fedora
```sh
$ sudo dnf install gcc make 
```
## Building 
Simply type the command `make`.

The binary will be in `build/pbf`. 

## Installation
After building, you can install pbf to your `~/.local/bin` with the command:
```sh
$ make install 
```
You should now be able to invoke the program using the `pbf` command.

***Make sure that `~/.local/bin` is part of your `$PATH` variable. Otherwise your shell won't find it.***

Otherwise, if you don't want pbf to install into that directory, you can simply change the `installdir` variable in the top of the makefile.

### Uninstalling pbf
If you want to uninstall pbf, simply go to the pbf directory that has been cloned from github. and run:
```sh
$ make uninstall
```
