learnsdl2
=========

Learn game programming with libsdl2, following [Lazy Foo](http://lazyfoo.net/)'s tutorial [Beginning Game Programming v2.0](http://lazyfoo.net/tutorials/SDL/index.php)

Rewrite lesson sample programs in C, not C++. Build with [CMake][7] on Linux.


## Build

1. Install package `build-essential`, `cmake`, `libsdl2-dev`, `libsdl2-ttf-dev`, `libsdl2-image-dev`, `libsdl2-mixer-dev`.

2. Open command line in source code root directory, then input the follow command:

    ```shell
    mkdir build
    cd build
    cmake -G "Unix Makefiles" ..
    make
    ```
