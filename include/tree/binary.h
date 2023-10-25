/** !
 * Include header for unbalanced binary search tree

 * @file tree/binary.h 
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

// tree
#include <tree/tree.h>

// Forward declarations
struct binary_tree_s;
struct binary_tree_node_s;

// Type definitions
typedef struct binary_tree_s binary_tree;
typedef struct binary_tree_node_s binary_tree_node;

// Struct definitions
struct binary_tree_node_s
{ 
    void             *p_key,
                     *p_value;
    binary_tree_node *p_left,
                     *p_right;
};

struct binary_tree_s
{
    binary_tree_node *p_root;
    tree_equal_fn    *pfn_is_equal;
};

// Allocators
/** !
 * Allocate memory for a binary tree
 * 
 * @param pp_binary_tree return
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_create ( binary_tree **const pp_binary_tree );

// Constructors
/** !
 * Construct an empty binary tree
 * 
 * @param pp_binary_tree return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_construct ( binary_tree **const pp_binary_tree, tree_equal_fn *pfn_is_equal );

// Accessors
/** !
 * Search a binary tree for an element
 * 
 * @param p_binary_tree the binary tree
 * @param p_value       the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_search ( const binary_tree *const p_binary_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert an element into a binary tree
 * 
 * @param p_binary_tree the binary tree
 * @param p_value       the element
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_insert ( binary_tree *const p_binary_tree, const void *const p_key, const void *const p_value );

/** !
 * Remove an element from a binary tree
 * 
 * @param p_binary_tree the binary tree
 * @param p_key         the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_remove ( binary_tree *const p_binary_tree, void *p_key, void **p_value );

/** !
 * Deallocate a binary tree
 * 
 * @param pp_binary_tree pointer to binary tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_destroy ( binary_tree **const pp_binary_tree );
