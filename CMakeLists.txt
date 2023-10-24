# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# This is the name of the repository
project ("tree")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
    add_compile_options(-Wall -Wextra -Wpedantic -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init -Wlogical-not-parentheses -Wnull-dereference)
endif ()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[tree] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Add the tree project
if ( NOT "${HAS_TREE}")

    # Log
    message("[tree] Adding tree project")

    # Let any parent project know that it has the tree project
    set(HAS_TREE true PARENT_SCOPE)
endif()

# Add source to this project's executable.
add_executable (tree_example "main.c")
add_dependencies(tree_example sync tree)
target_include_directories(tree_example PUBLIC include include/tree ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(tree_example sync tree)

# Add source to the tester
# add_executable (tree_test "tree_test.c")
# add_dependencies(tree_test sync tree)
# target_include_directories(tree_test PUBLIC include)
# target_link_libraries(tree_test sync tree)

# Add source to this project's library
add_library (tree SHARED "tree.c" "binary.c" "b.c" "redblack.c")
add_dependencies(tree sync)
target_include_directories(tree PUBLIC include include/tree ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(tree sync)