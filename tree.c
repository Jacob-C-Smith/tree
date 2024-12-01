/** !
 * Implementation of functions in main tree header
 * 
 * @file tree.c
 * 
 * @author Jacob Smith
 */
// Header file
#include <tree/tree.h>

// tree module
#include <tree/avl.h>
#include <tree/b.h>
#include <tree/binary.h>
#include <tree/red_black.h>

// Static data
static const unsigned long long eight_bytes_of_zero = 0;

fn_tree_construct *_tree_constructors[TREE_QUANTITY] =
{
    [TREE_AVL]       = avl_tree_construct,
    [TREE_B]         = b_tree_construct,
    [TREE_BINARY]    = binary_tree_construct,
    [TREE_RED_BLACK] = red_black_tree_construct
};

fn_tree_construct *_tree_balanced_constructors[TREE_QUANTITY] =
{
    [TREE_AVL]       = avl_tree_construct_balanced,
    [TREE_B]         = b_tree_construct,
    [TREE_BINARY]    = binary_tree_construct_balanced,
    [TREE_RED_BLACK] = red_black_tree_construct_balanced
};

fn_tree_parse *_tree_parsers[TREE_QUANTITY] =
{
    [TREE_AVL]       = avl_tree_parse,
    [TREE_B]         = b_tree_parse,
    [TREE_BINARY]    = binary_tree_parse,
    [TREE_RED_BLACK] = red_black_tree_parse
};

tree _tree_prototypes[TREE_QUANTITY] =
{
    [TREE_AVL] = (tree)
    {
        .pfn_tree_comparator         = tree_compare,
        .pfn_tree_key_accessor       = tree_key_accessor,

        .pfn_tree_serialize          = avl_tree_serialize,

        .pfn_tree_value_parser        = (void *) 0,
        .pfn_tree_value_serializer    = (void *) 0,
 
        .pfn_tree_search             = avl_tree_search,
        .pfn_tree_insert             = avl_tree_insert,
        .pfn_tree_remove             = avl_tree_remove,

        .pfn_tree_traverse_preorder  = avl_tree_traverse_preorder,
        .pfn_tree_traverse_postorder = avl_tree_traverse_postorder,
        .pfn_tree_traverse_inorder   = avl_tree_traverse_inorder,

        .p_concrete_tree             = (void *) 0
    },
    [TREE_B] = (tree)
    {
        .pfn_tree_comparator         = tree_compare,
        .pfn_tree_key_accessor       = tree_key_accessor,

        .pfn_tree_serialize          = b_tree_serialize,

        .pfn_tree_value_parser       = (void *) 0,
        .pfn_tree_value_serializer   = (void *) 0,

        .pfn_tree_search             = b_tree_search,
        .pfn_tree_insert             = b_tree_insert,
        .pfn_tree_remove             = b_tree_remove,

        .pfn_tree_traverse_preorder  = (void *) 0,
        .pfn_tree_traverse_postorder = (void *) 0,
        .pfn_tree_traverse_inorder   = b_tree_traverse_inorder,

        .p_concrete_tree             = (void *) 0
    },
    [TREE_BINARY] = (tree)
    {
        .pfn_tree_comparator         = tree_compare,
        .pfn_tree_key_accessor       = tree_key_accessor,

        .pfn_tree_serialize          = binary_tree_serialize,

        .pfn_tree_value_parser       = (void *) 0,
        .pfn_tree_value_serializer   = (void *) 0,

        .pfn_tree_search             = binary_tree_search,
        .pfn_tree_insert             = binary_tree_insert,
        .pfn_tree_remove             = binary_tree_remove,

        .pfn_tree_traverse_preorder  = binary_tree_traverse_preorder,
        .pfn_tree_traverse_postorder = binary_tree_traverse_postorder,
        .pfn_tree_traverse_inorder   = binary_tree_traverse_inorder,

        .p_concrete_tree             = (void *) 0
    },
    [TREE_RED_BLACK] = (tree)
    {
        .pfn_tree_comparator         = tree_compare,
        .pfn_tree_key_accessor       = tree_key_accessor,

        .pfn_tree_serialize          = red_black_tree_serialize,

        .pfn_tree_value_parser       = tree_parser,
        .pfn_tree_value_serializer   = tree_serializer,

        .pfn_tree_search             = red_black_tree_search,
        .pfn_tree_insert             = red_black_tree_insert,
        .pfn_tree_remove             = red_black_tree_remove,

        .pfn_tree_traverse_preorder  = red_black_tree_traverse_preorder,
        .pfn_tree_traverse_postorder = red_black_tree_traverse_postorder,
        .pfn_tree_traverse_inorder   = red_black_tree_traverse_inorder,

        .p_concrete_tree             = (void *) 0
    }
};
int tree_init ( void )
{

    // Success
    return 1;
}

int tree_construct ( tree **pp_tree, enum tree_type_e _type, tree_create_identity *p_head )
{

    // Argument check
    if ( pp_tree == (void *) 0 ) goto no_tree;
    
    // Initialized data
    tree *p_tree = TREE_REALLOC(0, sizeof(tree));

    // Error check
    if ( p_tree == (void *) 0 ) goto no_mem;

    // Clone a prototype
    if ( _type > 0 ) goto prototype_tree;

    prototype_done:
    
    // Factory 
    while ( p_head )
    {

        // Strategybinary_tree_serialize
        switch (p_head->_type)
        {
            case TREE_CREATE_IDENTITY:  goto factory_identity;
            case TREE_CREATE_ACCESSORS: goto factory_accessors;
            case TREE_CREATE_SERIALIZE: goto factory_serialize;
            case TREE_CREATE_TRAVERSAL: goto factory_traversal;
            case TREE_CREATE_VALUES:    goto factory_values;
            
            // Error
            default: break;
        }

        factory_step_complete:
    }

    // Return a pointer to the caller
    *pp_tree = p_tree;

    // Success
    return 1;

    // TODO:
    failed_to_construct_prototype:
    no_mem:
        ;
        return 0;

    // Clone a prototype
    prototype_tree:
    
        switch (_type)
        {

            case TREE_AVL:
            case TREE_B:
            case TREE_BINARY:
            case TREE_RED_BLACK:

                // Clone the prototype
                memcpy(p_tree, &_tree_prototypes[_type], sizeof(tree));

                // Construct a tree 
                if ( _tree_constructors[_type](&p_tree->p_concrete_tree, p_head->pfn_comparator, p_head->pfn_key_accessor, p_head->value_size) == 0 ) goto failed_to_construct_prototype;

                // Done
                break;

            // Default
            default: goto unknown_tree_prototype;
        }

        // Done
        goto prototype_done;

    factory_identity:
    {
        
        // Initialized data
        tree_create_identity *p_identity = p_head;

        // Update the head
        p_head = p_identity->p_next;

        // Install the tree comparator
        p_tree->pfn_tree_comparator = p_identity->pfn_comparator;

        // Install the key accessor
        p_tree->pfn_tree_key_accessor = p_identity->pfn_key_accessor;

        // TODO: Set the value size
        //

        // Done
        goto factory_step_complete;
    }
    
    factory_accessors:
    {
        
        // Initialized data
        tree_create_accessors *p_accessors = p_head;

        // Update the head
        p_head = p_accessors->p_next;
        
        // Install the insert accessor
        p_tree->pfn_tree_insert = p_accessors->pfn_insert;
        
        // Install the search accessor
        p_tree->pfn_tree_search = p_accessors->pfn_search;

        // Install the remove accessor
        p_tree->pfn_tree_remove = p_accessors->pfn_remove;
        
        // Done
        goto factory_step_complete;
    }

    factory_serialize:
    {
        
        // Initialized data
        tree_create_serializer *p_serializer = p_head;

        // Update the head
        p_head = p_serializer->p_next;

        // Install the parser
        p_tree->pfn_tree_value_parser = p_serializer->pfn_value_parse;
        
        // Install the serializer
        p_tree->pfn_tree_value_serializer = p_serializer->pfn_value_serialize;
        
        // Done
        goto factory_step_complete;
    }

    factory_traversal:
    {
        
        // Initialized data
        tree_create_traversal *p_traversal = p_head;

        // Update the head
        p_head = p_traversal->p_next;

        // Install the preorder traversal
        p_tree->pfn_tree_traverse_preorder = p_traversal->traverse.pfn_preorder;
        
        // Install the postorder traversal
        p_tree->pfn_tree_traverse_postorder = p_traversal->traverse.pfn_postorder;

        // Install the inorder traversal
        p_tree->pfn_tree_traverse_inorder = p_traversal->traverse.pfn_inorder;

        // Done
        goto factory_step_complete;
    }

    factory_values:
    {
        
        // Initialized data
        tree_create_values *p_values = p_head;

        

        // Done
        goto factory_step_complete;
    }

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"pp_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            unknown_tree_prototype:
                #ifndef NDEBUG
                    log_error("[tree] TODO: Error\n");
                #endif

                // Error
                return 0;
        }
    }
}

int tree_compare ( const void *const a, const void *const b )
{
    
    // Return
    return ( a == b ) ? 0 : ( a < b ) ? 1 : -1;
}

const void *tree_key_accessor ( const void *p_value )
{

    // Success
    return p_value;
}

int tree_serializer ( FILE *p_file, void *p_key, void *p_value )
{

    // Write the value to the output
    fwrite(&p_value, sizeof(void *), 1, p_file);
    
    // Success
    return 1;
}

int tree_parser ( FILE *p_file, void **pp_value )
{

    // Initialized data
    void *p_value = malloc(sizeof(void *));

    // Read the pointer from the file
    fread(&p_value, 8, 1, p_file);

    // Return a pointer to the caller
    *pp_value = p_value;
    
    // Success
    return 1;
}

int tree_serialize ( tree *const p_tree, const char *p_path )
{

    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_serialize(p_tree->p_concrete_tree, p_path);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_insert ( tree *p_tree, void *p_value )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_insert(p_tree->p_concrete_tree, p_value);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_search ( tree *p_tree, void *p_key, void **pp_valaue )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_search(p_tree->p_concrete_tree, p_key, pp_valaue);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_remove ( tree *p_tree, void *p_key, void **pp_valaue )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_remove(p_tree->p_concrete_tree, p_key, pp_valaue);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_traverse_inorder ( tree *p_tree, fn_tree_traverse *pfn_traverse )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_traverse_inorder(p_tree->p_concrete_tree, pfn_traverse);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_traverse_preorder  ( tree *p_tree, fn_tree_traverse *pfn_traverse )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_traverse_preorder(p_tree->p_concrete_tree, pfn_traverse);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int tree_traverse_postorder ( tree *p_tree, fn_tree_traverse *pfn_traverse )
{
    
    // Argument check
    if ( p_tree == (void *) 0 ) goto no_tree;

    // Success
    return p_tree->pfn_tree_traverse_postorder(p_tree->p_concrete_tree, pfn_traverse);

    // Error handling
    {

        // Argument check
        {
            no_tree:
                #ifndef NDEBUG
                    log_error("[tree] Null pointer provided for parameter \"p_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

