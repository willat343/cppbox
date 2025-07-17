# Build Example
add_executable(cppbox_tests
    src/traits.cpp
)

# Include Directories
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../include>
    # $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# Properties
set_target_properties(cppbox_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Compile Options
target_compile_options(cppbox_tests PRIVATE
    -Wall -Wextra -Wpedantic
)

# Link Libraries
target_link_libraries(cppbox_tests PUBLIC
    ${PROJECT_NAME}
    gtest_main
    gtest
    pthread
)

# Add test
add_test(NAME cppbox_tests COMMAND cppbox_tests)
