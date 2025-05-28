# cppbox

Collection of general-purpose C++ functions, classes and utilities

## Core Library

### Installation

```bash
git clone git@github.com:willat343/cppbox.git
cd cppbox
cmake -S . -B build -DBUILD_DOCUMENTATION=OFF -DBUILD_TESTS=OFF
cmake --build build
cmake --build . -j
sudo cmake --build build --target install
```

### Uninstallation

```bash
sudo cmake --build build --target uninstall
```

### Include in Downstream Project

In the downstream project's `CMakeLists.txt`:
```cmake
find_package(cppbox REQUIRED)
target_link_libraries(<target> PUBLIC ${cppbox_LIBRARIES})
```

The `cppbox` provides CMake targets in `${cppbox_LIBRARIES}` which contain the properties (include directories, link libraries, compile options, compile flags, link flags, etc.) needed by the downstream project, and hence only `target_link_libraries()` is required.

## Catkin Support

A `package.xml` is supplied to facilitate an isolated installation within a catkin workspace (e.g. for ROS applications).

### Installation

Either:
```bash
ln -s /path/to/cppbox /path/to/catkin_ws/src
```
Or:
```bash
cd /path/to/catkin_ws/src
git clone git@github.com:willat343/cppbox.git
```

Then:
```bash
cd /path/to/catkin_ws
catkin build cppbox
```

### Uninstallation

```bash
cd /path/to/catkin_ws
catkin clean cppbox
```

### Include in Downstream Project

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<depend>cppbox</depend>
```
One can then either use the workspace's isolated installation or use the system installation otherwise.
Importing the dependency is then exactly the same as it would be in a non-catkin package as described above (do NOT rely on the `catkin` variables like `catkin_LIBRARIES` and `catkin_INCLUDE_DIRS`).
