/** !
 * Implementation of B tree
 * 
 * @file b.c
 * 
 * @author Jacob Smith
 */

#include <tree/b.h>

// Function declarations
/** !
 * Get the root node of a B tree
 * 
 * @param p_b_tree     the B tree
 * @param pp_root_node return
 * 
 * @return 1 on success, 0 on error
 */
int b_tree_root ( const b_tree *const p_b_tree, b_tree_node **pp_root_node )
{

    // Argument check
    if ( p_b_tree     == (void *) 0 ) goto no_b_tree;
    if ( pp_root_node == (void *) 0 ) goto no_return;
    
    // Error check
    if ( p_b_tree->p_root == (void *) 0 ) goto no_root_node;

    // Return a pointer to the caller
    *pp_root_node = p_b_tree->p_root;
    
    // Success
    return 1;

    // TODO
    no_b_tree:
    no_return:
    no_root_node:

        // Error
        return 0;

    // Error handling
    {

    }
}

/** !
 * Split the root node of a B tree
 * 
 * @param p_b_tree the B tree
 * 
 * @return 1 on success, 0 on error
 */
int b_tree_split_root ( b_tree *const p_b_tree )
{

    // Argument check
    if ( p_b_tree == (void *) 0 ) goto no_b_tree;

    // Initialized data
    b_tree_node *p_new_root_node = (void *) 0;

    // Allocate a node
    //p_new_root_node = b_tree_node_allocate();

    // TODO: Populate the new root node

    // Update the root node
    p_b_tree->p_root = p_new_root_node;

    // Split the new root node
    //b_tree_split_child(p_b_tree->p_root, 0);

    // Update the height
    p_b_tree->_metadata.height++;

    // Success
    return 1;

    // TODO:
    no_b_tree:

        // Error
        return 0;
}

int b_tree_insert_not_full ( b_tree *const p_b_tree, const void *const p_key, const void *const p_value )
{

    // Argument check
    if ( p_b_tree == (void *) 0 ) goto no_b_tree;
    if ( p_key    == (void *) 0 ) goto no_key;
    if ( p_value  == (void *) 0 ) goto no_value;

    // Initialized data

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_b_tree:
                #ifndef NDEBUG
                    // TODO
                #endif

                // Error
                return 0;

            no_key:
                #ifndef NDEBUG
                    // TODO
                #endif

                // Error
                return 0;
                
            no_value:
                #ifndef NDEBUG
                    // TODO
                #endif

                // Error
                return 0;
        }
    }
}

/** !
 * Read a B tree's metadata 
 * 
 * @param b_tree the B tree
 * 
 * @return 1 on success, 0 on error
 */
int b_tree_write_meta_data ( const b_tree *const p_b_tree )
{

    // Argument check
    if ( p_b_tree == (void *) 0 ) goto no_b_tree;

    // Error check
    if ( p_b_tree->p_random_access == NULL ) goto no_random_access;

    // Seek start 
    fseek(p_b_tree->p_random_access, 0, SEEK_SET);

    // Write the quantity of keys
    //fwrite(p_b_tree->_metadata.key_quantity, sizeof(unsigned long long), 1, p_b_tree->p_random_access);

    // Write the address of the root node
    //fwrite(p_b_tree->_metadata.root_address, sizeof(unsigned long long), 1, p_b_tree->p_random_access);

    // Write the degree of the B tree
    //fwrite(p_b_tree->_metadata.degree, sizeof(int), 1, p_b_tree->p_random_access);

    // Write the quantity of nodes in the B tree
    //fwrite(p_b_tree->_metadata.node_quantity, sizeof(int), 1, p_b_tree->p_random_access);

    // Write the height of the B tree
    //fwrite(p_b_tree->_metadata.height, sizeof(int), 1, p_b_tree->p_random_access);

    // Success
    return 1;

    // TODO
    no_b_tree:
    no_random_access:

        // Error
        return 0;

    // Error handling
}

/** !
 * Read a B tree's metadata 
 * 
 * @param b_tree the B tree
 * 
 * @return 1 on success, 0 on error
 */
int b_tree_read_meta_data ( b_tree *const p_b_tree )
{

    // Argument check
    if ( p_b_tree == (void *) 0 ) goto no_b_tree;

    // Error check
    if ( p_b_tree->p_random_access == NULL ) goto no_random_access;

    // Seek start 
    fseek(p_b_tree->p_random_access, 0, SEEK_SET);

    // Read the quantity of keys
    fread(&p_b_tree->_metadata.key_quantity, sizeof(unsigned long long), 1, p_b_tree->p_random_access);

    // Read the address of the root node
    fread(&p_b_tree->_metadata.root_address, sizeof(unsigned long long), 1, p_b_tree->p_random_access);

    // Read the degree of the B tree
    fread(&p_b_tree->_metadata.degree, sizeof(int), 1, p_b_tree->p_random_access);

    // Read the quantity of nodes in the B tree
    fread(&p_b_tree->_metadata.node_quantity, sizeof(int), 1, p_b_tree->p_random_access);

    // Read the height of the B tree
    fread(&p_b_tree->_metadata.height, sizeof(int), 1, p_b_tree->p_random_access);

    // Success
    return 1;

    // TODO
    no_b_tree:
    no_random_access:

        // Error
        return 0;

    // Error handling
}

/** !
 * Read a chunk of data from the random access file
 * 
 * @param p_b_tree       pointer to B tree
 * @param disk_address   pointer to data on disk
 * @param pp_b_tree_node return
 * 
 * @return 1 on success, 0 on error
*/
int b_tree_disk_read ( b_tree *p_b_tree, unsigned long long disk_address, b_tree_node **pp_b_tree_node )
{
    
    
    // Success
    return 0;
}

/** !
 * Return the size of a file IF buffer == 0 ELSE read a file into buffer
 * 
 * @param path path to the file
 * @param buffer buffer
 * @param binary_mode "wb" IF true ELSE "w"
 * 
 * @return 1 on success, 0 on error
 */
size_t load_file ( const char *path, void *buffer, bool binary_mode )
{

    // Argument checking 
    if ( path == 0 ) goto no_path;

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, (binary_mode) ? "rb" : "r");
    
    // Check if file is valid
    if ( f == NULL ) goto invalid_file;

    // Find file size and prep for read
    fseek(f, 0, SEEK_END);
    ret = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Read to data
    if ( buffer ) ret = fread(buffer, 1, ret, f);

    // The file is no longer needed
    fclose(f);
    
    // Success
    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_path:
                #ifndef NDEBUG
                    log_error("Null pointer provided for parameter \"path\" in call to function \"%s\n", __FUNCTION__);
                #endif

            // Error
            return 0;
        }

        // File errors
        {
            invalid_file:
                #ifndef NDEBUG
                    log_error("[Standard library] Failed to load file \"%s\". %s\n",path, strerror(errno));
                #endif

            // Error
            return 0;
        }
    }
}


// Function definitions
int b_tree_create ( b_tree **const pp_b_tree )
{
    
    // Argument check
    if ( pp_b_tree == (void *) 0 ) goto no_b_tree;

    // Initialized data
    b_tree *p_b_tree = TREE_REALLOC(0, sizeof(b_tree));

    // Error check
    if ( p_b_tree == (void *) 0 ) goto no_mem;

    // Zero set the struct
    memset(p_b_tree, 0, sizeof(b_tree));

    // Return a pointer to the caller
    *pp_b_tree = p_b_tree;

    // Success
    return 1;

    // TODO:
    no_b_tree:
    no_mem:
        
        // Error
        return 0;

    // Error handling
    {

    }
}

int b_tree_construct ( b_tree **const pp_b_tree, const char *const path, tree_equal_fn *pfn_is_equal, int degree, unsigned long long node_size )
{

    // Argument check
    if ( pp_b_tree == (void *) 0 ) goto no_b_tree;
    if ( degree    <           2 ) goto no_degree;
    if ( pp_b_tree == (void *) 0 ) goto no_node_size;

    // Initialized data
    b_tree *p_b_tree = (void *) 0;
    bool  file_exists = load_file(path, 0, true);
    FILE *p_random_access_file = (void *) 0;

    // File does not exist
    if ( file_exists == false )
        
        // Create the file
        p_random_access_file = fopen(path, "w+");

    // File exists
    else 

        // Load the file
        p_random_access_file = fopen(path, "rw");

    // Error check
    if ( p_random_access_file == (void *) 0 ) goto failed_to_get_random_access_file;

    // Read the metadata from the file
    if ( file_exists )
    {

        // Read the metadata
        b_tree_read_meta_data(p_b_tree);

        // Load the root of the B tree
        b_tree_disk_read(p_b_tree, p_b_tree->_metadata.root_address, &p_b_tree->p_root);
    }

    // Populate B tree metadata. Write root
    else
    {

        p_b_tree->p_random_access = p_random_access_file;
        p_b_tree->functions.pfn_is_equal;
        p_b_tree->functions.pfn_serialize_node;
        p_b_tree->functions.pfn_parse_node;

        p_b_tree->_metadata = (b_tree_metadata) 
        {
            .node_quantity = 1,
            .node_size = node_size,
            .key_quantity = 0,
            .degree = degree,
            .height = 0,
        };
        p_b_tree->p_root;
    }

    // 1 -> open it and read the meta data
    // 0 -> create the new file, and write initial metadata
    // 
    // Initial metadata: key_count = 0, degree = degree, num_nodes = 1, height = 0

    // Construct a cache to map pointers to nodes
    
    // Success
    return 1;

    // TODO
    no_b_tree:
    no_degree:
    no_node_size:
    failed_to_get_random_access_file:

        // Error
        return 0;

    // Error handling
    {

    }
}

int b_tree_flush ( b_tree *const p_b_tree )
{

    // Argument check
    // 

    // Initialized data
    //

    // Disk write the root node
    //

    // Update metadata root address to root node location
    //

    // Write the metadata
    //
    
    // Success
    return 1;
}

int b_tree_search ( const b_tree *const p_b_tree, const void *const p_key, const void **const pp_value )
{
    
    // Success
    return 0;
}

int b_tree_insert ( b_tree *const p_b_tree, const void *const p_key, const void *const p_value )
{

    // Argument check
    if ( p_b_tree == (void *) 0 ) goto no_b_tree;
    if ( p_key    == (void *) 0 ) goto no_key;
    if ( p_value  == (void *) 0 ) goto no_value;
    
    // Is the root full?
    if ( p_b_tree->p_root->key_quantity == ( ( 2 * p_b_tree->_metadata.degree ) - 1 ) )
    {

        // Edge case
        if ( p_b_tree->p_root->leaf )
            
            // Increment the quantity of nodes
            p_b_tree->_metadata.node_quantity++;
        
        // Split the root before inserting 
        b_tree_split_root(p_b_tree);
    }

    // Insert the key
    //b_tree_insert_not_full(p_b_tree->p_root, p_key, p_value);

    // Success
    return 1;

    // TODO: 
    no_b_tree:
    no_key:
    no_value:

        // Error
        return 0;
}

int b_tree_remove ( b_tree *const p_b_tree, const void *const p_key, const void **const p_value )
{
    
    // Success
    return 0;
}

int b_tree_parse ( b_tree **const pp_b_tree, FILE *p_file, tree_equal_fn *pfn_is_equal, b_tree_parse_fn *pfn_parse_node )
{
    
    // Success
    return 0;
}

int b_tree_serialize ( b_tree *const p_b_tree, const char *p_path, b_tree_serialize_fn *pfn_serialize_node )
{
    
    // Success
    return 0;
}

int b_tree_destroy ( b_tree **const pp_b_tree )
{

    // Argument check
    if ( pp_b_tree == (void *) 0 ) goto no_b_tree;

    // Initialized data
    b_tree *p_b_tree = *pp_b_tree;

    // Lock
    //

    // No more pointer for caller
    *pp_b_tree = (void *) 0;

    // Unlock
    //
    
    // TODO: Deallocate

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_b_tree:
                #ifndef NDEBUG
                    log_error("[tree] [b] Null pointer provided for parameter \"pp_b_tree\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
