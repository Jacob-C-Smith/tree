/** !
 * Include header for search tree. 
 * 
 * Search trees are one of (AVL, Binary, Red-Black)
 * 
 * @file tree/search.h 
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
#include <tree/avl.h>
#include <tree/binary.h>
#include <tree/red_black.h>

// Enumeration definitions
enum search_tree_type_e
{
    SEARCH_TREE_CUSTOM    = 0,
    SEARCH_TREE_AVL       = 1,
    SEARCH_TREE_BINARY    = 2,
    SEARCH_TREE_RED_BLACK = 3,
    FREQUENT_ACCESS       = SEARCH_TREE_AVL,
    FREQUENT_MUTATE       = SEARCH_TREE_RED_BLACK,
    NO_BALANCING          = SEARCH_TREE_BINARY,
    SEARCH_TREE_QUANTITY  = 4
};

enum search_tree_create_info_e
{
    SEARCH_TREE_CREATE_INFO_NODE_IDENTITY,
    SEARCH_TREE_CREATE_INFO_NODE_SERIALIZERS,
    SEARCH_TREE_CREATE_INFO_ACCESSORS,
    SEARCH_TREE_CREATE_INFO_TRAVERSAL
};

// Forward declarations
struct search_tree_s;
struct search_tree_node_s;

// Type definitions
typedef struct search_tree_s search_tree;
typedef struct search_tree_node_s search_tree_node;
typedef int (fn_search_tree_serialize)(FILE *p_file, search_tree_node *p_search_tree_node);
typedef int (fn_search_tree_parse)(FILE *p_file, search_tree_node *p_search_tree_node );
typedef int (fn_search_tree_traverse)(void *p_value);

typedef int (fn_search_tree_construct) ( void **const pp_search_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );
typedef int (fn_search_tree_insert) ( void *p_search_tree, void *p_value );
typedef int (fn_search_tree_search) ( void *p_search_tree, void *p_key, void **pp_value );
typedef int (fn_search_tree_remove) ( void *p_search_tree, void *p_key, void **pp_value );
typedef int (fn_search_tree_traverse_inorder)   ( void *p_search_tree, fn_binary_tree_traverse *pfn_binary_tree_traverse );
typedef int (fn_search_tree_traverse_preorder)  ( void *p_search_tree, fn_binary_tree_traverse *pfn_binary_tree_traverse );
typedef int (fn_search_tree_traverse_postorder) ( void *p_search_tree, fn_binary_tree_traverse *pfn_binary_tree_traverse );

typedef struct
{
    enum search_tree_create_info_e _type;
    struct
    {
        fn_tree_comparator   *pfn_is_equal;
        fn_tree_key_accessor *pfn_key_accessor;
        unsigned long long    node_size;
    };
    void *p_next;
} tree_create_identity;

typedef struct
{
    enum search_tree_create_info_e _type;
    struct
    {
        fn_tree_serialize *pfn_serialize;
        fn_tree_parse     *pfn_parse;
    } value;
    void *p_next;
} tree_create_serializer;

typedef struct
{
    enum search_tree_create_info_e _type;
    struct
    {
        fn_tree_insert *pfn_insert;
        fn_tree_search *pfn_search;
        fn_tree_remove *pfn_remove;
    };
    void *p_next;
} tree_create_accessors;

typedef struct
{
    enum search_tree_create_info_e _type;
    struct
    {
        fn_tree_traverse_inorder   *pfn_inorder;
        fn_tree_traverse_preorder  *pfn_preorder;
        fn_tree_traverse_postorder *pfn_postorder;
    } traverse;
    void *p_next;
} tree_create_traversal;

// Constructors
/** !
 * Construct an empty binary tree
 * 
 * @param pp_search_tree return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_construct ( search_tree **const pp_search_tree, enum search_tree_type_e _type, void *p_tree_create_info_chain );

/** !
 * Construct a balanced binary tree from a sorted list of keys and values. 
 * 
 * @param pp_search_tree    return
 * @param pp_values         the list of values
 * @param property_quantity the size of the list
 * @param pfn_is_equal      function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size         the size of a serialized node in bytes
 * 
*/
int search_tree_construct_balanced ( search_tree **const pp_search_tree, void **pp_values, size_t property_quantity, enum search_tree_type_e _type, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );

// Accessors
/** !
 * Search a binary tree for an element
 * 
 * @param p_search_tree the binary tree
 * @param p_value       the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_search ( const search_tree *const p_search_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert a property into a binary tree
 * 
 * @param p_search_tree the binary tree
 * @param p_value       the property value
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_insert ( search_tree *const p_search_tree, const void *const p_value );

/** !
 * Remove an element from a binary tree
 * 
 * @param p_search_tree the binary tree
 * @param p_key         the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_remove ( search_tree *const p_search_tree, const void *const p_key, const void **const p_value );

// Traversal
/** !
 * Traverse a binary tree using the pre order technique
 * 
 * @param p_search_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int search_tree_traverse_preorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse );

/** !
 * Traverse a binary tree using the in order technique
 * 
 * @param p_search_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int search_tree_traverse_inorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse );

/** !
 * Traverse a binary tree using the post order technique
 * 
 * @param p_search_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int search_tree_traverse_postorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse );

// Parser
/** !
 * Construct a binary tree from a file
 * 
 * @param pp_search_tree return
 * @param p_file         path to the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_parse ( search_tree **const pp_search_tree, const char *p_file, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_tree_key_accessor, fn_search_tree_parse *pfn_parse_node );

// Serializer
/** !
 * Write a binary tree to a file
 * 
 * @param p_search_tree      the binary tree 
 * @param p_path             path to the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_serialize ( search_tree *const p_search_tree, const char *p_path, fn_search_tree_serialize *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a binary tree
 * 
 * @param pp_search_tree pointer to binary tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int search_tree_destroy ( search_tree **const pp_search_tree );
