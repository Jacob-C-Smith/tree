/** !
 * Include header for merkle tree

 * @file tree/merkle.h 
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

// sync module
#include <sync/sync.h>

// hash cache module
#include <hash_cache/hash_cache.h>
#include <hash_cache/hash.h>

// tree
#include <tree/tree.h>

// Forward declarations
struct merkle_tree_s;
struct merkle_tree_node_s;

// Type definitions
/** !
 *  @brief The type definition for a merkle tree
 */
typedef struct merkle_tree_s merkle_tree;

/** !
 *  @brief The type definition for a merkle tree node
 */
typedef struct merkle_tree_node_s merkle_tree_node;

/** !
 *  @brief The type definition for a function that serializes a node to a file
 * 
 *  @param p_file             the file
 *  @param p_merkle_tree_node the merkle tree node
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_merkle_tree_serialize)(FILE *p_file, merkle_tree_node *p_merkle_tree_node);

/** !
 *  @brief The type definition for a function that parses a node from a file
 * 
 *  @param p_file              the file
 *  @param p_merkle_tree       the merkle tree node
 *  @param pp_merkle_tree_node return
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_merkle_tree_parse)(FILE *p_file, merkle_tree_node *p_merkle_tree_node );

/** !
 *  @brief The type definition for a function that is called on each node while traversing a tree
 * 
 *  @param p_value the value
 *  @param p_hash  the hash
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_merkle_tree_traverse)(void *p_value, hash64 _hash, bool leaf);

// Struct definitions
struct merkle_tree_node_s
{ 
    bool leaf;
    void *p_value;
    hash64 _hash;
    merkle_tree_node *p_left,
                     *p_right;
    unsigned long long node_pointer;
};

struct merkle_tree_s
{
    mutex _lock;
    merkle_tree_node *p_root;
    FILE             *p_random_access;
    
    struct 
    {
        fn_tree_comparator            *pfn_is_equal;
        fn_tree_key_accessor     *pfn_key_accessor;
        fn_hash64                *pfn_hash_function;
        fn_merkle_tree_serialize *pfn_serialize_node;
        fn_merkle_tree_parse     *pfn_parse_node;
    } functions;

    struct 
    {
        unsigned long long internal_node_quantity;
        unsigned long long leaf_node_quantity;
        unsigned long long node_size;
    } metadata;

    merkle_tree_node *_p_leaves[];
};

// Constructors
/** !
 * Construct an empty merkle tree
 * 
 * @param pp_merkle_tree return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_construct ( merkle_tree **const pp_merkle_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, fn_hash64 *pfn_hash_function, unsigned long long node_size );

// Accessors
/** !
 * Search a binary tree for an element
 * 
 * @param p_merkle_tree the binary tree
 * @param p_value       the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_search ( const merkle_tree *const p_merkle_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert a property into a binary tree
 * 
 * @param p_merkle_tree the binary tree
 * @param p_value       the property value
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_insert ( merkle_tree *const p_merkle_tree, const void *const p_value );

/** !
 * Remove an element from a binary tree
 * 
 * @param p_merkle_tree the binary tree
 * @param p_key         the element
 * @param pp_value      return
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_remove ( merkle_tree *const p_merkle_tree, const void *const p_key, const void **const p_value );

// Traversal
/** !
 * Traverse a binary tree using the pre order technique
 * 
 * @param p_merkle_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int merkle_tree_traverse_preorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse );

/** !
 * Traverse a binary tree using the in order technique
 * 
 * @param p_merkle_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int merkle_tree_traverse_inorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse );

/** !
 * Traverse a binary tree using the post order technique
 * 
 * @param p_merkle_tree pointer to binary tree
 * @param pfn_traverse  called for each node in the binary tree
 * 
 * @return 1 on success, 0 on error
*/
int merkle_tree_traverse_postorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse );

// Parser
/** !
 * Construct a binary tree from a file
 * 
 * @param pp_merkle_tree return
 * @param p_file         path to the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_parse ( merkle_tree **const pp_merkle_tree, const char *p_file, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_tree_key_accessor, fn_merkle_tree_parse *pfn_parse_node );

// Serializer
/** !
 * Write a binary tree to a file
 * 
 * @param p_merkle_tree      the binary tree 
 * @param p_path             path to the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_serialize ( merkle_tree *const p_merkle_tree, const char *p_path, fn_merkle_tree_serialize *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a binary tree
 * 
 * @param pp_merkle_tree pointer to binary tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int merkle_tree_destroy ( merkle_tree **const pp_merkle_tree );
