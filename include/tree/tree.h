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

// sync module
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

// Enumeration definitions
enum tree_type_e
{
    TREE_CUSTOM    =  0,

    TREE_AVL       =  1,
    TREE_B         =  2,
    TREE_BINARY    =  3,
    TREE_RED_BLACK =  4,

    FREQUENT_ACCESS =  TREE_AVL,
    FREQUENT_MUTATE =  TREE_RED_BLACK,
    BIG_DATA        =  TREE_B,
    NO_BALANCING    =  TREE_BINARY,

    TREE_QUANTITY   =  5,
    TREE_INVALID    = -1
};

enum tree_create_info_e
{
    TREE_CREATE_IDENTITY,
    TREE_CREATE_SERIALIZE,
    TREE_CREATE_ACCESSORS,
    TREE_CREATE_TRAVERSAL,
    TREE_CREATE_VALUES
};

// Forward declarations
struct tree_s;

// Type definitions
typedef struct tree_s tree;

/** !
 *  @brief The type definition for a node comparator function
 * 
 *  @param p_a pointer to a
 *  @param p_b pointer to b
 * 
 *  @return 0 if a == b else -1 if A > B else 1
 */
typedef int (fn_tree_comparator)(const void *const p_a, const void *const p_b);

/** !
 *  @brief The type definition for a function that accesses the key of a given value
 * 
 *  @param p_value the value
 * 
 *  @return 1 on success, 0 on error
 */
typedef const void *(fn_tree_key_accessor)(const void *const p_value);

/** !
 *  @brief The type definition for a function that serializes a tree to a file
 * 
 *  @param p_tree the tree
 *  @param p_path path to the file
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_serialize) ( tree *const p_tree, const char *p_path );

/** !
 *  @brief The type definition for a function that parses a tree from a file
 * 
 *  @param pp_tree the tree
 *  @param p_path  path to the file
 *  @param p_head  pointer to head of constructor chain
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_parse) ( tree **const pp_tree, const char *p_path );

/** !
 *  @brief The type definition for a function that serializes a value to a file.
 *         The value must be serialized sequentially, from [cursor, cursor + node_size]
 * 
 *  @param p_file  the FILE
 *  @param p_key   the key
 *  @param p_value the value
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_value_serializer)(FILE *p_file, void *p_key, void *p_value);








typedef int (fn_tree_value_parser)(FILE *p_file, void **pp_value );

typedef int (fn_tree_traverse)(void *p_value);

typedef int (fn_tree_construct) ( void **const pp_search_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size );






/** !
 *  @brief The type definition for a function that inserts a value into a tree

 *  @param p_tree  the tree
 *  @param p_value the property value
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_insert) ( void *p_tree, void *p_value );

/** !
 *  @brief The type definition for a function that searches a tree for a value
 * 
 *  @param p_tree   the tree
 *  @param p_key    the key
 *  @param pp_value result
 * 
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_search) ( void *p_tree, void *p_key, void **pp_value );

/** !
 *  @brief The type definition for a function that removes a value from a tree
 * 
 *  @param p_tree   the tree
 *  @param p_key    the key
 *  @param pp_value result IF pp_value != null ELSE ignored
 *  
 *  @return 1 on success, 0 on error
 */
typedef int (fn_tree_remove) ( void *p_tree, void *p_key, void **pp_value );

/** !
 *  @brief The type definition for a function that traverss a binary tree using the 
 *  in order technique
 * 
 *  @param p_tree       pointer to tree
 *  @param pfn_traverse pointer to function called for each value in the binary tree
 * 
 *  @return 1 on success, 0 on error
*/
typedef int (fn_tree_traverse_inorder) ( void *p_tree, fn_tree_traverse *pfn_tree_traverse );

/** !
 *  @brief The type definition for a function that traverss a binary tree using the 
 *  pre order technique
 * 
 *  @param p_tree       pointer to tree
 *  @param pfn_traverse pointer to function called for each value in the binary tree
 * 
 *  @return 1 on success, 0 on error
*/
typedef int (fn_tree_traverse_preorder) ( void *p_tree, fn_tree_traverse *pfn_tree_traverse );

/** !
 *  @brief The type definition for a function that traverss a binary tree using the 
 *  post order technique
 * 
 *  @param p_tree       pointer to tree
 *  @param pfn_traverse pointer to function called for each value in the binary tree
 * 
 *  @return 1 on success, 0 on error
*/
typedef int (fn_tree_traverse_postorder) ( void *p_tree, fn_tree_traverse *pfn_tree_traverse );

typedef struct
{
    enum tree_create_info_e _type;
    struct
    {
        fn_tree_comparator   *pfn_comparator;
        fn_tree_key_accessor *pfn_key_accessor;
        unsigned long long    value_size;
    };
    void *p_next;
} tree_create_identity;

typedef struct
{
    enum tree_create_info_e _type;
    struct 
    {
        fn_tree_value_serializer *pfn_value_serialize;
        fn_tree_value_parser     *pfn_value_parse;
    };
    void *p_next;
} tree_create_serializer;

typedef struct
{
    enum tree_create_info_e _type;
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
    enum tree_create_info_e _type;
    struct
    {
        fn_tree_traverse_inorder   *pfn_inorder;
        fn_tree_traverse_preorder  *pfn_preorder;
        fn_tree_traverse_postorder *pfn_postorder;
    } traverse;
    void *p_next;
} tree_create_traversal;

typedef struct
{
    enum tree_create_info_e _type;
    struct
    {
        void   **pp_values;
        size_t   len;
        bool     sorted;
    } traverse;
    void *p_next;
} tree_create_values;

// Structure declarations
struct tree_s
{
    void *p_concrete_tree;

    fn_tree_comparator         *pfn_tree_comparator;
    fn_tree_key_accessor       *pfn_tree_key_accessor;
    fn_tree_value_parser       *pfn_tree_value_parser;
    fn_tree_value_serializer   *pfn_tree_value_serializer;
    fn_tree_serialize          *pfn_tree_serialize;
    fn_tree_search             *pfn_tree_search;
    fn_tree_insert             *pfn_tree_insert;
    fn_tree_remove             *pfn_tree_remove;
    fn_tree_traverse_preorder  *pfn_tree_traverse_preorder;
    fn_tree_traverse_postorder *pfn_tree_traverse_postorder;
    fn_tree_traverse_inorder   *pfn_tree_traverse_inorder;
};

// Function declarations

// Initializer
int tree_init ( void ); 

// Constructor
/** !
 * Tree constructor
 * 
 * @param pp_tree result
 * @param _type   one of < avl | b | binary | red black >
 * @param p_head  pointer to head of constructor chain
 * 
 * @return 1 on success, 0 on error
 */
int tree_construct ( tree **pp_tree, enum tree_type_e _type, tree_create_identity *p_head );

// Comparator
/** !
 * Default comparator
 * 
 * @param p_a pointer to a
 * @param p_b pointer to b
 * 
 * @return 0 if a == b else -1 if a > b else 1
 */
int tree_compare ( const void *const p_a, const void *const p_b );

// Accessors
/** !
 * Default key accessor
 * 
 * @param pp_result result
 * @param p_value   the value to extract the key from
 * 
 * @return 1 on success, 0 on error
 */
const void *tree_key_accessor ( const void *const p_value );

// Value serializers
/** !
 * Default value serializer
 * 
 * @param p_file  the file to serialize to
 * @param p_value the value to write 
 * 
 * @return 1 on success, 0 on error
*/
int tree_serializer ( FILE *p_file, void *p_key, void *p_value );

// Parser
/** !
 * Default value parser
 * 
 * @param p_file  the file to read from
 * @param p_value the value to construct
 * 
 * @return 1 on success, 0 on error
*/
int tree_parser ( FILE *p_file, void **pp_value );

// Serialize
/** ! 
 * 
 * 
 * 
 * 
 * TODO: Document
*/
int tree_serialize ( tree *const p_tree, const char *p_path );

/** !
 * Insert a property into a tree
 * 
 * @param p_tree  the tree
 * @param p_value the value
 * 
 * @return 1 on success, 0 on error
 */
int tree_insert ( tree *p_tree, void *p_value );

// Mutators
/** !
 * Search a tree for an element
 * 
 * @param p_tree   the tree
 * @param p_value  the value
 * @param pp_value result
 * 
 * @return 1 on success, 0 on error
 */
int tree_search ( tree *p_tree, void *p_key, void **pp_valaue );

/** !
 * Remove an element from a tree
 * 
 * @param p_tree   the tree
 * @param p_key    the key
 * @param pp_value result
 * 
 * @return 1 on success, 0 on error
 */
int tree_remove ( tree *p_tree, void *p_key, void **pp_valaue );

/** !
 * Traverse a tree using the pre order technique
 * 
 * @param p_tree       pointer to tree
 * @param pfn_traverse called for each value in the tree
 * 
 * @return 1 on success, 0 on error
*/
int tree_traverse_inorder ( tree *p_tree, fn_tree_traverse *pfn_traverse );

/** !
 * Traverse a tree using the in order technique
 * 
 * @param p_tree       pointer to tree
 * @param pfn_traverse called for each value in the tree
 * 
 * @return 1 on success, 0 on error
*/
int tree_traverse_preorder ( tree *p_tree, fn_tree_traverse *pfn_traverse );

/** !
 * Traverse a tree using the post order technique
 * 
 * @param p_tree       pointer to tree
 * @param pfn_traverse called for each value in the tree
 * 
 * @return 1 on success, 0 on error
*/
int tree_traverse_postorder ( tree *p_tree, fn_tree_traverse *pfn_traverse );
