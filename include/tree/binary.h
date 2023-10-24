/** !
 * Include header for binary tree

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
    void             *data;
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

// Mutators
/** !
 * Insert an element into a binary tree
 * 
 * @param p_binary_tree the binary tree
 * @param p_value       the element
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_insert ( binary_tree *const p_binary_tree, void *p_value );

