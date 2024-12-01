﻿/** !
 * Include header for Red-Black tree

 * @file tree/red_black.h 
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
struct red_black_tree_s;
struct red_black_tree_node_s;

// Type definitions
/** !
 *  @brief The type definition for a red_black tree
 */
typedef struct red_black_tree_s red_black_tree;

/** !
 *  @brief The type definition for a red_black tree node
 */
typedef struct red_black_tree_node_s red_black_tree_node;

/** !
 *  @brief The type definition for a function that serializes a node to a file
 * 
 *  @param p_file             the file
 *  @param p_red_black_tree_node the red_black tree node
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_red_black_tree_serialize)(FILE *p_file, red_black_tree_node *p_red_black_tree_node);

/** !
 *  @brief The type definition for a function that parses a node from a file
 * 
 *  @param p_file              the file
 *  @param p_red_black_tree       the red_black tree node
 *  @param pp_red_black_tree_node return
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_red_black_tree_parse)(FILE *p_file, red_black_tree_node *p_red_black_tree_node );

/** !
 *  @brief The type definition for a function that is called on each node while traversing a tree
 * 
 *  @param p_value the value
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_red_black_tree_traverse)(void *p_value);

// Struct definitions
struct red_black_tree_node_s
{ 
    void *p_value;
    int height;
    red_black_tree_node *p_left,
                        *p_right;
    unsigned long long  node_pointer;
};

struct red_black_tree_s
{
    mutex _lock;
    red_black_tree_node *p_root;
    FILE          *p_random_access;
    
    struct 
    {
        fn_tree_comparator         *pfn_is_equal;
        fn_tree_key_accessor  *pfn_key_accessor;
        fn_red_black_tree_serialize *pfn_serialize_node;
        fn_red_black_tree_parse     *pfn_parse_node;
    } functions;

    struct 
    {
        unsigned long long node_quantity;
        unsigned long long node_size;
    } metadata;
};

// Constructors
/** !
 * Construct an empty red_black tree
 * 
 * @param pp_red_black_tree return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_construct ( red_black_tree **const pp_red_black_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );

/** !
 * Construct a balanced red_black tree from a sorted list of keys and values. 
 * 
 * @param pp_red_black_tree    return
 * @param pp_values         the list of values
 * @param property_quantity the size of the list
 * @param pfn_is_equal      function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size         the size of a serialized node in bytes
 * 
*/
int red_black_tree_construct_balanced ( red_black_tree **const pp_red_black_tree, void **pp_values, size_t property_quantity, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );

// Accessors
/** !
 * Search a red_black tree for an element
 * 
 * @param p_red_black_tree the red_black tree
 * @param p_value       the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_search ( const red_black_tree *const p_red_black_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert a property into a red_black tree
 * 
 * @param p_red_black_tree the red_black tree
 * @param p_value       the property value
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_insert ( red_black_tree *const p_red_black_tree, const void *const p_value );

/** !
 * Remove an element from a red_black tree
 * 
 * @param p_red_black_tree the red_black tree
 * @param p_key         the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_remove ( red_black_tree *const p_red_black_tree, const void *const p_key, const void **const p_value );

// Traversal
/** !
 * Traverse a red_black tree using the pre order technique
 * 
 * @param p_red_black_tree pointer to red_black tree
 * @param pfn_traverse  called for each node in the red_black tree
 * 
 * @return 1 on success, 0 on error
*/
int red_black_tree_traverse_preorder ( red_black_tree *const p_red_black_tree, fn_red_black_tree_traverse *pfn_traverse );

/** !
 * Traverse a red_black tree using the in order technique
 * 
 * @param p_red_black_tree pointer to red_black tree
 * @param pfn_traverse  called for each node in the red_black tree
 * 
 * @return 1 on success, 0 on error
*/
int red_black_tree_traverse_inorder ( red_black_tree *const p_red_black_tree, fn_red_black_tree_traverse *pfn_traverse );

/** !
 * Traverse a red_black tree using the post order technique
 * 
 * @param p_red_black_tree pointer to red_black tree
 * @param pfn_traverse  called for each node in the red_black tree
 * 
 * @return 1 on success, 0 on error
*/
int red_black_tree_traverse_postorder ( red_black_tree *const p_red_black_tree, fn_red_black_tree_traverse *pfn_traverse );

// Parser
/** !
 * Construct a red_black tree from a file
 * 
 * @param pp_red_black_tree return
 * @param p_file         path to the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_parse ( red_black_tree **const pp_red_black_tree, const char *p_file, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_tree_key_accessor, fn_red_black_tree_parse *pfn_parse_node );

// Serializer
/** !
 * Write a red_black tree to a file
 * 
 * @param p_red_black_tree      the red_black tree 
 * @param p_path             path to the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_serialize ( red_black_tree *const p_red_black_tree, const char *p_path, fn_red_black_tree_serialize *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a red_black tree
 * 
 * @param pp_red_black_tree pointer to red_black tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int red_black_tree_destroy ( red_black_tree **const pp_red_black_tree );
