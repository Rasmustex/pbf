# pbf
<p align="center">
  <img width="600"
       alt="screenshot pbf"
       src="https://user-images.githubusercontent.com/71628935/132048430-f77245d1-7c8b-4370-860b-d0975d2b2689.png">
</p>

## About
Pbf is a brainfuck interpreter written in C. It is currently very simple and bare-bones, but options will be added later, as well as possibly a bf "shell".

### The environment
By default, pbf provides your program with a 1KiB memory array, meaning that you can have up to 1000 characters involved in your program. This limitation is easily changed by editing the `main.c` file. The array consists of single-byte unsigned characters, meaning there is no negative number support. Pbf implements wraparound by default, meaning that if the memory pointer exceeds the limits of the array on either side, it wraps around to the other end of the array. This means that your program will not crash if it tries to reach an address below 0 or above 999; the pointer will instead move to the other side of the array (from 0 to 999 or from 999 to 0).

Pbf also gives basic error messages, and tells you if one of your brackets is missing a corresponding one.

## Usage
To run your program using pbf, simply enter the command:
```sh
# Unless you have installed pbf, you will have to write the path to pbf instead of just "pbf"
pbf <filename>
```

## Building and installation 
If you want to build pbf using the source code in this repository, please see [building pbf](https://github.com/Rasmustex/pbf/blob/main/BUILD.md).

***NOTE***: Currently, pbf is only tested on GNU/Linux, and is written with GNU/Linux in mind. There is, however, a good chance that it will compile and run just fine MacOS.

## License
Pbf is released under the [GPLv3](https://github.com/Rasmustex/pbf/blob/main/LICENSE)
