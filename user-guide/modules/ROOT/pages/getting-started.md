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
  * 👀ALREADY ALL pre-compiled 👀
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

#### ways to download Boost
##### -- via -- [B2](https://www.bfgroup.xyz/b2/)
* recommended one
  * Reason: official supported build system / used -- by the -- Boost libraries 

* steps
  * [download](https://www.boost.org/releases/latest/)
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

#### ways to compile
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

* | folder / extract B2

  ```bash
  ./bootstrap.sh --prefix=/usr/local
  # 0. configure the prefix | install b2
  #     == NOTHING is installed
  #     generate ./b2
  # 1. if you want to build ONLY some libraries -> pass `--with-libraries=librarya,libraryb`
  # ./bootstrap.sh --prefix=/usr/local --with-libraries=librarya,libraryb
  # 2. check libraries / need to be built   -> `--show-libraries`
  # ./bootstrap.sh --show-libraries
  
  ./b2
  # == compile the Boost libraries | ./stage
  # == make  
  
  sudo ./b2 install
  # install | system
  # == make install
  
  cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
  # check if boost was installed properly
  ```

##### -- via -- CMake

```bash
mkdir __build
cd __build
cmake ..
cmake --build .
cmake --build . --target install
```

* TODO: If you are using a multi-config generator, such as Visual Studio, you can install the Debug and Release variants of the library separately with:

### Individual Modules (== subset of Boot libraries)

* allows
  * ONLY installing the dependencies / you require -- check [Boost Dependency Report](https://pdimov.github.io/boostdep-report/) -- 
* use cases
  * | CI Systems

* requirements
  * know your target libraries' dependencies
    * _primary dependencies_
      * := libraries / DIRECTLY referenced -- by -- your target library
    * _secondary dependencies_ 
      * := libraries /
        * NOT referenced -- by -- your target library
        * referenced -- by the -- primary OR other secondary libraries
  * git
  * python

* steps
  ```bash
  git clone https://github.com/boostorg/boost.git -b boost-{latest_version} {release_basename} --depth 1 <1>
  # download the Boost super-project / contains references -- to -- ALL Boost libraries
  
  git submodule update --depth 1 -q --init tools/boostdep <2>
  # initialize boost:boostdep[] -- to -- determine internal boost dependencies
  
  git submodule update --depth 1 -q --init libs/unordered <3>
  # initialize boost:unordered[]
  # repeat / EACH needed module
  
  python tools/boostdep/depinst/depinst.py -X test -g "--depth 1" unordered <4>
  # initialize any dependencies of boost:unordered[]
  # repeat / EACH needed module 
  ----

  ```bash
  cmake --build . --target install --config Debug
  cmake --build . --target install --config Release
  ```

* TODO: Although both the https://www.bfgroup.xyz/b2/[B2] and the CMake scripts work fine, the final installed libraries will have different layouts for historical reasons.
Both the CMake integration scripts and the libraries will be installed under different paths and this can create incompatibilities between Boost installations.

TIP: You don't need to *build* Boost with CMake to be able to *use* Boost with CMake.
CMake integration will work fine even if you install Boost with https://www.bfgroup.xyz/b2/[B2].

* [MORE](https://github.com/boostorg/cmake)

## Environment variables

* recommendations
  * AFTER installing Boost, update your environment variables
* allows
  * specifying where to look for the Boost libraries & headers 

### | Windows
* steps
  * `set BOOST_ROOT=prefixAtBootstrap`
    * == root directory of the Boost
    * `prefixAtBootstrap`
      * by default, `C:\boost`

### | Linux
* steps
  * | your "~/.bashrc" OR "~/.profile"
    ```bash
    export BOOST_ROOT=prefixAtBootstrap
    # root directory of the Boost
    #   by default, /usr/local  
    #       export BOOST_ROOT=/usr/local
    
    export LD_LIBRARY_PATH=prefixAtBootstrap/lib:$LD_LIBRARY_PATH
    # | execute a program, ADDITIONAL directories -- to -- search for shared libraries
    #   by default, export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH  
    
    export CPLUS_INCLUDE_PATH=prefixAtBootstrap/include:$CPLUS_INCLUDE_PATH
    # ADDITIONAL directories -- to -- search for C++ libraries
    #   by default, CPLUS_INCLUDE_PATH=/usr/local/include:$CPLUS_INCLUDE_PATH 
    ```

### | macOS
* steps
  * | your "~/.bashrc" OR "~/.profile"
    ```bash
    export BOOST_ROOT=prefixAtBootstrap
    # root directory of the Boost
    #   by default, /usr/local  
    #       export BOOST_ROOT=/usr/local
    ```

# [B2](https://www.bfgroup.xyz/b2/)
* == custom build app
  * allows
    * building the Boost libraries
