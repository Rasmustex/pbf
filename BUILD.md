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

The binary will be in `build/pbf`. For now, you'd have to install it manually if you want it installed, but an option to `sudo make install` will be added in the future.