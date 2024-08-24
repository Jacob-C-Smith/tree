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
 *  @brief The type definition for a two dimensional vector
 */ 
typedef struct { double x, y; } tree_vec2;

/** !
 *  @brief The type definition for a function that tests the equality of two nodes
 * 
 *  @param p_a pointer to a
 *  @param p_b pointer to b
 * 
 *  @return 0 if a == b else -1 if A > B else 1
 */
typedef int (fn_tree_equal)(const void *const p_a, const void *const p_b);


// Initializer
int tree_init ( void ); 

// Comparator
/** !
 * Compare a to b
 * 
 * @param p_a pointer to a
 * @param p_b pointer to b
 * 
 * @return 0 if a == b else -1 if a > b else 1
 */
int tree_compare_function ( const void *const p_a, const void *const p_b );
