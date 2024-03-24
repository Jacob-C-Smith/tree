/** !
 * Include header for rectangle tree
 * 
 * @file tree/rectangle.h 
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

// sync 
#include <sync/sync.h>

// tuple
#include <tuple/tuple.h>

// tree
#include <tree/tree.h>

// Forward declarations
struct rectangle_tree_s;
struct rectangle_tree_node_s;

// Type definitions
/** !
 *  @brief The type definition for an r tree
 */
typedef struct rectangle_tree_s rectangle_tree;

/** !
 *  @brief The type definition for an r tree node
 */
typedef struct rectangle_tree_node_s rectangle_tree_node;

/** !
 *  @brief The type definition for a function that serializes a node to a file
 * 
 *  @param p_file                the file
 *  @param p_rectangle_tree_node the rectangle tree node
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (rectangle_tree_serialize_fn)(FILE *p_file, rectangle_tree_node *p_rectangle_tree_node);

/** !
 *  @brief The type definition for a function that parses a node from a file
 * 
 *  @param p_file         the file
 *  @param p_rectangle_tree       the rectangle tree node
 *  @param pp_rectangle_tree_node return
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (rectangle_tree_parse_fn)(FILE *p_file, rectangle_tree *p_rectangle_tree, rectangle_tree_node **pp_rectangle_tree_node, unsigned long long node_pointer );

// Struct definitions
struct rectangle_tree_node_s
{ 
    bool               leaf;
    int                key_quantity;
    unsigned long long node_pointer;
};

struct rectangle_tree_s
{
    rectangle_tree_node *p_root;
    FILE        *p_random_access;

    struct 
    {
        tree_equal_fn       *pfn_is_equal;
        rectangle_tree_serialize_fn *pfn_serialize_node;
        rectangle_tree_parse_fn     *pfn_parse_node;
    } functions;

    struct 
    {
        unsigned long long node_quantity,
                           root_address;
        int node_size,
            key_quantity,
            degree,
            height;
    } metadata;
};

// Allocators
/** !
 * Allocate memory for a r tree
 * 
 * @param pp_rectangle_tree return
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_create ( rectangle_tree **const pp_rectangle_tree );

// Constructors
/** !
 * Construct an empty rectangle tree
 * 
 * @param pp_rectangle_tree      return
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param degree         the degree of the rectangle tree
 * @param node_size      the size of a serialized node in bytes
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_construct ( rectangle_tree **const pp_rectangle_tree, tree_equal_fn *pfn_is_equal, int degree, unsigned long long node_size );

// Accessors
/** !
 * Search a rectangle tree for an element
 * 
 * @param p_rectangle_tree the rectangle tree
 * @param p_value  the element
 * @param pp_value return
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_search ( const rectangle_tree *const p_rectangle_tree, const void *const p_key, const void **const pp_value );

// Mutators
/** !
 * Insert a property into a rectangle tree
 * 
 * @param p_rectangle_tree the rectangle tree
 * @param p_key    the property key
 * @param p_value  the property value
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_insert ( rectangle_tree *const p_rectangle_tree, const void *const p_key, const void *const p_value );

/** !
 * Remove an element from a rectangle tree
 * 
 * @param p_rectangle_tree the rectangle tree
 * @param p_key    the element
 * @param pp_value return
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_remove ( rectangle_tree *const p_rectangle_tree, const void *const p_key, const void **const p_value );

// Parser
/** !
 * Construct a rectangle tree from a file
 * 
 * @param pp_rectangle_tree      return
 * @param p_file         the file
 * @param pfn_is_equal   function for testing equality of elements in set IF parameter is not null ELSE default
 * @param pfn_parse_node a function for parsing nodes from the file
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_parse ( rectangle_tree **const pp_rectangle_tree, FILE *p_file, tree_equal_fn *pfn_is_equal, rectangle_tree_parse_fn *pfn_parse_node );

// Serializer
/** !
 * Write a rectangle tree to a file
 * 
 * @param p_rectangle_tree           the rectangle tree 
 * @param p_path             path to the file
 * @param pfn_serialize_node a function for serializing nodes to the file
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_serialize ( rectangle_tree *const p_rectangle_tree, const char *p_path, rectangle_tree_serialize_fn *pfn_serialize_node );

// Destructors
/** !
 * Deallocate a rectangle tree
 * 
 * @param pp_rectangle_tree pointer to rectangle tree pointer
 * 
 * @return 1 on success, 0 on error
 */
int rectangle_tree_destroy ( rectangle_tree **const pp_rectangle_tree );
