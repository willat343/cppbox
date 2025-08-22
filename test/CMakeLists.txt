set(TESTS_NAME ${PROJECT_NAME}_tests)

# Build Example
add_executable(${TESTS_NAME}
    src/traits.cpp
)

# Include Directories
target_include_directories(${TESTS_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../include>
)

# Properties
set_target_properties(${TESTS_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Compile Options
target_compile_options(${TESTS_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
)

# Link Libraries
target_link_libraries(${TESTS_NAME} PUBLIC
    ${LIBRARY_NAME}
    gtest_main
    gtest
    pthread
)

# Add test
add_test(NAME ${TESTS_NAME} COMMAND ${TESTS_NAME})
