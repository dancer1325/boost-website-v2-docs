# Getting Started

* goal
  * how to get your first Boost app running -- from -- source

##  Prerequisites

* C++ compiler
  * | Windows
    * [download Microsoft Visual Studio IDE](https://visualstudio.microsoft.com/vs/)
  * | Linux
    * built-in GCC -- `g++ --version` -- 
    * | Ubuntu OR Debian-based distributions

      ```bash
      sudo apt update
      sudo apt install build-essential python3 libbz2-dev libz-dev libicu-dev
      ```

    * | Fedora

      ```bash
      sudo dnf update
      sudo dnf install gcc-c++ python3 bzip2-devel zlib-devel libicu-devel
      ```

    * | RedHat-based (RHEL, CentOS Stream, etc.)

      ```bash
      sudo yum update
      sudo yum install gcc-c++ python3 bzip2-devel zlib-devel libicu-devel
      ```

    * | Arch-based (Arch Linux, Manjaro, etc.)

      ```bash
      sudo pacman -Syu
      sudo pacman -S base-devel python3 bzip2 zlib icu
      ```
  * | macOS
    * recommendations: use Clang
      ```bash
      clang++ --version
      ```

## how to install Boost?
* how to verify installation?
  ```bash
  cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
  ```

### -- via -- package manager
* pros
  * ALREADY ALL pre-compiled 
* cons
  * lack of control | installation process
  * version conflicts
  * NO latest version

#### C++ Package Managers
##### Conan
* [here](https://conan.io/center/recipes/boost)
##### Vcpkg
* NOT officially supported
  * == NOT tested -- by -- Boost authors

* ways
  * OPTION1 -- via CL --
    ```
    vcpkg install boost
    
    # individual boost modules
    vcpkg install boost-variant2 boost-describe 
    ```
    * [boost modules](faq.md#modular-boost)
  * OPTION2 -- [manifest mode](https://learn.microsoft.com/en-us/vcpkg/concepts/manifest-mode) -- 
    * add `boost` | your "vcpkg.json"

    ```json
    {
        "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
        "name": "my-application",
        "version": "0.15.2",
        "dependencies": [
            "boost"
            // individual boost modules
            "boost-variant2",
            "boost-describe"
        ]
    }
    ```

* if you want to integrate it with CMake -> use [Vcpkg toolchain](https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration) + `CMAKE_TOOLCHAIN_FILE`

#### System-Level Package Managers
##### | Ubuntu
```bash
sudo apt update

# Install the Boost development libraries
sudo apt install libboost-all-dev
```

##### | Fedora
```bash
sudo dnf update

# Install the Boost development libraries
sudo dnf install boost-devel
```

##### | CentOS
```bash
sudo yum update

# Install the Boost development libraries
sudo yum install boost-devel

# | CentOS 8+, enable PowerTools repository
# sudo yum config-manager --set-enabled powertools
```

##### | Arch
```bash
sudo pacman -Syu

# Install the Boost development libraries
sudo pacman -S boost
```

##### | macOS (Homebrew):
```bash
brew update
brew upgrade

# Install the Boost development libraries
brew install boost

# Verify installation
brew list boost
```

### -- via -- Source
* steps
  * [download Boost](#download-boost)
  * compile it
    * vs -- via -- package manager
    * ADDITIONAL step

#### Download Boost
##### -- via -- [B2](https://www.bfgroup.xyz/b2/)
* recommended one
  * Reason: official supported build system / used -- by the -- Boost libraries 

* steps
  * [download](https://www.boost.org/users/download/)
  * right click > extract it

##### -- via -- CMake
* steps
  * [download](https://github.com/boostorg/boost/releases)
  * right click > extract it

##### -- via -- CL
###### | Windows
```bash
# curl https://archives.boost.io/release/X.Y.Z/source/boost_1_89_0.zip
curl https://archives.boost.io/release/1.89.0/source/boost_1_89_0.zip

# tar -xf boost_X_Y_Z.zip 
tar -xf boost_1_89_0.zip

# cd boost_X_Y_Z 
cd boost_1_89_0
```

###### | Linux
```bash
# wget https://archives.boost.io/release/X.Y.Z/source/boost_1_89_0.zip
wget https://archives.boost.io/release/1.89.0/source/boost_1_89_0.zip

# tar -xf boost_X_Y_Z.zip 
tar -xf boost_1_89_0.zip

# cd boost_X_Y_Z 
cd boost_1_89_0
```

###### | macOS

```bash
# curl https://archives.boost.io/release/X.Y.Z/source/boost_1_89_0.zip
curl https://archives.boost.io/release/1.89.0/source/boost_1_89_0.zip

# tar -xf boost_X_Y_Z.zip 
tar -xf boost_1_89_0.zip

# cd boost_X_Y_Z 
cd boost_1_89_0
```

###### | Git

```bash
git clone https://github.com/boostorg/boost.git -b boost-{latest_version} {release_basename} --depth 1
cd {release_basename}

# initialize ALL boost modules
git submodule update --depth 1 --init --recursive <2>
```

#### Bootstrap
##### -- via -- B2
* recommended
###### | Windows
```bash
bootstrap.bat
b2
b2 install --prefix=C:\Boost
```

* POSSIBLE Problems:
  * Problem1:

    ![](../images/cpp-runtime-error.png)
    * Solution: install OR update your Visual Studio's version

###### | Unix variants

* if libraries are _header-only_ -> NOT require this step
  * Reason: copied | your installation folder

```bash
./bootstrap.sh --prefix=/usr/local
# 1. if you want to build ONLY some libraries -> pass `--with-libraries=librarya,libraryb`
# ./bootstrap.sh --prefix=/usr/local --with-libraries=librarya,libraryb
# 2. check libraries / need to be built   -> `--show-libraries`
# ./bootstrap.sh --show-libraries

./b2

./b2 install
```

##### -- via -- CMake

```bash
mkdir __build
cd __build
cmake ..
cmake --build .
cmake --build . --target install
```

If you are using a multi-config generator, such as Visual Studio, you can install the Debug and Release variants of the library separately with:

### Individual Modules (== subset of Boot libraries)

* use cases
  * | CI Systems

[source,bash,subs="attributes+"]
.Downloading boost:unordered[] and internal dependencies
----
git clone https://github.com/boostorg/boost.git -b boost-{latest_version} {release_basename} --depth 1 <1>
git submodule update --depth 1 -q --init tools/boostdep <2>
git submodule update --depth 1 -q --init libs/unordered <3>
python tools/boostdep/depinst/depinst.py -X test -g "--depth 1" unordered <4>
----

<1> Download the Boost super-project, which contains references to all Boost libraries
<2> Initialize boost:boostdep[] used to determine internal boost dependencies
<3> Initialize boost:unordered[].
Repeat this step for any other modules you need.
<4> Initialize any dependencies of boost:unordered[].
Repeat this step for any other modules you need.

This procedure requires `git` and `python`.
The following steps in this document apply to both methods of installing Boost.
The only difference is what libraries will be available.



[source]
----
cmake --build . --target install --config Debug
cmake --build . --target install --config Release
----

Although both the https://www.bfgroup.xyz/b2/[B2] and the CMake scripts work fine, the final installed libraries will have different layouts for historical reasons.
Both the CMake integration scripts and the libraries will be installed under different paths and this can create incompatibilities between Boost installations.

TIP: You don't need to *build* Boost with CMake to be able to *use* Boost with CMake.
CMake integration will work fine even if you install Boost with https://www.bfgroup.xyz/b2/[B2].

* [MORE](https://github.com/boostorg/cmake)

## Environment variables

We recommend you update your environment variables after installing Boost.
When you update your environment variables, you are telling your operating system and other tools where to look for the Boost libraries and headers.

[tabs,sync-group-id=os]
====
Windows::
+
--

[source]
----
set BOOST_ROOT=C:\boost <1>
----

<1> Specify the root directory of the Boost pass:[C++] libraries so other tools can find it

IMPORTANT: Replace `C:\boost` with the prefix directory you specified during the installation, if different.

--

Linux::
+
--

[source,bash]
----
export BOOST_ROOT=/usr/local <1>
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH <2>
export CPLUS_INCLUDE_PATH=/usr/local/include:$CPLUS_INCLUDE_PATH <3>
----

<1> Specify the root directory of the Boost pass:[C++] libraries so other tools can find it
<2> Specify additional directories to search for shared libraries when executing a program
<3> Specify additional directories to search for pass:[C++] header files

IMPORTANT: Replace `/usr/local` with the prefix directory you specified during the installation, if different.

You can add these `export` commands to your `~/.bashrc` or `~/.profile` file to make the changes permanent.

--

macOS::
+
--

[source,bash]
----
export BOOST_ROOT=/usr/local <1>
----

<1> Specify the root directory of the Boost pass:[C++] libraries so other tools can find it

IMPORTANT: Replace `/usr/local` with the prefix directory you specified during the installation, if different.

You can add these `export` commands to your `~/.bashrc` or `~/.profile` file to make the changes permanent.

--
====

[#your-first-app]
== Your First App

=== Header-only libraries

Let's start by using a header-only library.
Copy the following program into a file called `example.cpp`.

[source,C++]
.example.cpp
----
// Include a header from the Boost.Lambda library
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::cout << "Enter numbers: ";

    // Read a sequence of integers from standard input, use Boost.Lambda to multiply each number by three, then write it to the standard output
    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " ");
}
----

We can now compile this program:

[tabs,sync-group-id=build]
========
CMake::
+
--
You can use https://cmake.org/[CMake,window="_blank"] to configure a project to use Boost and your `example.cpp`.
Here's an example `CMakeLists.txt` file that uses Boost:

[source,cmake]
.CMakeLists.txt
----
cmake_minimum_required(VERSION 3.8...3.31)
project(MyProject)

find_package(Boost REQUIRED)
add_executable(MyProject example.cpp)
target_link_libraries(MyProject Boost::headers)
----

Store this file next to your `example.cpp` and run the basic CMake workflow:

[source,none,subs="attributes+"]
----
mkdir build <1>
cd build <2>
cmake .. -D BOOST_ROOT=path/to/{release_basename} <3>
cmake --build . <4>
----

<1> Create a `build` directory which should store the results
<2> Change the current working directory to `build`
<3> Run the CMake configure step, providing it with the Boost directory
<4> Build the project

If using CMake >=3.13, this can be simplified to:

[source,none,subs="attributes+"]
----
cmake -S . -B build -D BOOST_ROOT=path/to/{release_basename}
cmake --build build
----

In either case, the resulting executable should be available in the `build` directory.

--

Visual Studio::
+
--

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

[TIP]
====
Visual Studio provides support for CMake since Visual Studio 2017. CMake is a cross-platform build system that can generate build files for a variety of build tools, including Visual Studio solutions, makefiles, and ninja files.
By supporting CMake, Visual Studio is able to provide a consistent development experience across multiple platforms and build tools.
Additionally, the ability to generate CMake projects from Visual Studio allows developers to take advantage of Visual Studio's debugging and profiling tools while still using their preferred build system.

While Visual Studio provides a user friendly environment for building software, it may not always be the best choice for managing complex projects with multiple dependencies.
In such cases, it is recommended to consider using CMake, a popular and flexible build system that can generate build files for a variety of build tools.
You can have the option of using CMake to manage your complex projects, while still using Visual Studio's robust development and debugging features.
====

--

By Hand::
+
--
In the directory where you saved *example.cpp*, issue the following command:

Visual Studio Compiler:

[source,none,subs="attributes+"]
----
cl /I C:\boost\include example.cpp
----

GCC:

[source,none,subs="attributes+"]
----
g++ -I /usr/local/include example.cpp -o example
----

Clang:

[source,none,subs="attributes+"]
----
clang++ -I /usr/local/include example.cpp -o example
----

NOTE: Replace `C:\boost` or `/usr/local` with your Boost installation prefix if necessary.

[TIP]
====
It is generally not recommended to use these commands by hand for complex projects, as managing all the compile and link options can quickly become unwieldy.
Using a build system like CMake or Make can greatly simplify the process of building and managing a project, particularly when dealing with large codebases or dependencies.

Using a build system also has other advantages, such as easier dependency management, the ability to easily configure the build for different platforms or compilers, and the ability to easily integrate with other tools such as version control systems and automated testing frameworks.
====

--
========

To test the result, run the executable from the path where it was built:

[tabs,sync-group-id=os]
====
Windows::
+
--
[source]
----
echo 1 2 3 | example
----
--

Linux::
+
--
[source]
----
echo 1 2 3 | ./example
----
--

macOS::
+
--
[source]
----
echo 1 2 3 | ./example
----
--
====

Did you get the expected result?

=== Compiled Libraries

In this section, we will locate an example from GitHub, and then build and run a project based on the example.

For most Boost libraries, there is an `example` sub-folder containing a range of examples.
For this guide, we will locate an example that reads a JSON file, and pretty-prints its contents.

Copy all the code from https://github.com/boostorg/json/blob/develop/example/pretty.cpp[`json/example/pretty.cpp`,window="_blank"] into your `example.cpp`.
Let's compile it:

[tabs,sync-group-id=build]
========
CMake::
+
--
Edit the contents of `CMakeLists.txt`:

[source,cmake]
.CMakeLists.txt
----
cmake_minimum_required(VERSION 3.8...3.31)
project(MyProject)

find_package(Boost REQUIRED COMPONENTS json)
add_executable(MyProject main.cpp)
target_link_libraries(MyProject Boost::json)
----

In this example, we explicitly require `json` as boost:json[] is a compiled library.
Compiled libraries need to be explicitly required and linked separately.

Run the commands for the usual CMake workflow once more to build the executable.

NOTE: Note how the difference between header-only and compiled libraries is transparent when using a build system.
--

Visual Studio::
+
--
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
--

By Hand::
+
--
Repeat the instructions to read the compile the executable:

In the directory where you saved `example.cpp`, issue the following command:

Visual Studio Compiler:

[source,none,subs="attributes+"]
----
cl /I C:\boost\include /link C:\boost\lib\libboost_json-vc71-mt-d-x86-1_34.lib example.cpp
----

GCC:

[source,none,subs="attributes+"]
----
g++ -I /usr/local/include example.cpp -L /usr/local/libboost_json.a -o example
----

Clang:

[source,none,subs="attributes+"]
----
clang++ -I /usr/local/include example.cpp -L /usr/local/lib -l boost_json -o example
----

NOTE: Replace `C:\boost` or `/usr/local` with your Boost installation prefix if necessary.

As boost:json[] is a compiled library, we need the linker option in our example.
The name of the library file might vary according to your architecture and the options provided to `b2` while installing boost.
Check the `lib` in your installation prefix.
--
========

Search your computer for any JSON file, unless you have one you would like to use already.
Record the full path to that file and run the example with:

[tabs,sync-group-id=os]
====
Windows::
+
--
[source]
----
example "path/to/json/file.json"
----
--

Linux::
+
--
[source]
----
./example "path/to/json/file.json"
----
--

macOS::
+
--
[source]
----
./example "path/to/json/file.json"
----
--
====

Did you get the expected result?

# [B2](https://www.bfgroup.xyz/b2/)
* == custom build app
  * allows
    * building the Boost libraries



=== Summary

Although the samples you have now built and run are quite simple, if you have got this far successfully, it means your build, installation and project linking are all working correctly.
Great job!

=== Next Steps

You might like to scan the examples folders of some of the other libraries that you are interested in, and create and run projects to get them running.

Once you are more experienced with Boost, you might like to build and install only those libraries you require. To this end, it can be helpful to know the _dependencies_ that your target libraries have. This includes both _primary dependencies_ (the libraries directly referenced by your target library) and _secondary dependencies_ (the libraries not referenced by your target library, but referenced by the primary or other secondary libraries). To aid you in determining this information, refer to the https://pdimov.github.io/boostdep-report/[Boost Dependency Report]. This report is updated with each public release of Boost.
