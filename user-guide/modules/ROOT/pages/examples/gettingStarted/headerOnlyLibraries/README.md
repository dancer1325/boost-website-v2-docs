# how to compile?
## -- via -- CMake
* allows
  * simplifying the process
    * _Examples:_ dependency management, configure the build, integration with other tools
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
  * check the resulting executable | "build/"

## -- via -- Visual Studio
* TODO:
* Open Visual Studio and select *Create a new project*
* Choose *Console App* from the range of project templates.
* Change the names in the *Configure your new project* dialog, or leave the defaults, and click *Create*.
* Replace all the boilerplate content of the .cpp file with the contents of the `example.cpp` file, noting the inclusion of the header from Boost: *lambda.hpp*.
* Right-click on the name of the project in the *Solution Explorer* pane, and select *Properties*.
* Under *C/C++* select *General*, then click on *Additional Include Directories*
* Add the path to your Boost *include* folder, that will have been built in the previous section.

image::additional-include-directories.png[]

* Next, still in the project properties, select *Linker*, then *General*, and locate the *Additional Library Directories*
* Add the path to the Boost *lib* folder.

image::additional-library-directories.png[]

* Click *OK* to accept your input.

You can already run your example from Visual Studio:

* In the *Debug* menu, select *Start Without Debugging*, or press the F5 key.
* A Command Prompt should open up, so enter a list of numbers separated by spaces, and then *Enter*.
* You should get a line of numbers, your originals multiplied by 3.

image:first-app-running.png[]

Visual Studio provides support for CMake since Visual Studio 2017. CMake is a cross-platform build system that can generate build files for a variety of build tools, including Visual Studio solutions, makefiles, and ninja files.
By supporting CMake, Visual Studio is able to provide a consistent development experience across multiple platforms and build tools.
Additionally, the ability to generate CMake projects from Visual Studio allows developers to take advantage of Visual Studio's debugging and profiling tools while still using their preferred build system.

While Visual Studio provides a user friendly environment for building software, it may not always be the best choice for managing complex projects with multiple dependencies.
In such cases, it is recommended to consider using CMake, a popular and flexible build system that can generate build files for a variety of build tools.
You can have the option of using CMake to manage your complex projects, while still using Visual Studio's robust development and debugging features.

## MANUALLY
* | complex projects,
  * NOT recommended
    * Reason: manage ALL the compile & link options can quickly become unwieldy
### -- via -- Visual Studio Compiler
* `cl /I C:\boost\include example.cpp`
### -- via -- GCC
* `g++ -I /usr/local/include example.cpp -o example`
### -- via -- Clang
* `clang++ -I /usr/local/include example.cpp -o example`
* TODO:

# how to run?
## | Windows
* steps
  * `echo 1 2 3 | example`
  * TODO:
## | Linux
* steps
  * `echo 1 2 3 | ./example`
  * TODO:
## | MacOs
* steps
  * `echo 1 2 3 | ./example`
  * TODO: