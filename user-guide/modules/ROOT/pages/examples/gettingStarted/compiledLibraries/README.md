* goal
  * build & run a project -- based on -- Github example
    * [example.cpp](example.cpp)  == [pretty.cpp](https://github.com/boostorg/json/blob/develop/example/pretty.cpp)
      * reads a JSON file + pretty-prints its contents
    * [file.hpp](https://github.com/boostorg/json/blob/develop/example/file.hpp)

* vs header-only library
  * | compilation, 
    * link with the compiled library

# how to compile?
## -- via -- B2
* TODO: 
## -- via -- CMake
* steps
  * configure [CMake](https://cmake.org/)
    * _Example:_ [CMakeLists.txt](CMakeLists.txt)
  * run
    * | ANY CMake version
      ```bash
      mkdir build
      # Create a "build/" directory / store the results
  
      cd build
      # switch the current working directory -- to -- "build/"
  
      cmake .. -D BOOST_ROOT=path/to/yourBoostRelease
      # if you use default location (==/usr/local)  -> run `cmake .. -D BOOST_ROOT=/usr/local`    OR    `cmake ..`
      # run CMake / provide the Boost directory
  
      cmake --build .
      # build the project
      ```
    * | CMake v3.13+
      ```bash
      cmake -S . -B build -D BOOST_ROOT=path/to/yourBoostRelease
      # if you use default location (==/usr/local)  -> run `cmake -S . -B build -D BOOST_ROOT=/usr/local`    OR    `cmake -S . -B build`
      
      cmake --build build
      ```
    * Problems:
      * Problem1: "example.cpp:21:10: fatal error: 'file.hpp' file not found"
        * Solution: add missing [file.hpp](https://github.com/boostorg/json/blob/develop/example/file.hpp)
  * check the resulting executable | "build/MyProject"

## -- via -- Visual Studio
* TODO:
  . Create a new Visual Studio pass:[C++] Console App.
  Name it JsonPrint.
  . Update both the additional include directories, and additional library directories, as you did for the previous section.
  . Copy all the code from https://github.com/boostorg/json/blob/develop/example/pretty.cpp, and use it to replace all the default content of the project's cpp file.

You can already run your example from Visual Studio:

. Search your computer for any JSON file, unless you have one you would like to use already.
Record the full path to that file.

. In Visual Studio, locate and select *Build Solution*.

You should get neatly formatted output:

image:json-example-running.png[]

[circle]
* If your JSON included symbols such as the umlaut, these will not be rendered correctly unless you change the format of your Command Prompt to UTF-8. By default, a Command Prompt supports a code page numbered 437. To change the code page to UTF-8, type `chcp 65001`.

* If you get compile errors such as `cannot open file 'libboost_json-vc143-mt-gd-x64-1_81.lib'` you have probably not entered the *Additional Library Directories* correctly.

## MANUALLY
### -- via -- Visual Studio Compiler
* `cl /I C:\boost\include /link C:\boost\lib\libboost_json-vc71-mt-d-x86-1_34.lib example.cpp`
### -- via -- GCC
* `g++ -I /usr/local/include example.cpp -L /usr/local/libboost_json.a -o example`
  * `-l`
    * Reason: link -- with the -- compiled library
### -- via -- Clang
* `clang++ -I /usr/local/include example.cpp -L /usr/local/lib -l boost_json -o example`
  * `-l`
    * Reason: link -- with the -- compiled library

# how to run?
## | Windows
* steps
  * `.\build\MyProject test.json`
    * return the .json / prettified
## | Linux
* steps
  * `./build/MyProject test.json`
    * return the .json / prettified
## | MacOs
* steps
  * `./build/MyProject test.json`
    * return the .json / prettified
