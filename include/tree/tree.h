/** !
 * Include header for tree library
 * 
 * @file tree/tree.h 
 * 
 * @author Jacob Smith
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// sync submodule
#include <sync/sync.h>

// Platform dependent macros
#ifdef _WIN64
    #define DLLEXPORT extern __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

// Memory management macro
#ifndef TREE_REALLOC
    #define TREE_REALLOC(p, sz) realloc(p,sz)
#endif

// Type definitions
/** !
 *  @brief The type definition for a function that tests the equality of two set members
 */
typedef int (tree_equal_fn)(const void *a, const void *b);
