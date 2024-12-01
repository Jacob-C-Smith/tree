/** !
 * Implementation of search search tree
 * 
 * @file search.c
 * 
 * @author Jacob Smith
 */

// Header file


// Function definitions
int search_tree_construct ( search_tree **const pp_search_tree, enum search_tree_type_e _type, search_tree_identity *p_search_tree_identity )
{

    // Argument check
    if ( pp_search_tree         == (void *) 0 ) goto no_search_tree;

    // Initialized data
    search_tree *p_search_tree = TREE_REALLOC(0, sizeof(search_tree));
    fn_tree_comparator                     *pfn_is_equal;
    fn_tree_key_accessor              *pfn_key_accessor;
    fn_search_tree_serialize          *pfn_serialize_node;
    fn_search_tree_parse              *pfn_parse_node;
    fn_search_tree_insert             *pfn_search_tree_insert;
    fn_search_tree_search             *pfn_search_tree_search;
    fn_search_tree_remove             *pfn_search_tree_remove;
    fn_search_tree_traverse_inorder   *pfn_search_tree_traverse_inorder;
    fn_search_tree_traverse_preorder  *pfn_search_tree_traverse_preorder;
    fn_search_tree_traverse_postorder *pfn_search_tree_traverse_postorder;

    // Error checking
    if ( p_search_tree == (void *) 0 ) goto failed_to_allocate_search_tree;

    if ( p_search_tree_identity == (void *) 0 ) goto no_search_tree_identity;

    switch ( _type )
    {
        case SEARCH_TREE_AVL:
        case SEARCH_TREE_BINARY:
        case SEARCH_TREE_RED_BLACK:

            // Construct the
            if ( _search_tree_constructors[_type](&p_search_tree->p_concrete_tree, p_search_tree_identity->pfn_is_equal, p_search_tree_identity->pfn_key_accessor, p_search_tree_identity->node_size) == 0 ) goto failed_to_construct_search_tree;
            break;
    
        default:
            break;
    }


    // Clone the prototype
    //memcpy(p_search_tree, &_search_tree_prototypes[_type], sizeof(search_tree));

    done:
    // Return a pointer to the caller
    *pp_search_tree = p_search_tree;

    // Success
    return 1;

    // TODO
    failed_to_construct_search_tree:
    failed_to_construct_avl_tree:
    failed_to_construct_binary_tree:
    failed_to_construct_red_black_tree:
        return 0;
    
    no_search_tree_identity:
    {

        // Initialized data
        search_tree *p_search_tree = TREE_REALLOC(0, sizeof(search_tree));

        // Initialize function pointers
        pfn_is_equal                       = tree_compare,
        pfn_key_accessor                   = tree_key_accessor,
        pfn_serialize_node                 = 0,
        pfn_parse_node                     = 0,
        pfn_search_tree_insert             = binary_tree_insert,
        pfn_search_tree_search             = binary_tree_search,
        pfn_search_tree_remove             = binary_tree_remove,
        pfn_search_tree_traverse_inorder   = binary_tree_traverse_inorder,
        pfn_search_tree_traverse_preorder  = binary_tree_traverse_preorder,
        pfn_search_tree_traverse_postorder = binary_tree_traverse_postorder;

        // Populate the result
        *p_search_tree = (search_tree)
        {
            ._type = SEARCH_TREE_BINARY,
            .functions = 
            {
                .pfn_is_equal                       = pfn_is_equal,
                .pfn_key_accessor                   = pfn_key_accessor,
                .pfn_serialize_node                 = pfn_serialize_node,
                .pfn_parse_node                     = pfn_parse_node,
                .pfn_search_tree_insert             = pfn_search_tree_insert,
                .pfn_search_tree_search             = pfn_search_tree_search,
                .pfn_search_tree_remove             = pfn_search_tree_remove,
                .pfn_search_tree_traverse_inorder   = pfn_search_tree_traverse_inorder,
                .pfn_search_tree_traverse_preorder  = pfn_search_tree_traverse_preorder,
                .pfn_search_tree_traverse_postorder = pfn_search_tree_traverse_postorder
            }
        };

        // Done
        goto done;
    }

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Null pointer provided for parameter \"pp_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree errors
        {
            failed_to_allocate_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Failed to allocate search tree in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_search ( const search_tree *const p_search_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;

    // Done
    return p_search_tree->functions.pfn_search_tree_search(p_search_tree->tree.p_binary_tree, p_key, pp_value);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_insert ( search_tree *const p_search_tree, const void *const p_value )
{

    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;

    // Success
    return p_search_tree->functions.pfn_search_tree_insert(p_search_tree->tree.p_binary_tree, p_value);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_remove ( search_tree *const p_search_tree, const void *const p_key, const void **const pp_value )
{

    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;

    // Success
    return p_search_tree->functions.pfn_search_tree_remove(p_search_tree->tree.p_binary_tree, p_key, pp_value);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_traverse_preorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Success
    return p_search_tree->functions.pfn_search_tree_traverse_preorder(p_search_tree->tree.p_binary_tree, pfn_traverse);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_traverse_inorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse )
{

    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Done
    return p_search_tree->functions.pfn_search_tree_traverse_inorder(p_search_tree->tree.p_binary_tree, pfn_traverse);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_traverse_postorder ( search_tree *const p_search_tree, fn_search_tree_traverse *pfn_traverse )
{


    // Argument check
    if ( p_search_tree == (void *) 0 ) goto no_search_tree;
    if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

    // Done
    return p_search_tree->functions.pfn_search_tree_traverse_postorder(p_search_tree->tree.p_binary_tree, pfn_traverse);

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"p_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_traverse_function:
                #ifndef NDEBUG
                    log_error("[tree] [search] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int search_tree_destroy ( search_tree **const pp_search_tree )
{

    // Argument check
    if ( pp_search_tree == (void *) 0 ) goto no_search_tree;

    // Initialized data
    search_tree *p_search_tree = *pp_search_tree;

    // Fast exit
    if ( p_search_tree == (void *) 0 ) return 1;

    // Release the tree
    p_search_tree = TREE_REALLOC(p_search_tree, 0);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_search_tree:
                #ifndef NDEBUG
                    printf("[tree] [search] Null pointer provided for parameter \"pp_search_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Tree error
        {
            failed_to_free_nodes:
                #ifndef NDEBUG
                    printf("[tree] [search] Failed to free search tree nodes in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
