learnsdl2
=========

Learn game programming with libsdl2, following [Lazy Foo](http://lazyfoo.net/)'s tutorial [Beginning Game Programming v2.0](http://lazyfoo.net/tutorials/SDL/index.php)

Rewrite lesson sample programs in C, not C++. Build with [CMake][7] and [TDM-GCC][6] on Windows.


## Build

1. Download SDL2 development libraries, include [SDL2][1], [SDL2_image][2], [SDL2_ttf][3], [SDL2_mixer][4]. Extract to a directory such as `D:\mingw_dev_lib\` , `bin` to `bin`, `lib` to `lib`, `include` to `include`, etc. You can find out more details about setting up libraries [here][5].

2. Install [TDM-GCC][6] and [CMake][7].

3. Open command line in source code root directory, then input the follow command:

    ```shell
    mkdir build
    cd build
    cmake -G "MinGW files" ..
    mingw32-make
    ```

[1]: http://libsdl.org/download-2.0.php "SDL 2.0"
[2]: https://www.libsdl.org/projects/SDL_image/ "SDL_image 2.0"
[3]: https://www.libsdl.org/projects/SDL_ttf/ "SDL_ttf 2.0"
[4]: https://www.libsdl.org/projects/SDL_mixer/ "SDL_mixer 2.0"
[5]: http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php "Hello SDL"
[6]: http://tdm-gcc.tdragon.net/ "TDM-GCC"
[7]: http://www.cmake.org/ "CMake"
