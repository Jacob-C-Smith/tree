/** !
 * Implementation of binary search tree
 * 
 * @file binary.c
 * 
 * @author Jacob Smith
 */

#include <tree/binary.h>

int binary_tree_create ( binary_tree **pp_binary_tree )
{

    // Argument check
    if ( pp_binary_tree == (void *) 0 ) goto no_binary_tree;

    // Initialized data
    binary_tree *p_binary_tree = TREE_REALLOC(0, sizeof(binary_tree));

    // Error checking
    if ( p_binary_tree == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_binary_tree, 0, sizeof(binary_tree));

    // Return a pointer to the caller
    *pp_binary_tree = p_binary_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"pp_binary_tree\" in call to function \"%s\"\n", __FUNCTION__);
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

int binary_tree_node_create ( binary_tree_node **pp_binary_tree_node )
{

    // Argument check
    if ( pp_binary_tree_node == (void *) 0 ) goto no_binary_tree_node;

    // Initialized data
    binary_tree_node *p_binary_tree_node = TREE_REALLOC(0, sizeof(binary_tree_node));

    // Error checking
    if ( p_binary_tree_node == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_binary_tree_node, 0, sizeof(binary_tree_node));

    // Return a pointer to the caller
    *pp_binary_tree_node = p_binary_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"pp_binary_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
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

int binary_tree_construct ( binary_tree **const pp_binary_tree, tree_equal_fn *pfn_is_equal )
{

    // Argument check
    if ( pp_binary_tree == (void *) 0 ) goto no_binary_tree;

    // Initialized data
    binary_tree *p_binary_tree = TREE_REALLOC(0, sizeof(binary_tree));

    // Error checking
    if ( p_binary_tree == (void *) 0 ) goto failed_to_allocate_binary_tree;

    // Populate the binary tree structure
    *p_binary_tree = (binary_tree)
    {
        .p_root       = (void *) 0,
        .pfn_is_equal = (pfn_is_equal) ? pfn_is_equal : tree_compare_function
    };

    // Return a pointer to the caller
    *pp_binary_tree = p_binary_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"pp_binary_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Failed to allocate binary tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int binary_tree_search ( const binary_tree *const p_binary_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_binary_tree == (void *) 0 ) goto no_binary_tree;

    // State check
    if ( p_binary_tree->p_root == (void *) 0 ) return 0;

    // Initialized data
    binary_tree_node *p_node = p_binary_tree->p_root;
    int comparator_return = 0;

    try_again:

    // Which side? 
    comparator_return = p_binary_tree->pfn_is_equal(p_node->p_key, p_key);

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

        // Error
        return 0;
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

        // Error
        return 0;
    }

    // Return a pointer to the caller
    *pp_value = p_node->p_value;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"p_binary_tree\" in call to function \"%s\"\n", __FUNCTION__)
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_binary_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [binary] Failed to allocate binary tree node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int binary_tree_insert ( binary_tree *const p_binary_tree, const void *const p_key, const void *const p_value )
{

    // Argument check
    if ( p_binary_tree == (void *) 0 ) goto no_binary_tree;

    // State check
    if ( p_binary_tree->p_root == (void *) 0 ) goto no_root;

    // Initialized data
    binary_tree_node *p_node = p_binary_tree->p_root;
    int comparator_return = 0;

    try_again:

    // Which side? 
    comparator_return = p_binary_tree->pfn_is_equal(p_node->p_key, p_key);

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

        // Construct a binary tree node
        if ( binary_tree_node_create(&p_node->p_left) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_left->p_key   = p_key;
        p_node->p_left->p_value = p_value;
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

        // Construct a binary tree node
        if ( binary_tree_node_create(&p_node->p_right) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_right->p_key   = p_key;
        p_node->p_right->p_value = p_value;
        
    }

    // Success
    return 1;

    // This branch runs if there is no root node
    no_root:
    {

        // Initialized data
        binary_tree_node *p_node = (void *) 0;

        // Construct a binary tree node
        if ( binary_tree_node_create(&p_node) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_key   = p_key;
        p_node->p_value = p_value;

        // Store the node as the root of the tree
        p_binary_tree->p_root = p_node;

        // Success
        return 1;
    }

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"p_binary_tree\" in call to function \"%s\"\n", __FUNCTION__)
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_binary_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [binary] Failed to allocate binary tree node in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

