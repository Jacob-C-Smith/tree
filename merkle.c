// /** !
//  * Implementation of merkle tree
//  * 
//  * @file merkle.c
//  * 
//  * @author Jacob Smith
//  */

// // Header file
// #include <tree/merkle.h>

// // Static data
// static const unsigned long long eight_bytes_of_zero = 0;

// // Forward declarations
// /** !
//  * Allocate memory for a merkle tree
//  * 
//  * @param pp_merkle_tree return
//  * 
//  * @return 1 on success, 0 on error
//  */
// int merkle_tree_create ( merkle_tree **const pp_merkle_tree );

// /** !
//  * Allocate memory for a merkle tree node
//  * 
//  * @param pp_merkle_tree_node return
//  * 
//  * @return 1 on success, 0 on error
//  */
// int merkle_tree_node_create ( merkle_tree_node **pp_merkle_tree_node );

// /** !
//  * Allocate a node for a specific merkle tree, and set the node pointer. 
//  * 
//  * The node pointer is an integer ordinal that is atomically incremented 
//  * each time the allocator is called. 
//  * 
//  * @param p_merkle_tree       the merkle tree to allocate a node to
//  * @param pp_merkle_tree_node return
//  * 
//  * @return 1 on success, 0 on error
//  */
// int merkle_tree_node_allocate ( merkle_tree *p_merkle_tree, merkle_tree_node **pp_merkle_tree_node );

// /** !
//  * Traverse a merkle tree using the pre order technique
//  * 
//  * @param p_merkle_tree_node pointer to merkle tree node
//  * @param pfn_traverse       called for each node in the merkle tree
//  * 
//  * @return 1 on success, 0 on error
// */
// int merkle_tree_traverse_preorder_node ( merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse );

// /** !
//  * Traverse a merkle tree using the in order technique
//  * 
//  * @param p_merkle_tree_node pointer to merkle tree node
//  * @param pfn_traverse       called for each node in the merkle tree
//  * 
//  * @return 1 on success, 0 on error
// */
// int merkle_tree_traverse_inorder_node ( merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse );

// /** !
//  * Traverse a merkle tree using the post order technique
//  * 
//  * @param p_merkle_tree      the merkle tree
//  * @param p_merkle_tree_node pointer to merkle tree node
//  * @param pfn_traverse       called for each node in the merkle tree
//  * 
//  * @return 1 on success, 0 on error
// */
// int merkle_tree_traverse_postorder_node ( merkle_tree *p_merkle_tree, merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse );

// /** !
//  * Deallocate a merkle tree node
//  * 
//  * @param pp_merkle_tree_node pointer to merkle tree node pointer
//  * 
//  * @return 1 on success, 0 on error
//  */
// int merkle_tree_node_destroy ( merkle_tree_node **const pp_merkle_tree_node );

// // Function definitions
// int merkle_tree_create ( merkle_tree **pp_merkle_tree )
// {

//     // Argument check
//     if ( pp_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Initialized data
//     merkle_tree *p_merkle_tree = TREE_REALLOC(0, sizeof(merkle_tree));

//     // Error checking
//     if ( p_merkle_tree == (void *) 0 ) goto no_mem;

//     // Zero set the memory
//     memset(p_merkle_tree, 0, sizeof(merkle_tree));

//     // Return a pointer to the caller
//     *pp_merkle_tree = p_merkle_tree;

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Standard library
//         {
//             no_mem:
//                 #ifndef NDEBUG
//                     printf("[Standard Library] Call to function \"realloc\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_node_create ( merkle_tree_node **pp_merkle_tree_node )
// {

//     // Argument check
//     if ( pp_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;

//     // Initialized data
//     merkle_tree_node *p_merkle_tree_node = TREE_REALLOC(0, sizeof(merkle_tree_node));

//     // Error checking
//     if ( p_merkle_tree_node == (void *) 0 ) goto no_mem;

//     // Zero set the memory
//     memset(p_merkle_tree_node, 0, sizeof(merkle_tree_node));

//     // Return a pointer to the caller
//     *pp_merkle_tree_node = p_merkle_tree_node;

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Standard library
//         {
//             no_mem:
//                 #ifndef NDEBUG
//                     printf("[Standard Library] Call to function \"realloc\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_node_allocate ( merkle_tree *p_merkle_tree, merkle_tree_node **pp_merkle_tree_node )
// {

//     // Argument check
//     if ( p_merkle_tree       == (void *) 0 ) goto no_merkle_tree;
//     if ( pp_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;
    
//     // Initialized data
//     merkle_tree_node *p_merkle_tree_node = (void *) 0;

//     // Allocate a node
//     if ( merkle_tree_node_create(&p_merkle_tree_node) == 0 ) goto failed_to_allocate_node;

//     // Store the node pointer
//     p_merkle_tree_node->node_pointer = p_merkle_tree->metadata.node_quantity;

//     // Increment the node quantity
//     p_merkle_tree->metadata.node_quantity++;

//     // Return a pointer to the caller
//     *pp_merkle_tree_node = p_merkle_tree_node;

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
                
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree
//         {
//             failed_to_allocate_node:
//                 #ifndef NDEBUG
//                     printf("[tree] Call to function \"merkle_tree_node_create\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Unlock
//                 mutex_unlock(&p_merkle_tree->_lock);
                
//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_construct ( merkle_tree **const pp_merkle_tree, fn_tree_comparator *pfn_is_equal, fn_tree_key_accessor *pfn_key_accessor, fn_hash64 *pfn_hash_function, unsigned long long node_size )
// {

//     // Argument check
//     if ( pp_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Initialized data
//     merkle_tree *p_merkle_tree = TREE_REALLOC(0, sizeof(merkle_tree));

//     // Error checking
//     if ( p_merkle_tree == (void *) 0 ) goto failed_to_allocate_merkle_tree;

//     // Populate the merkle tree structure
//     *p_merkle_tree = (merkle_tree)
//     {
//         .p_root    = (void *) 0,
//         .functions =
//         {
//             .pfn_is_equal = (pfn_is_equal) ? pfn_is_equal : tree_compare,
//             .pfn_key_accessor = (pfn_key_accessor) ? pfn_key_accessor : tree_key_accessor,
//             .pfn_hash_function = (pfn_hash_function) ? pfn_hash_function : hash_crc64
//         },
//         .metadata =
//         {
//             .node_quantity = 0,
//             .node_size     = node_size + ( 2 * sizeof(unsigned long long) + sizeof(hash64) )
//         }
//     };

//     // Construct a lock
//     mutex_create(&p_merkle_tree->_lock);

//     // Return a pointer to the caller
//     *pp_merkle_tree = p_merkle_tree;

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_allocate_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Failed to allocate merkle tree in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_search ( const merkle_tree *const p_merkle_tree, const void *const p_key, const void **const pp_value )
// {

//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // State check
//     if ( p_merkle_tree->p_root == (void *) 0 ) return 0;

//     // Initialized data
//     merkle_tree_node *p_node = p_merkle_tree->p_root;
//     int comparator_return = 0;

//     try_again:

//     // Which side? 
//     comparator_return = p_merkle_tree->functions.pfn_is_equal
//     (
//         p_merkle_tree->functions.pfn_key_accessor( p_node->p_value ),
//         p_key
//     );

//     // Search the left node
//     if ( comparator_return < 0 )
//     {

//         // If the left node exists ...
//         if ( p_node->p_left )
//         {

//             // ... update the state ...
//             p_node = p_node->p_left;

//             // ... and try again
//             goto try_again;
//         }

//         // Unlock
//         mutex_unlock(&p_merkle_tree->_lock);
        
//         // Error
//         return 0;
//     }

//     // Search the right node
//     else if ( comparator_return > 0 )
//     {

//         // If the right node exists ...
//         if ( p_node->p_right )
//         {

//             // ... update the state ...
//             p_node = p_node->p_right;

//             // ... and try again
//             goto try_again;
//         }

//         // Unlock
//         mutex_unlock(&p_merkle_tree->_lock);
    
//         // Error
//         return 0;
//     }

//     // Return a pointer to the caller
//     *pp_value = p_node->p_value;

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_insert ( merkle_tree *const p_merkle_tree, const void *const p_value )
// {

//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // Initialized data
//     merkle_tree_node *p_node = p_merkle_tree->p_root;

//     // State check
//     if ( p_merkle_tree->p_root == (void *) 0 ) goto no_root;

//     try_again:

//     // // Which side? 
//     // comparator_return = p_merkle_tree->functions.pfn_is_equal
//     // (
//     //     p_merkle_tree->functions.pfn_key_accessor(p_node->p_value),
//     //     p_merkle_tree->functions.pfn_key_accessor(p_value)
//     // );

//     // If the right node is occupied ...
//     if ( p_node->p_right && p_node->p_left == 0 )
//     {
//         merkle_tree_node *p_new_right = (void *) 0;

//         p_node->p_left = p_node->p_right;
        
//         if ( merkle_tree_node_allocate(p_merkle_tree, &p_new_right) == 0 ) goto failed_to_allocate_merkle_tree_node;

//         p_new_right->p_value = p_value;
//         p_new_right->_hash   = p_merkle_tree->functions.pfn_hash_function(p_value, p_merkle_tree->metadata.node_size);

//         p_node->p_right = p_new_right;

//         goto done;

//     }
    
//     if ( p_node->p_left && p_node->p_right )
//     {
        
//         merkle_tree_node *p_new_left = (void *) 0;

//         // Construct a merkle tree node
//         if ( merkle_tree_node_allocate(p_merkle_tree, &p_new_left) == 0 ) goto failed_to_allocate_merkle_tree_node;
//         p_new_left->p_left  = p_node->p_left,
//         p_new_left->p_right = p_node->p_right,
//         p_node->p_left      = p_new_left;
//         p_node->p_right     = p_node;
//         goto done;

//     }

//     done: 

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // This branch runs if there is no root node
//     no_root:
//     {

//         // Initialized data
//         p_node = (void *) 0;

//         // Construct a merkle tree node
//         if ( merkle_tree_node_allocate(p_merkle_tree, &p_node) == 0 ) goto failed_to_allocate_merkle_tree_node;
        
//         p_node->leaf = true;

//         // Store the value
//         p_node->p_value = (void *) p_value;
//         p_node->_hash = p_merkle_tree->functions.pfn_hash_function(p_value, p_merkle_tree->metadata.node_size);

//         // Store the node as the root of the tree
//         p_merkle_tree->p_root = p_node;

//         // Unlock
//         mutex_unlock(&p_merkle_tree->_lock);
        
//         // Success
//         return 1;
//     }

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_allocate_merkle_tree_node:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Failed to allocate merkle tree node in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Unlock
//                 mutex_unlock(&p_merkle_tree->_lock);
                
//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_remove ( merkle_tree *const p_merkle_tree, const void *const p_key, const void **const pp_value )
// {

//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // State check
//     if ( p_merkle_tree->p_root == (void *) 0 ) return 0;

//     // Initialized data
//     merkle_tree_node *p_node  = p_merkle_tree->p_root;
//     void *p_value = 0;
//     int comparator_return = 0;

//     try_again:

//     // Which side? 
//     comparator_return = p_merkle_tree->functions.pfn_is_equal(
//         p_merkle_tree->functions.pfn_key_accessor( p_node->p_value ),
//         p_key
//     );

//     // Check the node on the left 
//     if ( comparator_return < 0 )
//     {

//         // If the left node is occupied ...
//         if ( p_node->p_left )
//         {
            
//             // If the left node is the target, remove it ...
//             if ( p_merkle_tree->functions.pfn_is_equal(p_merkle_tree->functions.pfn_key_accessor(p_node->p_left->p_value), p_key) == 0 ) goto remove_left;

//             // ... otherwise, update the state ...
//             p_node = p_node->p_left;

//             // ... and try again
//             goto try_again;
//         }

//         // Error
//         return 0;
//     }

//     // Check the node on the right
//     else if ( comparator_return > 0 )
//     {

//         // If the left node is occupied ...
//         if ( p_node->p_right )
//         {

//             // If the left node is the target, remove it ...
//             if ( p_merkle_tree->functions.pfn_is_equal(p_merkle_tree->functions.pfn_key_accessor(p_node->p_right->p_value), p_key) == 0 ) goto remove_right;

//             // ... otherwise, update the state ...
//             p_node = p_node->p_right;

//             // ... and try again
//             goto try_again;
//         }

//         // Error
//         return 0;
//     }

//     done:

//     // Return a pointer to the caller
//     *pp_value = p_value;

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // Remove left
//     remove_left:
//     {

//         // Initialized data
//         merkle_tree_node *p_left = p_node->p_left;

//         // Store the return value
//         p_value = p_left->p_value;

//         // Leaf
//         if ( ( p_left->p_left || p_left->p_right ) == 0 )
//         {

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_left);
//         }

//         // Left
//         else if ( p_left->p_left && ( p_left->p_right == 0 ) )
//         {
            
//             // Update the new left node
//             p_left = p_left->p_left;

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_left);

//             // Repair the tree
//             p_node->p_left = p_left;
//         }

//         // Right
//         else if ( ( p_left->p_left == 0 ) && p_left->p_right )
//         {
            
//             // Update the new left node
//             p_left = p_left->p_right;

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_left);

//             // Repair the tree
//             p_node->p_left = p_left;
//         }

//         // TODO: Left AND right
//         else
//         {
//             // Find the successor
//             // Swap the successor
//             // Done
//         }
        
//         // Done
//         goto done;
//     }

//     // Remove right
//     remove_right:
//     {

//         // Initialized data
//         merkle_tree_node *p_right = p_node->p_right;
        
//         // Store the return value
//         p_value = p_right->p_value;

//         // Leaf
//         if ( ( p_right->p_left || p_right->p_right ) == 0 )
//         {

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_right);
//         }


//         // Left
//         else if ( p_right->p_left && ( p_right->p_right == 0 ) )
//         {
            
//             // Update the new left node
//             p_right = p_right->p_left;

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_right);

//             // Repair the tree
//             p_node->p_right = p_right;
//         }

//         // Right
//         else if ( ( p_right->p_left == 0 ) && p_right->p_right )
//         {
            
//             // Update the new left node
//             p_right = p_right->p_right;

//             // Free the node
//             merkle_tree_node_destroy(&p_node->p_right);

//             // Repair the tree
//             p_node->p_right = p_right;
//         }

//         // TODO: Left AND right
//         else
//         {
//             // Find the successor
//             // Swap the successor
//             // Done
//         }

//         // Done
//         goto done;
//     }

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_preorder_node ( merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse )
// {

//     // Argument check
//     if ( p_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;
//     if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

//     // Root
//     pfn_traverse(p_merkle_tree_node->p_value, p_merkle_tree_node->_hash, !(p_merkle_tree_node->p_left || p_merkle_tree_node->p_right));

//     // Left
//     if ( p_merkle_tree_node->p_left ) merkle_tree_traverse_preorder_node(p_merkle_tree_node->p_left, pfn_traverse);

//     // Right
//     if ( p_merkle_tree_node->p_right ) merkle_tree_traverse_preorder_node(p_merkle_tree_node->p_right, pfn_traverse);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_inorder_node ( merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse )
// {

//     // Argument check
//     if ( p_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;
//     if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

//     // Left
//     if ( p_merkle_tree_node->p_left ) merkle_tree_traverse_inorder_node(p_merkle_tree_node->p_left, pfn_traverse);

//     // Root
//     pfn_traverse(p_merkle_tree_node->p_value, p_merkle_tree_node->_hash, !(p_merkle_tree_node->p_left || p_merkle_tree_node->p_right));

//     // Right
//     if ( p_merkle_tree_node->p_right ) merkle_tree_traverse_inorder_node(p_merkle_tree_node->p_right, pfn_traverse);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_postorder_node ( merkle_tree *p_merkle_tree, merkle_tree_node *p_merkle_tree_node, fn_merkle_tree_traverse *pfn_traverse )
// {

//     // Argument check
//     if ( p_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;
//     if ( pfn_traverse       == (void *) 0 ) goto no_traverse_function;

//     // Left
//     if ( p_merkle_tree_node->p_left ) merkle_tree_traverse_postorder_node(p_merkle_tree, p_merkle_tree_node->p_left, pfn_traverse);

//     // Right
//     if ( p_merkle_tree_node->p_right ) merkle_tree_traverse_postorder_node(p_merkle_tree, p_merkle_tree_node->p_right, pfn_traverse);

//     if ( p_merkle_tree_node->p_left && p_merkle_tree_node->p_right )
//     {

//         // Initialized data
//         hash64 _concatenated_hashes[2] =
//         {
//             p_merkle_tree_node->p_left->_hash,
//             p_merkle_tree_node->p_right->_hash
//         };

//         p_merkle_tree_node->_hash = p_merkle_tree->functions.pfn_hash_function(&_concatenated_hashes, sizeof(_concatenated_hashes));
//     }

//     // Root
//     pfn_traverse(p_merkle_tree_node->p_value, p_merkle_tree_node->_hash, !(p_merkle_tree_node->p_left || p_merkle_tree_node->p_right));

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_preorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse )
// {

//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;
//     if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // Traverse the tree
//     if ( merkle_tree_traverse_preorder_node(p_merkle_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_merkle_tree;    

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_traverse_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Failed to traverse merkle tree in call to function \"%s\"\n", __FUNCTION__);
//                 #endif
                
//                 // Unlock
//                 mutex_unlock(&p_merkle_tree->_lock);
                
//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_inorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse )
// {

//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;
//     if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // Traverse the tree
//     if ( merkle_tree_traverse_inorder_node(p_merkle_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_merkle_tree;    

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_traverse_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Failed to traverse merkle tree in call to function \"%s\"\n", __FUNCTION__);
//                 #endif
                
//                 // Unlock
//                 mutex_unlock(&p_merkle_tree->_lock);
                
//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_traverse_postorder ( merkle_tree *const p_merkle_tree, fn_merkle_tree_traverse *pfn_traverse )
// {


//     // Argument check
//     if ( p_merkle_tree == (void *) 0 ) goto no_merkle_tree;
//     if ( pfn_traverse  == (void *) 0 ) goto no_traverse_function;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // Traverse the tree
//     if ( merkle_tree_traverse_postorder_node(p_merkle_tree, p_merkle_tree->p_root, pfn_traverse) == 0 ) goto failed_to_traverse_merkle_tree;    

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"p_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;

//             no_traverse_function:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Null pointer provided for parameter \"pfn_traverse\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_traverse_merkle_tree:
//                 #ifndef NDEBUG
//                     log_error("[tree] [binary] Failed to traverse merkle tree in call to function \"%s\"\n", __FUNCTION__);
//                 #endif
                
//                 // Unlock
//                 mutex_unlock(&p_merkle_tree->_lock);
                
//                 // Error
//                 return 0;
//         }
//     }
// }

// int merkle_tree_node_destroy ( merkle_tree_node **const pp_merkle_tree_node )
// {

//     // Argument check
//     if ( pp_merkle_tree_node == (void *) 0 ) goto no_merkle_tree_node;

//     // Initialized data
//     merkle_tree_node *p_merkle_tree_node = *pp_merkle_tree_node;

//     // Fast exit
//     if ( p_merkle_tree_node == (void *) 0 ) return 1;

//     // Recursively free the left node
//     if ( merkle_tree_node_destroy(&p_merkle_tree_node->p_left) == 0 ) goto failed_to_free;

//     // Recursively free the right node
//     if ( merkle_tree_node_destroy(&p_merkle_tree_node->p_right) == 0 ) goto failed_to_free;

//     // Free the node
//     p_merkle_tree_node = TREE_REALLOC(p_merkle_tree_node, 0);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree_node:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree_node\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree errors
//         {
//             failed_to_free:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Failed to free merkle tree in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0; 
//         }
//     }
// }

// int merkle_tree_destroy ( merkle_tree **const pp_merkle_tree )
// {

//     // Argument check
//     if ( pp_merkle_tree == (void *) 0 ) goto no_merkle_tree;

//     // Initialized data
//     merkle_tree *p_merkle_tree = *pp_merkle_tree;

//     // Fast exit
//     if ( p_merkle_tree == (void *) 0 ) return 1;

//     // Lock
//     mutex_lock(&p_merkle_tree->_lock);

//     // No more pointer for caller
//     *pp_merkle_tree = (void *) 0;

//     // Unlock
//     mutex_unlock(&p_merkle_tree->_lock);

//     // Recursively free nodes
//     if ( merkle_tree_node_destroy(&p_merkle_tree->p_root) == 0 ) goto failed_to_free_nodes;

//     // Close the file
//     if ( p_merkle_tree->p_random_access ) fclose(p_merkle_tree->p_random_access);

//     // Destroy the lock
//     mutex_destroy(&p_merkle_tree->_lock);

//     // Release the tree
//     p_merkle_tree = TREE_REALLOC(p_merkle_tree, 0);

//     // Success
//     return 1;

//     // Error handling
//     {

//         // Argument errors
//         {
//             no_merkle_tree:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Null pointer provided for parameter \"pp_merkle_tree\" in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }

//         // Tree error
//         {
//             failed_to_free_nodes:
//                 #ifndef NDEBUG
//                     printf("[tree] [binary] Failed to free merkle tree nodes in call to function \"%s\"\n", __FUNCTION__);
//                 #endif

//                 // Error
//                 return 0;
//         }
//     }
// }
