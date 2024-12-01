/** !
 * Include header for Adelson-Velsky and Landis tree

 * @file tree/avl.h 
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
struct avl_tree_s;
struct avl_tree_node_s;

// Type definitions
/** !
 *  @brief The type definition for a avl tree
 */
typedef struct avl_tree_s avl_tree;

/** !
 *  @brief The type definition for a avl tree node
 */
typedef struct avl_tree_node_s avl_tree_node;

/** !
 *  @brief The type definition for a function that serializes a node to a file
 * 
 *  @param p_file             the file
 *  @param p_avl_tree_node the avl tree node
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_avl_tree_serialize)(FILE *p_file, avl_tree_node *p_avl_tree_node);

/** !
 *  @brief The type definition for a function that parses a node from a file
 * 
 *  @param p_file              the file
 *  @param p_avl_tree       the avl tree node
 *  @param pp_avl_tree_node return
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_avl_tree_parse)(FILE *p_file, avl_tree_node *p_avl_tree_node );

/** !
 *  @brief The type definition for a function that is called on each node while traversing a tree
 * 
 *  @param p_value the value
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_avl_tree_traverse)(void *p_value);

// Struct definitions
struct avl_tree_node_s
{ 
    void *p_value;
    int height;
    avl_tree_node *p_left,
                  *p_right;
    unsigned long long  node_pointer;
};

struct avl_tree_s
{
    mutex _lock;
    avl_tree_node *p_root;
    FILE          *p_random_access;
    
    struct 
    {
        fn_tree_comparator    *pfn_is_equal;
        fn_tree_key_accessor  *pfn_key_accessor;
        fn_avl_tree_serialize *pfn_serialize_node;
        fn_avl_tree_parse     *pfn_parse_node;
    } functions;

    struct 
    {
        unsigned long long node_quantity;
        unsigned long long node_size;
    } metadata;
};

// Constructors
/** !
 * Construct an empty avl tree
 * 
 * @param pp_avl_tree return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_construct ( avl_tree **const pp_avl_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );

/** !
 * Construct a balanced avl tree from a sorted list of keys and values. 
 * 
 * @param pp_avl_tree    return
 * @param pp_values         the list of values
 * @param property_quantity the size of the list
 * @param pfn_is_equal      function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size         the size of a serialized node in bytes
 * 
*/
int avl_tree_construct_balanced ( avl_tree **const pp_avl_tree, void **pp_values, size_t property_quantity, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );

// Accessors
/** !
 * Search a avl tree for an element
 * 
 * @param p_avl_tree the avl tree
 * @param p_value       the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_search ( const avl_tree *const p_avl_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert a property into a avl tree
 * 
 * @param p_avl_tree the avl tree
 * @param p_value       the property value
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_insert ( avl_tree *const p_avl_tree, const void *const p_value );

/** !
 * Remove an element from a avl tree
 * 
 * @param p_avl_tree the avl tree
 * @param p_key         the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_remove ( avl_tree *const p_avl_tree, const void *const p_key, const void **const p_value );

// Traversal
/** !
 * Traverse a avl tree using the pre order technique
 * 
 * @param p_avl_tree pointer to avl tree
 * @param pfn_traverse  called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_preorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse );

/** !
 * Traverse a avl tree using the in order technique
 * 
 * @param p_avl_tree pointer to avl tree
 * @param pfn_traverse  called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_inorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse );

/** !
 * Traverse a avl tree using the post order technique
 * 
 * @param p_avl_tree pointer to avl tree
 * @param pfn_traverse  called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_postorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse );

// Parser
/** !
 * Construct a avl tree from a file
 * 
 * @param pp_avl_tree return
 * @param p_file         path to the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_parse ( avl_tree **const pp_avl_tree, const char *p_file, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_tree_key_accessor, fn_avl_tree_parse *pfn_parse_node );

// Serializer
/** !
 * Write a avl tree to a file
 * 
 * @param p_avl_tree      the avl tree 
 * @param p_path             path to the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_serialize ( avl_tree *const p_avl_tree, const char *p_path, fn_avl_tree_serialize *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a avl tree
 * 
 * @param pp_avl_tree pointer to avl tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_destroy ( avl_tree **const pp_avl_tree );
