/** !
 * Implementation of binary search tree
 * 
 * @file binary.c
 * 
 * @author Jacob Smith
 */

#include <tree/binary.h>

static const unsigned long long eight_bytes_of_zero = 0;

// Forward declarations
int binary_tree_node_destroy ( binary_tree_node **const pp_binary_tree_node );

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

int binary_tree_node_allocate ( binary_tree *p_binary_tree, binary_tree_node **pp_binary_tree_node )
{

    // Argument check
    if ( p_binary_tree       == (void *) 0 ) goto no_binary_tree;
    if ( pp_binary_tree_node == (void *) 0 ) goto no_binary_tree_node;

    // Initialized data
    binary_tree_node *p_binary_tree_node = (void *) 0;

    // Allocate a node
    if ( binary_tree_node_create(&p_binary_tree_node) == 0 ) goto failed_to_allocate_node;

    // Store the node pointer
    p_binary_tree_node->node_pointer = p_binary_tree->metadata.node_quantity;

    // Increment the node quantity
    p_binary_tree->metadata.node_quantity++;

    // Return a pointer to the caller
    *pp_binary_tree_node = p_binary_tree_node;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_binary_tree:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"p_binary_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
            no_binary_tree_node:
                #ifndef NDEBUG
                    printf("[tree] [binary] Null pointer provided for parameter \"pp_binary_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree
        {
            failed_to_allocate_node:
                #ifndef NDEBUG
                    printf("[tree] Call to function \"binary_tree_node_create\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int binary_tree_construct ( binary_tree **const pp_binary_tree, tree_equal_fn *pfn_is_equal, unsigned long long node_size )
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
    comparator_return = p_binary_tree->functions.pfn_is_equal(p_node->p_key, p_key);

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
    }
}

int binary_tree_insert ( binary_tree *const p_binary_tree, const void *const p_key, const void *const p_value )
{

    // Argument check
    if ( p_binary_tree == (void *) 0 ) goto no_binary_tree;

    // Initialized data
    binary_tree_node *p_node = p_binary_tree->p_root;
    int comparator_return = 0;

    // State check
    if ( p_binary_tree->p_root == (void *) 0 ) goto no_root;

    try_again:

    // Which side? 
    comparator_return = p_binary_tree->functions.pfn_is_equal(p_node->p_key, p_key);

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
        if ( binary_tree_node_allocate(p_binary_tree, &p_node->p_left) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_left->p_key   = (void *) p_key;
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

        // Construct a binary tree node
        if ( binary_tree_node_allocate(p_binary_tree, &p_node->p_right) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_right->p_key   = (void *) p_key;
        p_node->p_right->p_value = (void *) p_value;
        
    }

    // Success
    return 1;

    // This branch runs if there is no root node
    no_root:
    {

        // Initialized data
        p_node = (void *) 0;

        // Construct a binary tree node
        if ( binary_tree_node_allocate(p_binary_tree, &p_node) == 0 ) goto failed_to_allocate_binary_tree_node;

        // Store the supplied value in the node
        p_node->p_key   = (void *) p_key;
        p_node->p_value = (void *) p_value;

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

int binary_tree_remove ( binary_tree *const p_binary_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_binary_tree == (void *) 0 ) goto no_binary_tree;

    // State check
    if ( p_binary_tree->p_root == (void *) 0 ) return 0;

    // Initialized data
    binary_tree_node *p_node  = p_binary_tree->p_root;
    void *p_value = 0;
    int comparator_return = 0;

    try_again:

    // Which side? 
    comparator_return = p_binary_tree->functions.pfn_is_equal(p_node->p_key, p_key);

    // Check the node on the left 
    if ( comparator_return < 0 )
    {

        // If the left node is occupied ...
        if ( p_node->p_left )
        {
            
            // If the left node is the target, remove it ...
            if ( p_binary_tree->functions.pfn_is_equal(p_node->p_left->p_key, p_key) == 0 ) goto remove_left;

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
            if ( p_binary_tree->functions.pfn_is_equal(p_node->p_right->p_key, p_key) == 0 ) goto remove_right;

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

    // Success
    return 1;

    // Remove left
    remove_left:
    {

        // Initialized data
        binary_tree_node *p_left = p_node->p_left;

        // Store the return value
        p_value = p_left->p_value;

        // Leaf
        if ( ( p_left->p_left || p_left->p_right ) == 0 )
        {

            // Free the node
            binary_tree_node_destroy(&p_node->p_left);
        }

        // Left
        else if ( p_left->p_left && ( p_left->p_right == 0 ) )
        {
            
            // Update the new left node
            p_left = p_left->p_left;

            // Free the node
            binary_tree_node_destroy(&p_node->p_left);

            // Repair the tree
            p_node->p_left = p_left;
        }

        // Right
        else if ( ( p_left->p_left == 0 ) && p_left->p_right )
        {
            
            // Update the new left node
            p_left = p_left->p_right;

            // Free the node
            binary_tree_node_destroy(&p_node->p_left);

            // Repair the tree
            p_node->p_left = p_left;
        }

        // TODO: Left AND right
        
        // Done
        goto done;
    }

    // Remove right
    remove_right:
    {

        // Initialized data
        binary_tree_node *p_right = p_node->p_right;
        
        // Store the return value
        p_value = p_right->p_value;

        // Leaf
        if ( ( p_right->p_left || p_right->p_right ) == 0 )
        {

            // Free the node
            binary_tree_node_destroy(&p_node->p_right);
        }


        // Left
        else if ( p_right->p_left && ( p_right->p_right == 0 ) )
        {
            
            // Update the new left node
            p_right = p_right->p_left;

            // Free the node
            binary_tree_node_destroy(&p_node->p_right);

            // Repair the tree
            p_node->p_right = p_right;
        }

        // Right
        else if ( ( p_right->p_left == 0 ) && p_right->p_right )
        {
            
            // Update the new left node
            p_right = p_right->p_right;

            // Free the node
            binary_tree_node_destroy(&p_node->p_right);

            // Repair the tree
            p_node->p_right = p_right;
        }

        // TODO: Left AND right

        // Done
        goto done;
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
    }
}

int binary_tree_parse_function ( FILE *p_file, binary_tree *p_binary_tree, binary_tree_node **pp_binary_tree_node, unsigned long long node_pointer )
{

    // Argument check
    if ( p_file              == (void *) 0 ) goto no_file;
    if ( p_binary_tree       == (void *) 0 ) goto no_binary_tree;
    if ( pp_binary_tree_node == (void *) 0 ) goto no_binary_tree_node;

    // Initialized data
    long offset = (long) ( sizeof(p_binary_tree->metadata) + (node_pointer * p_binary_tree->metadata.node_size) );
    binary_tree_node *p_binary_tree_node = (void *) 0;

    // Allocate a binary tree node
    if ( binary_tree_node_create(&p_binary_tree_node) == 0 ) goto failed_to_allocate_node;
    
    // Set the pointer correctly
    fseek(p_file, offset, SEEK_SET);

    // TODO: This should be the serializer function that the user ends up writing
    {

        // Write the key to the output
        fread(&p_binary_tree_node->p_key, sizeof(void *), 1, p_file);

        // Write the value to the output
        fread(&p_binary_tree_node->p_value, sizeof(void *), 1, p_file);
    }

    *pp_binary_tree_node = p_binary_tree_node;

    // Write the left pointer to the output
    //fwrite((p_binary_tree_node->p_left) ? &p_binary_tree_node->p_left->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the right pointer to the output
    //fwrite((p_binary_tree_node->p_right) ? &p_binary_tree_node->p_right->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the left node to the output
    //if ( p_binary_tree_node->p_left ) binary_tree_serialize_function(p_file, p_binary_tree, p_binary_tree_node->p_left);

    // Write the right node to the output
    //if ( p_binary_tree_node->p_right ) binary_tree_serialize_function(p_file, p_binary_tree, p_binary_tree_node->p_right);

    // Success
    return 1;
    
    // TODO:
    no_file:
    no_binary_tree:
    failed_to_allocate_node:
    no_binary_tree_node:

        // Error
        return 0;
}

int binary_tree_parse ( binary_tree **const pp_binary_tree, FILE *p_file, tree_equal_fn *pfn_is_equal, binary_tree_parse_fn *pfn_parse_node )
{
    
    // Argument check
    if ( pp_binary_tree == (void *) 0 ) goto no_binary_tree;
    if ( p_file         == (void *) 0 ) goto no_file;
    if ( pfn_parse_node == (void *) 0 ) goto no_parser;

    // Initialized data
    binary_tree *p_binary_tree = 0;
    unsigned long long node_quantity = 0,
                       node_size     = 0;

    // Allocate a binary tree
    if ( binary_tree_construct(&p_binary_tree, pfn_is_equal, node_size) == 0 ) goto failed_to_construct_binary_tree;

    // Read the metadata
    {

        // Set the cursor to the start of the file
        fseek(p_file, 0, SEEK_SET);

        // Write the quantity of nodes
        fread(&node_quantity, sizeof(unsigned long long), 1, p_file);

        // Write the size of a node
        fread(&node_size, sizeof(unsigned long long), 1, p_file);
    }

    // Write the root node
    if ( pfn_parse_node(p_file, p_binary_tree, &p_binary_tree->p_root, 0) == 0 ) return 0;

    *pp_binary_tree = p_binary_tree;

    // Success
    return 1;

    // TODO
    no_binary_tree:
    failed_to_construct_binary_tree:
    no_file:
    no_parser:

        // Error
        return 0;
}

int binary_tree_serialize_node ( FILE *p_file, binary_tree *p_binary_tree, binary_tree_node *p_binary_tree_node, binary_tree_serialize_fn *pfn_binary_tree_serialize )
{

    // Argument check
    if ( p_file             == (void *) 0 ) goto no_file;
    if ( p_binary_tree      == (void *) 0 ) goto no_binary_tree;
    if ( p_binary_tree_node == (void *) 0 ) goto no_binary_tree_node;

    // Initialized data
    long offset = (long) ( sizeof(p_binary_tree->metadata) + (p_binary_tree_node->node_pointer * p_binary_tree->metadata.node_size) );

    // Set the pointer correctly
    fseek(p_file, offset, SEEK_SET);

    // Serialize the node
    pfn_binary_tree_serialize(p_file, p_binary_tree_node);

    // Write the left pointer to the output
    fwrite((p_binary_tree_node->p_left) ? &p_binary_tree_node->p_left->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the right pointer to the output
    fwrite((p_binary_tree_node->p_right) ? &p_binary_tree_node->p_right->node_pointer : &eight_bytes_of_zero, sizeof(void *), 1, p_file);

    // Write the left node to the output
    if ( p_binary_tree_node->p_left ) binary_tree_serialize_node(p_file, p_binary_tree, p_binary_tree_node->p_left, pfn_binary_tree_serialize);

    // Write the right node to the output
    if ( p_binary_tree_node->p_right ) binary_tree_serialize_node(p_file, p_binary_tree, p_binary_tree_node->p_right, pfn_binary_tree_serialize);

    // Success
    return 1;
    
    // TODO:
    no_file:
    no_binary_tree:
    no_binary_tree_node:

        // Error
        return 0;
}

int binary_tree_serialize ( binary_tree *const p_binary_tree, FILE *p_file, binary_tree_serialize_fn *pfn_serialize_node )
{

    // Argument check
    if ( p_binary_tree      == (void *) 0 ) goto no_binary_tree;
    if ( p_file             == (void *) 0 ) goto no_file;
    if ( pfn_serialize_node == (void *) 0 ) goto no_serializer;

    // Write the metadata
    {

        // Set the cursor to the start of the file
        fseek(p_file, 0, SEEK_SET);

        // Write the quantity of nodes
        fwrite(&p_binary_tree->metadata.node_quantity, sizeof(unsigned long long), 1, p_file);

        // Write the size of a node
        fwrite(&p_binary_tree->metadata.node_size, sizeof(unsigned long long), 1, p_file);
    }

    // Write the root node
    if ( binary_tree_serialize_node(p_file, p_binary_tree, p_binary_tree->p_root, pfn_serialize_node) == 0 ) return 0;

    // Success
    return 1;

    // TODO
    no_binary_tree:
    no_file:
    no_serializer:

        // Error
        return 0;
}

int binary_tree_node_destroy ( binary_tree_node **const pp_binary_tree_node )
{

    // Argument check
    if ( pp_binary_tree_node == (void *) 0 ) goto no_binary_tree_node;

    // Initialized data
    binary_tree_node *p_binary_tree_node = *pp_binary_tree_node;

    // Fast exit
    if ( p_binary_tree_node == (void *) 0 ) return 1;

    // Free the node
    (void) TREE_REALLOC(p_binary_tree_node, 0);

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
    }
}

int binary_tree_destroy ( binary_tree **const pp_binary_tree )
{

    // Argument check
    if ( pp_binary_tree == (void *) 0 ) goto no_binary_tree;

    // Write an error message to standard out 
    printf("[tree] [binary] This function has not yet been implemented!\n");

    // Error
    return 0;

    // TODO:
    no_binary_tree:
        return 0;
}
