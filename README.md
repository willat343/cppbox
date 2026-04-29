# cppbox

Collection of general-purpose C++ functions, classes and utilities

## Core Library

| **Dependency** | **Version** | **Description** |
|----------------|-------------|-----------------|
| CMake | >= 3.21 | CMake Build Tool |
| [cmakebox](https://github.com/willat343/cmakebox) | >= 0.0.11 | CMake Functions and Utilities |

There are several ways to include `cppbox` within your project:
- [Preferred] Via `FetchContent` allowing package to be built as a submodule.
- Via `find_package`, requiring package to be installed to the system, locally, or to a catkin workspace.

## Include via FetchContent

It is recommended to leverage the functionality of [cmakebox](https://github.com/willat343/cmakebox) by including the following lines in the `CMakeLists.txt` (replace `X.Y.Z` with versions for each):
```CMake
set(CMAKEBOX_VERSION "X.Y.Z")
FetchContent_Declare(
    cmakebox
    GIT_REPOSITORY git@github.com:willat343/cmakebox.git
    GIT_TAG v${CMAKEBOX_VERSION}
)
FetchContent_MakeAvailable(cmakebox)
list(APPEND CMAKE_MODULE_PATH "${cmakebox_SOURCE_DIR}/cmake")
include(CMakeBox)

set(CPPBOX_VERSION "X.Y.Z")
import_dependency(
    cppbox
    TARGET cppbox::cppbox
    VERSION ${CPPBOX_VERSION}
    GIT_REPOSITORY git@github.com:willat343/cppbox
    GIT_TAG v${CPPBOX_VERSION}
)
```

Without relying on [cmakebox](https://github.com/willat343/cmakebox), this can be achieved with (replace `X.Y.Z` with version):
```CMake
set(CPPBOX_VERSION "X.Y.Z")
FetchContent_Declare(
    cppbox
    GIT_REPOSITORY git@github.com:willat343/cppbox
    GIT_TAG        v${CPPBOX_VERSION}
)
FetchContent_MakeAvailable(cppbox)
```

## Include via Install

### Clone

```bash
git clone git@github.com:willat343/cppbox.git
cd cppbox
```

### Configure

```bash
cmake -G Ninja -S . -B build
```

For local install add `-DCMAKE_INSTALL_DIR=$HOME/.local`.

### Build

```bash
cmake --build build -j
```

### Install

```bash
sudo cmake --build build --target install
```

### Include

Include with the following lines in the `CMakeLists.txt`:
```CMake
target_link_libraries(<target> PUBLIC cppbox::cppbox)
```

If `cppbox` was installed (rather than using `cmakebox` or `FetchContent` functionality), then also needed is:
```CMake
find_package(cppbox REQUIRED)
```

### Uninstall

```bash
sudo cmake --build build --target uninstall
```

## Include in Catkin Workspace

A `package.xml` is supplied to facilitate an isolated installation within a catkin workspace (e.g. for ROS applications).

### Clone

```bash
cd /path/to/catkin_ws/src
git clone git@github.com:willat343/cppbox.git
```

### Build

```bash
cd /path/to/catkin_ws
catkin build cppbox
```

### Include

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<depend>cppbox</depend>
```

One can then include `cppbox` package by including in the `CMakeLists.txt`:
```CMake
find_package(cppbox REQUIRED)
target_link_libraries(<target> PUBLIC cppbox::cppbox)
```

### Clean

```bash
cd /path/to/catkin_ws
catkin clean cppbox
```
