/** !
 * Example tree program
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>

// log
#include <log/log.h>

// tree
#include <tree/tree.h>
#include <tree/binary.h>
#include <tree/b.h>

// Preprocessor defines
#define BINARY_TREE_EXAMPLE_LIST_LENGTH 15
#define B_TREE_EXAMPLE_DEGREE           15
#define B_TREE_EXAMPLE_SEQUENCE_LENGTH  16

// Enumeration definitions
enum tree_examples_e
{
    TREE_EXAMPLE_AVL       = 0,
    TREE_EXAMPLE_B         = 1,
    TREE_EXAMPLE_BINARY    = 2,
    TREE_EXAMPLE_QUAD      = 3,
    TREE_EXAMPLE_R         = 4,
    TREE_EXAMPLE_RED_BLACK = 5,
    TREE_EXAMPLES_QUANTITY = 6
};

// Forward declarations
/** !
 * Print a usage message to standard out
 * 
 * @param argv0 the name of the program
 * 
 * @return void
 */
void print_usage ( const char *argv0 );

/** !
 * Parse command line arguments
 * 
 * @param argc            the argc parameter of the entry point
 * @param argv            the argv parameter of the entry point
 * @param examples_to_run return
 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run );

/** !
 * AVL tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_avl_example ( int argc, const char *argv[] );

/** !
 * B tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_b_example ( int argc, const char *argv[] );

/** !
 * Binary tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_binary_example ( int argc, const char *argv[] );

/** !
 * Quad tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_quad_example ( int argc, const char *argv[] );

/** !
 * R tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_r_example ( int argc, const char *argv[] );

/** !
 * Red black tree example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int tree_red_black_example ( int argc, const char *argv[] );

/** !
 * Convert text to two bit values. 
 * A -> 00, C -> 01, G-> 10, and T -> 11.
 * 
 * @param p_text   the text
 * @param p_result return
 * 
 * @return 1 on success, 0 on error
 */
int ascii_to_u64_encoded_2_bit_slice ( const char *const p_text, unsigned long long *p_result );

/** !
 * Example binary tree node serializer
 * 
 * @param p_file             the file to write to
 * @param p_binary_tree_node the binary tree node to write 
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node );

/** !
 * Example binary tree node parser
 * 
 * @param p_file             the file to read from
 * @param p_binary_tree_node the binary tree node to populate
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_parser ( FILE *p_file, binary_tree_node **pp_binary_tree_node );

/** !
 * Return the size of a file IF buffer == 0 ELSE read a file into buffer
 * 
 * @param path path to the file
 * @param buffer buffer
 * @param binary_mode "wb" IF true ELSE "w"
 * 
 * @return 1 on success, 0 on error
 */
size_t load_file ( const char *path, void *buffer, bool binary_mode );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    bool examples_to_run[TREE_EXAMPLES_QUANTITY] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, examples_to_run);

    // Initialize tree
    if ( tree_init() == 0 ) goto failed_to_initialize_tree;

    // Seed this for later
    srand(time(0));

    // Formatting
    printf(
        "╭──────────────╮\n"\
        "│ tree example │\n"\
        "╰──────────────╯\n"\
        "The tree library provides high level abstractions for %d different trees.\n"\
        "The AVL tree, the B tree, the binary tree, the quadtree, the R tree, and the red black tree.\n\n"\
        "An AVL tree is self balancing binary search tree; suitable for frequent searching.\n"\
        "A B tree is a self balancing, flat search tree; suitable for storage systems and large data.\n"\
        "A Binary tree is the most primitive tree.\n"\
        "A Quadtree is a tree where each node has four childern; suitable for dynamic spatial computing.\n"\
        "An R tree is a self balancing, flat search tree; suitable for large spatial data.\n"\
        "A Red Black tree is an unbalanced binary search tree. \n\n",
        TREE_EXAMPLES_QUANTITY
    );

    //////////////////////
    // Run the examples //
    //////////////////////

    // Run the AVL tree example program
    if ( examples_to_run[TREE_EXAMPLE_AVL] )

        // Error check
        if ( tree_avl_example(argc, argv) == 0 ) goto failed_to_run_avl_tree_example;

    // Run the B tree example program
    if ( examples_to_run[TREE_EXAMPLE_B] )

        // Error check
        if ( tree_b_example(argc, argv) == 0 ) goto failed_to_run_b_tree_example;
        
        
    // Run the binary tree example program
    if ( examples_to_run[TREE_EXAMPLE_BINARY] )

        // Error check
        if ( tree_binary_example(argc, argv) == 0 ) goto failed_to_run_binary_tree_example;
        

    // Run the quadtree example program
    if ( examples_to_run[TREE_EXAMPLE_QUAD] )

        // Error check
        if ( tree_quad_example(argc, argv) == 0 ) goto failed_to_run_quad_tree_example;
        

    // Run the R tree example program
    if ( examples_to_run[TREE_EXAMPLE_R] )

        // Error check
        if ( tree_r_example(argc, argv) == 0 ) goto failed_to_run_r_tree_example;
        

    // Run the red black tree example program
    if ( examples_to_run[TREE_EXAMPLE_RED_BLACK] )

        // Error check
        if ( tree_red_black_example(argc, argv) == 0 ) goto failed_to_run_red_black_tree_example;
        

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        
        failed_to_initialize_tree:

            // Write an error message to standard out
            printf("Failed to initialize tree!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_avl_tree_example:

            // Print an error message
            printf("Failed to run AVL tree example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_b_tree_example:

            // Print an error message
            printf("Failed to run B tree example!\n");

            // Error
            return EXIT_FAILURE;
        
        failed_to_run_binary_tree_example:

            // Print an error message
            printf("Failed to run binary tree example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_quad_tree_example:

            // Print an error message
            printf("Failed to run quadtree example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_r_tree_example:

            // Print an error message
            printf("Failed to run R tree example!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_red_black_tree_example:

            // Print an error message
            printf("Failed to run red black tree example!\n");

            // Error
            return EXIT_FAILURE;
    }
}

void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s [avl] [b] [binary] [quad] [r] [redblack] [--preserve-files]\n", argv0);

    // Done
    return;
}

void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) goto all_examples;

    // Error check
    if ( argc > TREE_EXAMPLES_QUANTITY + 1 ) goto invalid_arguments;

    // Iterate through each command line argument
    for (size_t i = 1; i < argc; i++)
    {
        
        // Thread example?
        if ( strcmp(argv[i], "avl") == 0 )

            // Set the avl tree example flag
            examples_to_run[TREE_EXAMPLE_AVL] = true;

        // Thread pool example?
        else if ( strcmp(argv[i], "b") == 0 )
            
            // Set the B tree example flag
            examples_to_run[TREE_EXAMPLE_B] = true;

        // Schedule example?
        else if ( strcmp(argv[i], "binary") == 0 )

            // Set the binary tree example flag
            examples_to_run[TREE_EXAMPLE_BINARY] = true;

        // Default
        else goto invalid_arguments;
    }
    
    // Success
    return;

    // Set each example flag
    all_examples:
    {

        // For each example ...
        for (size_t i = 0; i < TREE_EXAMPLES_QUANTITY; i++)
        
            // ... set the example flag
            examples_to_run[i] = true;
        
        // Success
        return;
    }

    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
    }
}

int tree_avl_example ( int argc, const char *argv[] )
{

    // Formatting
    printf(
        "╭──────────────────╮\n"\
        "│ AVL tree example │\n"\
        "╰──────────────────╯\n"\
        "This example TODO: Describe example.\n\n"
    );

    // Success
    return 1;
}

int tree_b_example ( int argc, const char *argv[] )
{

    // Formatting
    printf(
        "╭────────────────╮\n"\
        "│ B tree example │\n"\
        "╰────────────────╯\n"\
        "This example creates a B tree from the DNA of E. Coli\n\n"
    );
    
    // Initialized data
    b_tree *p_b_tree = { 0 };

    // Construct a B tree
    if ( b_tree_construct(&p_b_tree, "output.b_tree", 0, 3, 64) == 0 ) goto failed_to_create_b_tree;

    // Add data to the B tree
    goto add_e_coli_genome;

    // Done
    done_adding_genome:

    // Print the quantity of keys in the B tree
    printf("%d\n", b_tree_insert(p_b_tree, 1, 1));

    // Write the B tree to the disk
    // if ( b_tree_flush(p_b_tree) == 0 ) goto failed_to_flush_b_tree;

    // Destroy the B tree
    // if ( b_tree_destroy(&p_b_tree) == 0 ) goto failed_to_destroy_b_tree;

    // Load the B tree
    // if ( b_tree_load(&p_b_tree, "output.b_tree") == 0 ) goto failed_to_load_b_tree;

    // Query the B tree
    //
    
    // TODO: More stuff

    // Success
    return 1;

    // Parse and insert the e coli genome into the B tree
    add_e_coli_genome:
    {

        // Initialized data
        size_t file_size = load_file("../ecoli.genome", 0, false);
        unsigned long long sequence_id = 0;
        char  _buffer[B_TREE_EXAMPLE_SEQUENCE_LENGTH + 1] = { 0 },
             *file_contents = TREE_REALLOC(0, file_size);

        // Error check
        if ( file_contents == (void *) 0 ) goto failed_to_load_file;

        // Read the file
        load_file("../ecoli.genome", file_contents, false);

        // Iterate through the file
        for (size_t i = 0; i < file_size - B_TREE_EXAMPLE_SEQUENCE_LENGTH; i++)
        {

            // Examine the next N bases
            for (size_t j = 0; j < B_TREE_EXAMPLE_SEQUENCE_LENGTH; j++)

                // Store the character
                _buffer[j] = file_contents[i + j];
            
            // Produce a value from the sequence
            ascii_to_u64_encoded_2_bit_slice(_buffer, &sequence_id);

            // Insert the property into the B tree
            b_tree_insert(p_b_tree, sequence_id, sequence_id);
        }
        
        // Done
        goto done_adding_genome;
    }

    // TODO: 
    failed_to_load_file:
    failed_to_create_b_tree:
    failed_to_flush_b_tree:
    failed_to_destroy_b_tree:
    failed_to_load_b_tree:

        // Error
        return 0;

    // Error handling
    {

    }
}

int tree_binary_example ( int argc, const char *argv[] )
{
    
    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭─────────────────────╮\n"\
        "│ Binary tree example │\n"\
        "╰─────────────────────╯\n"\
        "This example creates a balanced binary tree from a sorted list of keys\n"\
        "in linear time. This balanced binary tree is serialized to the disk,\n"
        "loaded. \n\n"
    );

    // Initialized data
    binary_tree *p_binary_tree           = 0,
                *p_binary_tree_from_disk = 0;
    FILE *p_file = (void *) 0;
    size_t random_index = 0;
    char *p_result = 0;
    char *values [BINARY_TREE_EXAMPLE_LIST_LENGTH] =
    { 
        "eight", "four", "twelve", "two", "six", "ten", "fourteen", "one",
        "three", "five", "seven", "nine", "eleven", "thirteen", "fifteen" 
    };
    unsigned long long keys [BINARY_TREE_EXAMPLE_LIST_LENGTH] = 
    {
        8,4,12,2,6,10,14,1,3,5,7,9,11,13,15
    };

    // Construct a tree
    if ( binary_tree_construct(&p_binary_tree, 0, 16) == 0 ) goto failed_to_construct_tree;

    // Iterate over each property
    for (size_t i = 0; i < 8; i++)

        // Store each property in the tree
        (void) binary_tree_insert(p_binary_tree, keys[i], values[i]);

    // Serialize the binary tree to a file
    if ( binary_tree_serialize(p_binary_tree, "../output.binary_tree", binary_tree_example_serializer) == 0 ) goto failed_to_serialize_binary_tree;

    // Destroy the binary tree
    if ( binary_tree_destroy(&p_binary_tree) == 0 ) goto failed_to_destroy_binary_tree;

    // TODO: Fix

    // Load the binary tree from the file
    //if ( binary_tree_parse(&p_binary_tree, "../output.binary_tree", 0, binary_tree_example_parser) == 0 ) goto failed_to_parse_binary_tree;

    // Compute a random key to search for
    //random_index = rand() % 15;

    // Query the binary tree
    //if ( binary_tree_search(p_binary_tree, (void *) random_index, &p_result) == 0 ) goto failed_to_search_binary_tree;

    // Success
    return 1;

    // Error handling
    {

        // Tree errors
        {
            failed_to_construct_tree:
                
                // Write an error message to standard out
                log_error("Error: Failed to construct binary tree!\n");

                // Error
                return EXIT_FAILURE;
            
            failed_to_serialize_binary_tree:
                                
                // Write an error message to standard out
                log_error("Error: Failed to serialize binary tree!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_parse_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to parse binary tree!\n");

                // Error
                return EXIT_FAILURE;
            
            failed_to_destroy_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to destroy binary tree!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_search_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to search binary tree!\n");

                // Error
                return EXIT_FAILURE;
        }
    }
}

int tree_quad_example ( int argc, const char *argv[] )
{

    // Formatting
    printf(
        "╭──────────────────╮\n"\
        "│ Quadtree example │\n"\
        "╰──────────────────╯\n"\
        "This example simulates particles in a 2D plane.\n\n"
    );
    
    // Success
    return 1;
}

int tree_r_example ( int argc, const char *argv[] )
{

    // Formatting
    printf(
        "╭────────────────╮\n"\
        "│ R tree example │\n"\
        "╰────────────────╯\n"\
        "This example TODO: Describe example.\n\n"
    );
    
    // Success
    return 1;
}

int tree_red_black_example ( int argc, const char *argv[] )
{

    // Formatting
    printf(
        "╭────────────────────────╮\n"\
        "│ Red black tree example │\n"\
        "╰────────────────────────╯\n"\
        "This example TODO: Describe example.\n\n"
    );
    
    // Success
    return 1;
}

int ascii_to_u64_encoded_2_bit_slice ( const char *const p_text, unsigned long long *p_result )
{

    // Argument check
    if ( p_text   == (void *) 0 ) goto no_text;
    if ( p_result == (void *) 0 ) goto no_result;

    // Initialized data
    unsigned long long ret = 0;
    size_t c = -1;

    // Parse the text
    while ( p_text[c + 1] )
    {

        // Next character
        c++;

        // Shift everything left by two bits
        ret <<= 2;

        // Switch on the text
        switch ( p_text[c] )
        {
            case 'A':
                
                // Add 0b00
                ret += 0;

                // Done
                break;

            case 'C':
                
                // Add 0b01
                ret += 1;

                // Done
                break;

            case 'G':
                
                // Add 0b10
                ret += 2;

                // Done
                break;

            case 'T':
                
                // Add 0b11
                ret += 3;
                
                // Done 
                break;
            
            default:
                
                // Error
                goto unrecognized_character;
        }
    }

    // Return a value to the caller
    *p_result = ret;

    // Success
    return 1;

    // TODO:
    unrecognized_character:
    no_text:
    no_result:

        // Error
        return 0;

    // Error handling
    {
        
    }
}

int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Write the key to the output
    fwrite(&p_binary_tree_node->p_key, sizeof(void *), 1, p_file);

    // Write the value to the output
    fwrite(p_binary_tree_node->p_value, strlen(p_binary_tree_node->p_value), 1, p_file);

    // Pad the output ...
    for (size_t i = 0; i < ( sizeof(void *) - strlen(p_binary_tree_node->p_value) ); i++)

        // ... with zeros
        fputc('\0', p_file);

    // Success
    return 1;
}

int binary_tree_example_parser ( FILE *p_file, binary_tree_node **pp_binary_tree_node )
{

    // Read a key from the input
    // TODO: 


    // Read a value from the input
    // TODO: 

    // Success
    return 1;
}

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
