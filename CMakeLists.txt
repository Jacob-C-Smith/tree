# Need CMake 3.16.0
cmake_minimum_required (VERSION 3.16.0)

# This is the name of the repository
project ("tree")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Set compiler warnings
if(MSVC)
    # TODO
else()

    # For clang
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt -std=gnu99 -Wall -Wextra  -Weverything -Wno-declaration-after-statement -Ofast")

    # For GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -O3 -pthread -lpthread")
    add_compile_definitions(__USE_POSIX199309)
    add_compile_options(-Wall -Wextra -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -pthread -lpthread -Wlogical-not-parentheses -Wnull-dereference)
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Build sync with timer
add_compile_definitions(BUILD_SYNC_WITH_TIMER)

# Build sync with mutex
add_compile_definitions(BUILD_SYNC_WITH_MUTEX)

# Find the log module
if ( NOT "${HAS_LOG}")
    
    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")
    
    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the tuple module
if ( NOT "${HAS_TUPLE}")
    
    # Add the tuple directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/tuple ${CMAKE_SOURCE_DIR}/build/tuple)

    # Let any parent project know that this project has tuple
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_TUPLE true PARENT_SCOPE)
        set(TUPLE_INCLUDE_DIR ${TUPLE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add the tree project
if ( NOT "${HAS_TREE}")

    set (TREE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the tree project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_TREE true PARENT_SCOPE)
        set(TREE_INCLUDE_DIR ${TREE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable (tree_example "main.c")
add_dependencies(tree_example tree tuple sync log)
target_include_directories(tree_example PUBLIC ${TREE_INCLUDE_DIR} ${TUPLE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(tree_example tree tuple sync log)

# Add source to the tester
# add_executable (tree_test "tree_test.c")
# add_dependencies(tree_test sync tree)
# target_include_directories(tree_test PUBLIC include)
# target_link_libraries(tree_test sync tree)

# Add source to this project's library
add_library (tree SHARED "tree.c" "avl.c" "b.c" "binary.c" "quad.c" "rectangle.c" "redblack.c")
add_dependencies(tree tuple sync log)
target_include_directories(tree PUBLIC ${TREE_INCLUDE_DIR} ${TUPLE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(tree tuple sync log)