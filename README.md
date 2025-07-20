# cppbox

Collection of general-purpose C++ functions, classes and utilities

## Core Library

| **Dependency** | **Version** | **Description** |
|----------------|-------------|-----------------|
| CMake | >= 3.21 | CMake Build Tool |
| [cmakebox](https://github.com/willat343/cppbox) | >= 0.0.1 | CMake Functions and Utilities |

There are several ways to include `cppbox` within your project:
- [Preferred] Via `FetchContent` allowing `cppbox` to be built as a submodule.
- Via `find_package`, requiring `cppbox` to be installed to the system, locally, or to a catkin workspace.

## Include via FetchContent

It is recommended to leverage the functionality of [cmakebox](https://github.com/willat343/cppbox) by including the following lines in the `CMakeLists.txt` (replace `X.Y.Z` with version):
```CMake
set(CMAKEBOX_VERSION "0.0.1")
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
    USE_SYSTEM_REQUIRED_VERSION ${CPPBOX_VERSION}
    GIT_REPOSITORY git@github.com:willat343/cppbox
    GIT_TAG v${CPPBOX_VERSION}
)
```

Without relying on [cmakebox](https://github.com/willat343/cppbox), this can be achieved with (replace `X.Y.Z` with version):
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

For system install:
```bash
cmake -S . -B build
```

For local install:
```bash
cmake -S . -B build -DCMAKE_INSTALL_DIR=$HOME/.local
```

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
find_package(cppbox REQUIRED)
target_link_libraries(<target> PUBLIC cppbox::cppbox)
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

### Uninstallation

```bash
cd /path/to/catkin_ws
catkin clean cppbox
```

### Include

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<depend>cppbox</depend>
```

One can then include `cppbox` package by includeing in the `CMakeLists.txt`:
```CMake
find_package(cppbox REQUIRED)
target_link_libraries(<target> PUBLIC cppbox::cppbox)
```
