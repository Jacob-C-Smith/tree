/** !
 * Implementation of functions in main tree header
 * 
 * @file tree.c
 * 
 * @author Jacob Smith
 */

#include <tree/tree.h>

int tree_init ( void )
{

    // Success
    return 1;
}

int tree_compare_function ( const void *const a, const void *const b )
{
    
    // Return
    return ( a == b ) ? 0 : ( a < b ) ? 1 : -1;
}

const void *tree_key_is_value ( const void *p_value )
{

    // Success
    return p_value;
}