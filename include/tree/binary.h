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
/** !
 *  @brief The type definition for a binary tree
 */
typedef struct binary_tree_s binary_tree;

/** !
 *  @brief The type definition for a binary tree node
 */
typedef struct binary_tree_node_s binary_tree_node;

/** !
 *  @brief The type definition for a function that serializes a node
 */
typedef int (binary_tree_serialize_fn)(FILE *p_file, binary_tree_node *p_binary_tree_node);

/** !
 *  @brief The type definition for a function that parses a node
 */
typedef int (binary_tree_parse_fn)(FILE *p_file, binary_tree *p_binary_tree, binary_tree_node **pp_binary_tree_node, unsigned long long node_pointer );

// Struct definitions
struct binary_tree_node_s
{ 
    void               *p_key,
                       *p_value;
    binary_tree_node   *p_left,
                       *p_right;
    unsigned long long  node_pointer;
};

struct binary_tree_s
{
    binary_tree_node *p_root;

    struct 
    {
        tree_equal_fn            *pfn_is_equal;
        binary_tree_serialize_fn *pfn_serialize_node;
        binary_tree_parse_fn     *pfn_parse_node;
    } functions;

    struct 
    {
        unsigned long long node_quantity;
        unsigned long long node_size;
    } metadata;
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
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_construct ( binary_tree **const pp_binary_tree, tree_equal_fn *pfn_is_equal, unsigned long long node_size );

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
 * Insert a property into a binary tree
 * 
 * @param p_binary_tree the binary tree
 * @param p_key         the property key
 * @param p_value       the property value
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
int binary_tree_remove ( binary_tree *const p_binary_tree, const void *const p_key, const void **const p_value );

// Parser
/** !
 * Construct a binary tree from a file
 * 
 * @param pp_binary_tree return
 * @param p_file         the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_parse ( binary_tree **const pp_binary_tree, FILE *p_file, tree_equal_fn *pfn_is_equal, binary_tree_parse_fn *pfn_parse_node );

// Serializer
/** !
 * Write a binary tree to a file
 * 
 * @param p_binary_tree      the binary tree 
 * @param p_file             the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_serialize ( binary_tree *const p_binary_tree, FILE *p_file, binary_tree_serialize_fn *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a binary tree
 * 
 * @param pp_binary_tree pointer to binary tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_destroy ( binary_tree **const pp_binary_tree );
