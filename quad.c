/** !
 * Implementation of quad tree
 * 
 * @file quad.c
 * 
 * @author Jacob Smith
 */

#include <tree/quad.h>

int quad_tree_create ( quad_tree **const pp_quad_tree )
{

    // Argument check
    if ( pp_quad_tree == (void *) 0 ) goto no_quad_tree;

    // Initialized data
    quad_tree *p_quad_tree = TREE_REALLOC(0, sizeof(quad_tree));

    // Error checking
    if ( p_quad_tree == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_quad_tree, 0, sizeof(quad_tree));

    // Return a pointer to the caller
    *pp_quad_tree = p_quad_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_quad_tree:
                #ifndef NDEBUG
                    printf("[tree] [quad] Null pointer provided for parameter \"pp_quad_tree\" in call to function \"%s\"\n", __FUNCTION__);
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

int quad_tree_node_create ( quad_tree_node **pp_quad_tree_node )
{

    // Argument check
    if ( pp_quad_tree_node == (void *) 0 ) goto no_quad_tree_node;

    // Initialized data
    quad_tree_node *p_quad_tree_node = TREE_REALLOC(0, sizeof(quad_tree_node));

    // Error checking
    if ( p_quad_tree_node == (void *) 0 ) goto no_mem;

    // Zero set the memory
    memset(p_quad_tree_node, 0, sizeof(quad_tree_node));

    // Return a pointer to the caller
    *pp_quad_tree_node = p_quad_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_quad_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [quad] Null pointer provided for parameter \"pp_quad_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
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

int quad_tree_node_allocate ( quad_tree *p_quad_tree, quad_tree_node **pp_quad_tree_node )
{

    // Argument check
    if ( p_quad_tree       == (void *) 0 ) goto no_quad_tree;
    if ( pp_quad_tree_node == (void *) 0 ) goto no_quad_tree_node;

    // Initialized data
    quad_tree_node *p_quad_tree_node = (void *) 0;

    // Allocate a node
    if ( quad_tree_node_create(&p_quad_tree_node) == 0 ) goto failed_to_allocate_node;

    // Store the node pointer
    p_quad_tree_node->node_pointer = p_quad_tree->metadata.node_quantity;

    // Increment the node quantity
    p_quad_tree->metadata.node_quantity++;

    // Return a pointer to the caller
    *pp_quad_tree_node = p_quad_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_quad_tree:
                #ifndef NDEBUG
                    printf("[tree] [quad] Null pointer provided for parameter \"p_quad_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
            no_quad_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [quad] Null pointer provided for parameter \"pp_quad_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree
        {
            failed_to_allocate_node:
                #ifndef NDEBUG
                    printf("[tree] Call to function \"quad_tree_node_create\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int quad_tree_construct ( quad_tree **const pp_quad_tree, tree_equal_fn *pfn_is_equal, unsigned long long node_size )
{

    // Argument check
    if ( pp_quad_tree == (void *) 0 ) goto no_quad_tree;

    // Initialized data
    quad_tree *p_quad_tree = TREE_REALLOC(0, sizeof(quad_tree));

    // Error checking
    if ( p_quad_tree == (void *) 0 ) goto failed_to_allocate_quad_tree;

    // Populate the quad tree structure
    *p_quad_tree = (quad_tree)
    {
        .p_root    = (void *) 0,
        .functions =
        {
            .pfn_is_equal = (pfn_is_equal) ? pfn_is_equal : tree_compare_function
        },
        .metadata =
        {
            .node_quantity = 0,
            .node_size     = node_size + ( 2 * sizeof(unsigned long long) )
        }
    };

    // Return a pointer to the caller
    *pp_quad_tree = p_quad_tree;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_quad_tree:
                #ifndef NDEBUG
                    printf("[tree] [quad] Null pointer provided for parameter \"pp_quad_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_quad_tree:
                #ifndef NDEBUG
                    printf("[tree] [quad] Failed to allocate quad tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
} 

int quad_tree_insert ( quad_tree *const p_quad_tree, const void *const p_key, const void *const p_value )
{

    // Argument check
    if ( p_quad_tree == (void *) 0 ) goto no_quad_tree;
    if ( p_key       == (void *) 0 ) goto no_key;
    if ( p_value     == (void *) 0 ) goto no_value;

    // Initialized data
    quad_tree_node *p_node = p_quad_tree->p_root;
    int comparator_return = 0;

    // State check
    if ( p_quad_tree->p_root == (void *) 0 ) goto no_root;

    try_again:

    // Contains? 
    if ( comparator_return == p_quad_tree->functions.pfn_is_equal(p_node->p_key, p_key) )
    {

        // Top left
        if ( p_node->quadrants.p_top_left )
        {

            // Update the node
            p_node = p_node->quadrants.p_top_left;

            // Try again
            goto try_again;
        }

        // Top right
        else if ( p_node->quadrants.p_top_right )
        {

            // Update the node
            p_node = p_node->quadrants.p_top_right;

            // Try again
            goto try_again;
        }

        // Bottom left
        else if ( p_node->quadrants.p_bottom_left )
        {

            // Update the node
            p_node = p_node->quadrants.p_bottom_left;

            // Try again
            goto try_again;
        }

        // Bottom right
        else if ( p_node->quadrants.p_bottom_right )
        {

            // Update the node
            p_node = p_node->quadrants.p_bottom_right;

            // Try again
            goto try_again;
        }

    }

    // Store the node
    if ( quad_tree_node_allocate(p_quad_tree, &p_node) == 0 ) goto failed_to_allocate_quad_tree_node;
    
    // Store the key
    p_node->p_key = (void *) p_key;

    // Store the value
    p_node->p_value = (void *) p_value;

    // Success
    return 1;

    // This branch runs if there is no root node
    no_root:
    {

        // Initialized data
        p_node = (void *) 0;

        // Construct a quad tree node
        if ( quad_tree_node_allocate(p_quad_tree, &p_node) == 0 ) goto failed_to_allocate_quad_tree_node;

        // Store the key
        p_node->p_key = (void *) p_key;

        // Store the value
        p_node->p_value = (void *) p_value;

        // Store the node as the root of the tree
        p_quad_tree->p_root = p_node;

        // Success
        return 1;
    }

    // Success
    return 1;

    // TODO: Error handling
    {
        no_quad_tree:
        no_key:
        no_value:
        failed_to_allocate_quad_tree_node:
            return 0;
    }
}

int quad_tree_destroy ( quad_tree **const pp_quad_tree )
{
    return 0;
}