/** !
 * Implementation of Adelson-Velsky and Landis tree
 * Thank you, Soviet Union. 
 * 
 * @file avl.c
 * 
 * @author Jacob Smith
 */

#include <tree/avl.h>

// Static data
static const unsigned long long eight_bytes_of_zero = 0;

// Forward declarations
/** !
 * Allocate memory for an avl tree
 * 
 * @param pp_avl_tree return
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_create ( avl_tree **const pp_avl_tree );

/** !
 * Allocate memory for an avl tree node
 * 
 * @param pp_avl_tree_node return
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_node_create ( avl_tree_node **pp_avl_tree_node );

/** !
 * Allocate a node for a specific avl tree, and set the node pointer. 
 * 
 * The node pointer is an integer ordinal that is atomically incremented 
 * each time the allocator is called. 
 * 
 * @param p_avl_tree       the avl tree to allocate a node to
 * @param pp_avl_tree_node return
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_node_allocate ( avl_tree *p_avl_tree, avl_tree_node **pp_avl_tree_node );

/** !
 * Recursively construct a balanced avl search tree from a sorted list of keys and values
 * 
 * @param p_avl_tree the avl tree
 * @param pp_values     the list of values
 * @param start         the starting index 
 * @param end           the ending index
 * 
 * @return the root node 
 */
avl_tree_node *avl_tree_construct_balanced_recursive ( avl_tree *p_avl_tree, void **pp_values, size_t start, size_t end );

/** !
 * Recursively serialize avl tree nodes to a file
 * 
 * @param p_file                    the file
 * @param p_avl_tree             the avl tree
 * @param p_avl_tree_node        the avl tree node
 * @param pfn_avl_tree_serialize the node serializer function
 * 
 * @return 1 on success, 0 on error 
 */
int avl_tree_serialize_node ( FILE *p_file, avl_tree *p_avl_tree, avl_tree_node *p_avl_tree_node, fn_avl_tree_serialize *pfn_avl_tree_serialize );

/** !
 * Recursively parse avl tree nodes from a file
 * 
 * @param p_file                    the file
 * @param p_avl_tree             the avl tree
 * @param pp_avl_tree_node       result
 * @param pfn_avl_tree_serialize the node parser function
 * 
 * @return 1 on success, 0 on error 
 */
int avl_tree_parse_node ( FILE *p_file, avl_tree *p_avl_tree, avl_tree_node **pp_avl_tree_node, fn_avl_tree_parse *pfn_avl_tree_parse );

/** !
 * Traverse an avl tree using the pre order technique
 * 
 * @param p_avl_tree_node pointer to avl tree node
 * @param pfn_traverse       called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_preorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse );

/** !
 * Traverse an avl tree using the in order technique
 * 
 * @param p_avl_tree_node pointer to avl tree node
 * @param pfn_traverse       called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_inorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse );

/** !
 * Traverse an avl tree using the post order technique
 * 
 * @param p_avl_tree_node pointer to avl tree node
 * @param pfn_traverse       called for each node in the avl tree
 * 
 * @return 1 on success, 0 on error
*/
int avl_tree_traverse_postorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse );

/** !
 * Deallocate an avl tree node
 * 
 * @param pp_avl_tree_node pointer to avl tree node pointer
 * 
 * @return 1 on success, 0 on error
 */
int avl_tree_node_destroy ( avl_tree_node **const pp_avl_tree_node );

// Function definitions
int avl_tree_create ( avl_tree **pp_avl_tree )
{

    // Argument check
    if ( pp_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Initialized data
    avl_tree *p_avl_tree = TREE_REALLOC(0, sizeof(avl_tree));

    // Error checking
    if ( p_avl_tree == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_avl_tree, 0, sizeof(avl_tree));

    // Return a pointer to the caller
    *pp_avl_tree = p_avl_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library
        {
            no_mem:
                #ifndef NDEBUG
                    printf("[Standard Library] Call to function \"realloc\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_node_create ( avl_tree_node **pp_avl_tree_node )
{

    // Argument check
    if ( pp_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;

    // Initialized data
    avl_tree_node *p_avl_tree_node = TREE_REALLOC(0, sizeof(avl_tree_node));

    // Error checking
    if ( p_avl_tree_node == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_avl_tree_node, 0, sizeof(avl_tree_node));

    // Initial height
    p_avl_tree_node->height = 1;

    // Return a pointer to the caller
    *pp_avl_tree_node = p_avl_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library
        {
            no_mem:
                #ifndef NDEBUG
                    printf("[Standard Library] Call to function \"realloc\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_node_allocate ( avl_tree *p_avl_tree, avl_tree_node **pp_avl_tree_node )
{

    // Argument check
    if ( p_avl_tree       == (void *) 0 ) goto no_avl_tree;
    if ( pp_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;
    
    // Initialized data
    avl_tree_node *p_avl_tree_node = (void *) 0;

    // Allocate a node
    if ( avl_tree_node_create(&p_avl_tree_node) == 0 ) goto failed_to_allocate_node;

    // Store the node pointer
    p_avl_tree_node->node_pointer = p_avl_tree->metadata.node_quantity;

    // Increment the node quantity
    p_avl_tree->metadata.node_quantity++;

    // Return a pointer to the caller
    *pp_avl_tree_node = p_avl_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
            no_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree
        {
            failed_to_allocate_node:
                #ifndef NDEBUG
                    printf("[tree] Call to function \"avl_tree_node_create\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Unlock
                mutex_unlock(&p_avl_tree->_lock);
                
                // Error
                return 0;
        }
    }
}



int avl_tree_construct ( avl_tree **const pp_avl_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size )
{

    // Argument check
    if ( pp_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Initialized data
    avl_tree *p_avl_tree = TREE_REALLOC(0, sizeof(avl_tree));

    // Error checking
    if ( p_avl_tree == (void *) 0 ) goto failed_to_allocate_avl_tree;

    // Populate the avl tree structure
    *p_avl_tree = (avl_tree)
    {
        .p_root    = (void *) 0,
        .functions =
        {
            .pfn_is_equal = (pfn_is_equal) ? pfn_is_equal : tree_compare,
            .pfn_key_accessor = (pfn_key_accessor) ? pfn_key_accessor : tree_key_accessor
        },
        .metadata =
        {
            .node_quantity = 0,
            .node_size     = node_size + ( 2 * sizeof(unsigned long long) )
        }
    };

    // Construct a lock
    mutex_create(&p_avl_tree->_lock);

    // Return a pointer to the caller
    *pp_avl_tree = p_avl_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to allocate avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

avl_tree_node *avl_tree_construct_balanced_recursive ( avl_tree *p_avl_tree, void **pp_values, size_t start, size_t end )
{

    // NOTE: This function has undefined behavior if p_avl_tree, pp_keys, 
    //       and/or pp_values is null. Check your parameters before you call.

    // Initialized data
    avl_tree_node *p_avl_tree_node = (void *) 0;

    // Base case
    if ( start == end )
    {

        // Allocate an avl tree node
        if (avl_tree_node_allocate(p_avl_tree, &p_avl_tree_node) == 0) goto failed_to_allocate_node;

        // Store the value
        p_avl_tree_node->p_value = pp_values[start];
        
        // Done
        return p_avl_tree_node;
    }

    // One property
    else if ( end - start == 1 )
    {

        // Allocate an avl tree node
        if (avl_tree_node_allocate(p_avl_tree, &p_avl_tree_node) == 0) goto failed_to_allocate_node;

        // Store the value
        p_avl_tree_node->p_value = pp_values[end];

        // Allocate the left node
        if (avl_tree_node_allocate(p_avl_tree, &p_avl_tree_node->p_left) == 0) goto failed_to_allocate_node;

        // Store the left value
        p_avl_tree_node->p_left->p_value = pp_values[start];
        
        // Done
        return p_avl_tree_node;
    }

    // Two properties
    else
    {

        // Initialized data
        size_t median = (start + end) / 2;

        // Allocate an avl tree node
        if (avl_tree_node_allocate(p_avl_tree, &p_avl_tree_node) == 0) goto failed_to_allocate_node;

        // Store the value
        p_avl_tree_node->p_value = pp_values[median];

        // Construct the left
        p_avl_tree_node->p_left = avl_tree_construct_balanced_recursive(p_avl_tree, pp_values, start, median - 1);

        // Construct the right
        p_avl_tree_node->p_right = avl_tree_construct_balanced_recursive(p_avl_tree, pp_values, median + 1, end);

        // Done
        return p_avl_tree_node;
    }

    // Error
    return (void *) 0;

    // Error handling
    {

        // Tree errors
        {
            failed_to_allocate_node:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to allocate avl tree node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_construct_balanced ( avl_tree **const pp_avl_tree, void **pp_values, size_t property_quantity, fn_tree_comparator *pfn_is_equal,  fn_tree_key_accessor *pfn_key_accessor, unsigned long long node_size )
{

    // Argument check
    if ( pp_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Initialized data
    avl_tree *p_avl_tree = TREE_REALLOC(0, sizeof(avl_tree));

    // Error checking
    if ( p_avl_tree == (void *) 0 ) goto failed_to_allocate_avl_tree;

    // Populate the avl tree structure
    *p_avl_tree = (avl_tree)
    {
        .p_root    = (void *) 0,
        .functions =
        {
            .pfn_is_equal = (pfn_is_equal) ? pfn_is_equal : tree_compare,
            .pfn_key_accessor = (pfn_key_accessor) ? pfn_key_accessor : tree_key_accessor
        },
        .metadata =
        {
            .node_quantity = 0,
            .node_size     = node_size + ( 2 * sizeof(unsigned long long) )
        }
    };

    // Recursively construct an avl tree, and store the root
    p_avl_tree->p_root = avl_tree_construct_balanced_recursive(p_avl_tree, pp_values, 0, property_quantity);

    // Return a pointer to the caller
    *pp_avl_tree = p_avl_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to allocate avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}



int avl_tree_search ( const avl_tree *const p_avl_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // State check
    if ( p_avl_tree->p_root == (void *) 0 ) return 0;

    // Initialized data
    avl_tree_node *p_node = p_avl_tree->p_root;
    int comparator_return = 0;

    try_again:

    // Which side? 
    comparator_return = p_avl_tree->functions.pfn_is_equal
    (
        p_avl_tree->functions.pfn_key_accessor( p_node->p_value ),
        p_key
    );

    // Search the left node
    if ( comparator_return < 0 )
    {

        // If the left node exists ...
        if ( p_node->p_left )
        {

            // ... update the state ...
            p_node = p_node->p_left;

            // ... and try again
            goto try_again;
        }

        // Unlock
        mutex_unlock(&p_avl_tree->_lock);
        
        // Error
        return 0;
    }

    // Search the right node
    else if ( comparator_return > 0 )
    {

        // If the right node exists ...
        if ( p_node->p_right )
        {

            // ... update the state ...
            p_node = p_node->p_right;

            // ... and try again
            goto try_again;
        }

        // Unlock
        mutex_unlock(&p_avl_tree->_lock);
    
        // Error
        return 0;
    }

    // Return a pointer to the caller
    *pp_value = p_node->p_value;

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_max ( int a, int b )
{
    return (a > b) ? a : b;
}

int avl_tree_node_height ( avl_tree_node *p_node )
{

    // Argument check
    if ( p_node == (void *) 0 ) return 0;

    // Success
    return p_node->height;
}

int avl_tree_node_balance ( const avl_tree_node *const p_avl_node )
{
    if ( p_avl_node == (void *) 0 ) return 0;

    return avl_tree_node_height(p_avl_node->p_left) - avl_tree_node_height(p_avl_node->p_right);
}

int avl_tree_rotate_left ( avl_tree_node *p_node, avl_tree_node **pp_result )
{

    // Initialized data
    avl_tree_node *p_node_right      = p_node->p_right,
                  *p_node_right_left = p_node_right->p_left;

    // Rotate the nodes
    p_node_right->p_left = p_node;
    p_node->p_right = p_node_right_left;

    // Update height
    p_node->height = avl_tree_max(
        avl_tree_node_height(p_node->p_left),
        avl_tree_node_height(p_node->p_right)) + 1;
    p_node_right->height = avl_tree_max(
        avl_tree_node_height(p_node_right->p_left),
        avl_tree_node_height(p_node_right->p_right)) + 1;
    
    // Return a pointer to the caller
    *pp_result = p_node_right;

    // Success
    return 1;
}

// int avl_tree_rotate_right ( avl_tree_node *p_node, avl_tree_node **pp_result )
// {
//
//     // Initialized data
//     avl_tree_node *p_node_left       = p_node->p_left,
//                   *p_node_right_left = p_node_right->p_left;
//
//     // Rotate the nodes
//     p_node_right->p_left = p_node;
//     p_node->p_right = p_node_right_left;
//
//     // Update height
//     p_node->height = max(
//         avl_tree_node_height(p_node->p_left),
//         avl_tree_node_height(p_node->p_right)) + 1;
//     p_node_right->height = max(
//         avl_tree_node_height(p_node_right->p_left),
//         avl_tree_node_height(p_node_right->p_right)) + 1;
//  
//     // Return a pointer to the caller
//     *pp_result = p_node_right;
//
//     // Success
//     return 1;
// }

int avl_tree_insert ( avl_tree *const p_avl_tree, const void *const p_value )
{

    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // Initialized data
    avl_tree_node *p_node = p_avl_tree->p_root;
    int comparator_return = 0;

    // State check
    if ( p_avl_tree->p_root == (void *) 0 ) goto no_root;

    try_again:

    // Which side? 
    comparator_return = p_avl_tree->functions.pfn_is_equal
    (
        p_avl_tree->functions.pfn_key_accessor(p_node->p_value),
        p_avl_tree->functions.pfn_key_accessor(p_value)
    );

    // Store the node on the left 
    if ( comparator_return < 0 )
    {

        // If the left node is occupied ...
        if ( p_node->p_left )
        {

            // ... update the state ...
            p_node = p_node->p_left;

            // ... and try again
            goto try_again;
        }

        // Construct an avl tree node
        if ( avl_tree_node_allocate(p_avl_tree, &p_node->p_left) == 0 ) goto failed_to_allocate_avl_tree_node;

        // Store the value
        p_node->p_left->p_value = (void *) p_value;
    }

    // Store the node on the right
    else if ( comparator_return > 0 )
    {

        // If the left node is occupied ...
        if ( p_node->p_right )
        {

            // ... update the state ...
            p_node = p_node->p_right;

            // ... and try again
            goto try_again;
        }

        // Construct an avl tree node
        if ( avl_tree_node_allocate(p_avl_tree, &p_node->p_right) == 0 ) goto failed_to_allocate_avl_tree_node;

        // Store the value
        p_node->p_right->p_value = (void *) p_value;
        
    }

    // Update parent height
    p_node->height = 1 + avl_tree_max(
        avl_tree_node_height(p_node->p_left),
        avl_tree_node_height(p_node->p_right)
    );

    // Compute balance of parent node

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // This branch runs if there is no root node
    no_root:
    {

        // Initialized data
        p_node = (void *) 0;

        // Construct an avl tree node
        if ( avl_tree_node_allocate(p_avl_tree, &p_node) == 0 ) goto failed_to_allocate_avl_tree_node;

        // Store the value
        p_node->p_value = (void *) p_value;

        // Store the node as the root of the tree
        p_avl_tree->p_root = p_node;

        // Unlock
        mutex_unlock(&p_avl_tree->_lock);
        
        // Success
        return 1;
    }

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to allocate avl tree node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Unlock
                mutex_unlock(&p_avl_tree->_lock);
                
                // Error
                return 0;
        }
    }
}

int avl_tree_remove ( avl_tree *const p_avl_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // State check
    if ( p_avl_tree->p_root == (void *) 0 ) return 0;

    // Initialized data
    avl_tree_node *p_node  = p_avl_tree->p_root;
    void *p_value = 0;
    int comparator_return = 0;

    try_again:

    // Which side? 
    comparator_return = p_avl_tree->functions.pfn_is_equal(
        p_avl_tree->functions.pfn_key_accessor( p_node->p_value ),
        p_key
    );

    // Check the node on the left 
    if ( comparator_return < 0 )
    {

        // If the left node is occupied ...
        if ( p_node->p_left )
        {
            
            // If the left node is the target, remove it ...
            if ( p_avl_tree->functions.pfn_is_equal(p_avl_tree->functions.pfn_key_accessor(p_node->p_left->p_value), p_key) == 0 ) goto remove_left;

            // ... otherwise, update the state ...
            p_node = p_node->p_left;

            // ... and try again
            goto try_again;
        }

        // Error
        return 0;
    }

    // Check the node on the right
    else if ( comparator_return > 0 )
    {

        // If the left node is occupied ...
        if ( p_node->p_right )
        {

            // If the left node is the target, remove it ...
            if ( p_avl_tree->functions.pfn_is_equal(p_avl_tree->functions.pfn_key_accessor(p_node->p_right->p_value), p_key) == 0 ) goto remove_right;

            // ... otherwise, update the state ...
            p_node = p_node->p_right;

            // ... and try again
            goto try_again;
        }

        // Error
        return 0;
    }

    done:

    // Return a pointer to the caller
    *pp_value = p_value;

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Remove left
    remove_left:
    {

        // Initialized data
        avl_tree_node *p_left = p_node->p_left;

        // Store the return value
        p_value = p_left->p_value;

        // Leaf
        if ( ( p_left->p_left || p_left->p_right ) == 0 )
        {

            // Free the node
            avl_tree_node_destroy(&p_node->p_left);
        }

        // Left
        else if ( p_left->p_left && ( p_left->p_right == 0 ) )
        {
            
            // Update the new left node
            p_left = p_left->p_left;

            // Free the node
            avl_tree_node_destroy(&p_node->p_left);

            // Repair the tree
            p_node->p_left = p_left;
        }

        // Right
        else if ( ( p_left->p_left == 0 ) && p_left->p_right )
        {
            
            // Update the new left node
            p_left = p_left->p_right;

            // Free the node
            avl_tree_node_destroy(&p_node->p_left);

            // Repair the tree
            p_node->p_left = p_left;
        }

        // TODO: Left AND right
        else
        {
            // Find the successor
            // Swap the successor
            // Done
        }
        
        // Done
        goto done;
    }

    // Remove right
    remove_right:
    {

        // Initialized data
        avl_tree_node *p_right = p_node->p_right;
        
        // Store the return value
        p_value = p_right->p_value;

        // Leaf
        if ( ( p_right->p_left || p_right->p_right ) == 0 )
        {

            // Free the node
            avl_tree_node_destroy(&p_node->p_right);
        }


        // Left
        else if ( p_right->p_left && ( p_right->p_right == 0 ) )
        {
            
            // Update the new left node
            p_right = p_right->p_left;

            // Free the node
            avl_tree_node_destroy(&p_node->p_right);

            // Repair the tree
            p_node->p_right = p_right;
        }

        // Right
        else if ( ( p_right->p_left == 0 ) && p_right->p_right )
        {
            
            // Update the new left node
            p_right = p_right->p_right;

            // Free the node
            avl_tree_node_destroy(&p_node->p_right);

            // Repair the tree
            p_node->p_right = p_right;
        }

        // TODO: Left AND right
        else
        {
            // Find the successor
            // Swap the successor
            // Done
        }

        // Done
        goto done;
    }

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}



int avl_tree_traverse_preorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;
    if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

    // Root
    pfn_traverse(p_avl_tree_node->p_value);

    // Left
    if ( p_avl_tree_node->p_left ) avl_tree_traverse_preorder_node(p_avl_tree_node->p_left, pfn_traverse);

    // Right
    if ( p_avl_tree_node->p_right ) avl_tree_traverse_preorder_node(p_avl_tree_node->p_right, pfn_traverse);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree_node:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_traverse_inorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;
    if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

    // Left
    if ( p_avl_tree_node->p_left ) avl_tree_traverse_inorder_node(p_avl_tree_node->p_left, pfn_traverse);

    // Root
    pfn_traverse(p_avl_tree_node->p_value);

    // Right
    if ( p_avl_tree_node->p_right ) avl_tree_traverse_inorder_node(p_avl_tree_node->p_right, pfn_traverse);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree_node:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_traverse_postorder_node ( avl_tree_node *p_avl_tree_node, fn_avl_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;
    if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

    // Left
    if ( p_avl_tree_node->p_left ) avl_tree_traverse_postorder_node(p_avl_tree_node->p_left, pfn_traverse);

    // Right
    if ( p_avl_tree_node->p_right ) avl_tree_traverse_postorder_node(p_avl_tree_node->p_right, pfn_traverse);

    // Root
    pfn_traverse(p_avl_tree_node->p_value);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree_node:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_traverse_preorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // Traverse the tree
    if ( avl_tree_traverse_preorder_node(p_avl_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_avl_tree;    

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_traverse_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Failed to traverse avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Unlock
                mutex_unlock(&p_avl_tree->_lock);
                
                // Error
                return 0;
        }
    }
}

int avl_tree_traverse_inorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // Traverse the tree
    if ( avl_tree_traverse_inorder_node(p_avl_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_avl_tree;    

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_traverse_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Failed to traverse avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Unlock
                mutex_unlock(&p_avl_tree->_lock);
                
                // Error
                return 0;
        }
    }
}

int avl_tree_traverse_postorder ( avl_tree *const p_avl_tree, fn_avl_tree_traverse *pfn_traverse )
{


    // Argument check
    if ( p_avl_tree == (void *) 0 ) goto no_avl_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // Traverse the tree
    if ( avl_tree_traverse_postorder_node(p_avl_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_avl_tree;    

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] avl Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_traverse_avl_tree:
                #ifndef NDEBUG
                    log_error("[tree] avl Failed to traverse avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Unlock
                mutex_unlock(&p_avl_tree->_lock);
                
                // Error
                return 0;
        }
    }
}



int avl_tree_parse ( avl_tree **const pp_avl_tree, const char *p_file, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_tree_key_accessor, fn_avl_tree_parse *pfn_parse_node )
{
    
    // Argument check
    if ( pp_avl_tree == (void *) 0 ) goto no_avl_tree;
    if ( p_file         == (void *) 0 ) goto no_file;
    if ( pfn_parse_node == (void *) 0 ) goto no_parser;

    // Initialized data
    avl_tree *p_avl_tree = 0;
    unsigned long long node_quantity = 0,
                       node_size     = 0;
    FILE *p_f = fopen(p_file, "rw");

    // Read the metadata
    {

        // Set the cursor to the start of the file
        fseek(p_f, 0, SEEK_SET);

        // Read the quantity of nodes
        fread(&node_quantity, sizeof(unsigned long long), 1, p_f);

        // Read the size of a node
        fread(&node_size, sizeof(unsigned long long), 1, p_f);
    }

    // Allocate an avl tree
    if ( avl_tree_construct(&p_avl_tree, pfn_is_equal, pfn_tree_key_accessor, node_size - ( 2 * sizeof(unsigned long long) )) == 0 ) goto failed_to_construct_avl_tree;

    // Read the root node
    if ( avl_tree_parse_node(p_f, p_avl_tree, &p_avl_tree->p_root, pfn_parse_node) == 0 ) goto failed_to_construct_avl_tree;

    // Error check
    if ( p_avl_tree->metadata.node_quantity != node_quantity ) goto failed_to_parse_avl_tree; 

    // Return a pointer to the caller
    *pp_avl_tree = p_avl_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {            
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_file:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_file\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_parser:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pfn_parse_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_construct_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to construct avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_to_parse_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to parse avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_parse_node ( FILE *p_file, avl_tree *p_avl_tree, avl_tree_node **pp_avl_tree_node, fn_avl_tree_parse *pfn_avl_tree_parse )
{

    // Argument check
    if ( p_file                == (void *) 0 ) goto no_file;
    if ( p_avl_tree         == (void *) 0 ) goto no_avl_tree;
    if ( pp_avl_tree_node   == (void *) 0 ) goto no_avl_tree_node;
    if ( pfn_avl_tree_parse == (void *) 0 ) goto no_avl_tree_parser; 

    // Initialized data
    avl_tree_node *p_avl_tree_node = TREE_REALLOC(0, sizeof(avl_tree_node));
    unsigned long long left_pointer, right_pointer;
    int height;
    
    memset(p_avl_tree_node, 0, sizeof(avl_tree_node));

    p_avl_tree_node->node_pointer = ( ftell(p_file) ) / (p_avl_tree->metadata.node_size);

    // User provided parsing function
    pfn_avl_tree_parse(p_file, p_avl_tree_node);
    
    // Store the height
    fread(&height, sizeof(int), 1, p_file);

    // Store the left pointer
    fread(&left_pointer, 8, 1, p_file);

    // Store the right pointer
    fread(&right_pointer, 8, 1, p_file);
    
    // State check
    if ( left_pointer == 0 ) goto parse_right;

    // Set the pointer correctly
    fseek(p_file, (long) ( sizeof(p_avl_tree->metadata) + (left_pointer * ( p_avl_tree->metadata.node_size ))), SEEK_SET);

    // Parse the left node
    if ( avl_tree_parse_node(p_file, p_avl_tree, &p_avl_tree_node->p_left, pfn_avl_tree_parse) == 0 ) goto failed_to_parse_node;

    parse_right:

    // State check
    if ( right_pointer == 0 ) goto done;

    // Set the pointer correctly
    fseek(p_file, (long) ( sizeof(p_avl_tree->metadata) + (right_pointer * ( p_avl_tree->metadata.node_size))), SEEK_SET);

    // Parse the right node
    if ( avl_tree_parse_node(p_file, p_avl_tree, &p_avl_tree_node->p_right, pfn_avl_tree_parse) == 0 ) goto failed_to_parse_node;

    done:

    // Return a pointer to the caller
    *pp_avl_tree_node = p_avl_tree_node;

    // Increment the node quantity
    p_avl_tree->metadata.node_quantity++;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_file:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_file\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_avl_tree_parser:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pfn_avl_tree_parse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_parse_node:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to parse node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_serialize_node ( FILE *p_file, avl_tree *p_avl_tree, avl_tree_node *p_avl_tree_node, fn_avl_tree_serialize *pfn_avl_tree_serialize )
{

    // Argument check
    if ( p_file                 == (void *) 0 ) goto no_file;
    if ( p_avl_tree             == (void *) 0 ) goto no_avl_tree;
    if ( p_avl_tree_node        == (void *) 0 ) goto no_avl_tree_node;
    if ( pfn_avl_tree_serialize == (void *) 0 ) goto no_avl_tree_serializer; 

    // Initialized data
    long offset = (long) ( sizeof(p_avl_tree->metadata) + (p_avl_tree_node->node_pointer * p_avl_tree->metadata.node_size) );

    // Set the pointer correctly
    fseek(p_file, offset, SEEK_SET);

    // Serialize the node
    pfn_avl_tree_serialize(p_file, p_avl_tree_node);

    // Write the balance factor to the output
    fwrite(&p_avl_tree_node->height, sizeof(int), 1, p_file);

    // Write the left pointer to the output
    fwrite((p_avl_tree_node->p_left) ? &p_avl_tree_node->p_left->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the right pointer to the output
    fwrite((p_avl_tree_node->p_right) ? &p_avl_tree_node->p_right->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the left node to the output
    if ( p_avl_tree_node->p_left ) avl_tree_serialize_node(p_file, p_avl_tree, p_avl_tree_node->p_left, pfn_avl_tree_serialize);

    // Write the right node to the output
    if ( p_avl_tree_node->p_right ) avl_tree_serialize_node(p_file, p_avl_tree, p_avl_tree_node->p_right, pfn_avl_tree_serialize);

    // Success
    return 1;
    
    // Error handling
    {

        // Argument errors
        {
            no_file:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_file\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_avl_tree_serializer:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pfn_avl_tree_serialize\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int avl_tree_serialize ( avl_tree *const p_avl_tree, const char *p_path, fn_avl_tree_serialize *pfn_serialize_node )
{

    // Argument check
    if ( p_avl_tree      == (void *) 0 ) goto no_avl_tree;
    if ( p_path             == (void *) 0 ) goto no_file;
    if ( pfn_serialize_node == (void *) 0 ) goto no_serializer;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // Open the file
    p_avl_tree->p_random_access = fopen(p_path, "wb+");

    // Error check
    if ( p_avl_tree->p_random_access == NULL ) goto failed_to_open_file;

    // Write the metadata
    {

        // Set the cursor to the start of the file
        fseek(p_avl_tree->p_random_access, 0, SEEK_SET);

        // Write the quantity of nodes
        fwrite(&p_avl_tree->metadata.node_quantity, sizeof(unsigned long long), 1, p_avl_tree->p_random_access);

        // Write the size of a node
        fwrite(&p_avl_tree->metadata.node_size, sizeof(unsigned long long), 1, p_avl_tree->p_random_access);
    }

    // Write the root node
    if ( avl_tree_serialize_node(p_avl_tree->p_random_access, p_avl_tree, p_avl_tree->p_root, pfn_serialize_node) == 0 ) goto failed_to_serialize_node;

    // Flush the file
    fflush(p_avl_tree->p_random_access);

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_file:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"p_file\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_serializer:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pfn_serialize_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    
        // tree errors
        {
            failed_to_serialize_node:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to serialize node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errrors
        {
            failed_to_open_file:
                #ifndef NDEBUG
                    printf("[Standard Library] Failed to open file\n");
                #endif

                // Error
                return 0;
        }
    }
}



int avl_tree_node_destroy ( avl_tree_node **const pp_avl_tree_node )
{

    // Argument check
    if ( pp_avl_tree_node == (void *) 0 ) goto no_avl_tree_node;

    // Initialized data
    avl_tree_node *p_avl_tree_node = *pp_avl_tree_node;

    // Fast exit
    if ( p_avl_tree_node == (void *) 0 ) return 1;

    // Recursively free the left node
    if ( avl_tree_node_destroy(&p_avl_tree_node->p_left) == 0 ) goto failed_to_free;

    // Recursively free the right node
    if ( avl_tree_node_destroy(&p_avl_tree_node->p_right) == 0 ) goto failed_to_free;

    // Free the node
    p_avl_tree_node = TREE_REALLOC(p_avl_tree_node, 0);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree_node:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_free:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to free avl tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0; 
        }
    }
}

int avl_tree_destroy ( avl_tree **const pp_avl_tree )
{

    // Argument check
    if ( pp_avl_tree == (void *) 0 ) goto no_avl_tree;

    // Initialized data
    avl_tree *p_avl_tree = *pp_avl_tree;

    // Fast exit
    if ( p_avl_tree == (void *) 0 ) return 1;

    // Lock
    mutex_lock(&p_avl_tree->_lock);

    // No more pointer for caller
    *pp_avl_tree = (void *) 0;

    // Unlock
    mutex_unlock(&p_avl_tree->_lock);

    // Recursively free nodes
    if ( avl_tree_node_destroy(&p_avl_tree->p_root) == 0 ) goto failed_to_free_nodes;

    // Close the file
    if ( p_avl_tree->p_random_access ) fclose(p_avl_tree->p_random_access);

    // Destroy the lock
    mutex_destroy(&p_avl_tree->_lock);

    // Release the tree
    p_avl_tree = TREE_REALLOC(p_avl_tree, 0);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_avl_tree:
                #ifndef NDEBUG
                    printf("[tree] avl Null pointer provided for parameter \"pp_avl_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree error
        {
            failed_to_free_nodes:
                #ifndef NDEBUG
                    printf("[tree] avl Failed to free avl tree nodes in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
