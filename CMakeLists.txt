cmake_minimum_required(VERSION 3.21)
project(cppbox
    VERSION 0.1.3
    DESCRIPTION "Collection of general-purpose C++ functions, classes and utilities"
    LANGUAGES CXX
)

## Include Standard CMake Packages
# GNUInstallDirs for Install directories
include(GNUInstallDirs)
# FetchContent for dependencies
include(FetchContent)
# CTest for BUILD_TESTING option (default ON)
include(CTest)
# Package version and config file generation
include(CMakePackageConfigHelpers)

# General Options
option(BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF)
option(BUILD_SHARED_LIBS "Build shared library (if CPPBOX_HEADER_ONLY=OFF)" OFF)
option(CPPBOX_HEADER_ONLY "Build library as header-only" OFF)
option(DEVELOPER_MODE "Use local versions of cmakebox" OFF)

# Configure FetchContent source directories for DEVELOPER_MODE
if (DEVELOPER_MODE)
    set(FETCHCONTENT_SOURCE_DIR_CMAKEBOX "${CMAKE_SOURCE_DIR}/dependencies/cmakebox")
endif()

# Dependency: cmakebox
set(CMAKEBOX_VERSION "0.0.3")
FetchContent_Declare(
    cmakebox
    GIT_REPOSITORY git@github.com:willat343/cmakebox.git
    GIT_TAG v${CMAKEBOX_VERSION}
)
FetchContent_MakeAvailable(cmakebox)
list(APPEND CMAKE_MODULE_PATH "${cmakebox_SOURCE_DIR}/cmake")
include(CMakeBox)

# CMake Build Type
setup_build_type()

# Get CXX Compiler Information
get_cxx_compiler_info()

# Build Library
set(LIBRARY_NAME ${PROJECT_NAME})
if (CPPBOX_HEADER_ONLY)
    # Interface Library
    add_library(${LIBRARY_NAME} INTERFACE)
    target_compile_definitions(${LIBRARY_NAME} INTERFACE CPPBOX_HEADER_ONLY=1)
    set(PUBLIC_OR_INTERFACE INTERFACE)
else()
    # Shared/Static Library (determined by BUILD_SHARED_LIBS)
    add_library(${LIBRARY_NAME}
        src/bytes.cpp
        src/parse.cpp
    )
    target_compile_definitions(${LIBRARY_NAME} PUBLIC CPPBOX_HEADER_ONLY=0)
    set(PUBLIC_OR_INTERFACE PUBLIC)

    # Private Compile Options
    target_compile_options(${LIBRARY_NAME} PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()
add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

# Include Directories
target_include_directories(${LIBRARY_NAME} ${PUBLIC_OR_INTERFACE}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Properties
set_target_properties(${LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

# Public Compile Options
if (CMAKE_CXX_COMPILER_VERSION_MAJOR EQUAL 9)
    # Add experimental concepts flag
    target_compile_options(${LIBRARY_NAME} ${PUBLIC_OR_INTERFACE} -fconcepts)
endif()

# Configure package version and config files
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Installation
install(
    TARGETS ${LIBRARY_NAME}
    EXPORT ${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
    EXPORT ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}-export.cmake
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING
        PATTERN "*.hpp"
        PATTERN "*.h"
)

# Build-Tree Export
export(
    EXPORT ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-export.cmake"
)
export(PACKAGE ${PROJECT_NAME})

# Uninstallation
create_uninstall_target()

## Additional Builds
# Build Documentation
if (BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    configure_file(Doxyfile.in ${DOXYGEN_OUT})
    add_custom_target(documentation ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with doxygen."
        VERBATIM
    )
endif()

# Build Tests
if (BUILD_TESTS)
    add_subdirectory(test)
endif()
