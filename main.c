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

// Structure definitions
struct number_and_string_s
{
    char _string[16];
    double number;
};

// Type definitions
typedef struct number_and_string_s number_and_string;

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
 * Example binary tree comparator
 * 
 * @param p_a pointer to a
 * @param p_b pointer to b 
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_comparator ( const void *const p_a, const void *const p_b );

/** !
 * Example binary tree key accessor
 * 
 * @param pp_result result
 * @param p_value   the value to access 
 * 
 * @return 1 on success, 0 on error
*/
const void *const binary_tree_example_key_accessor (const void *const p_value);

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
int binary_tree_example_parser ( FILE *p_file, binary_tree_node *p_binary_tree_node );

/** !
 * Print a binary tree node to standard out
 * 
 * @param p_value the value
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_print_node ( void *p_value );

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

    // Seed the RNG for later
    srand(time(0));

    // Formatting
    log_info("╭──────────────╮\n");
    log_info("│ tree example │\n");
    log_info("╰──────────────╯\n");
    printf(
        "The tree library provides high level abstractions for %d different trees.\n"\
        "The AVL tree, the B tree, the binary tree, the quadtree, the R tree, and the red black tree.\n\n"\
        "An AVL tree is self balancing binary search tree; suitable for frequent searching.\n"\
        "A B tree is a self balancing, flat search tree; suitable for storage systems and large data.\n"\
        "A Binary tree is the most primitive tree.\n"\
        "A Quadtree is a tree where each node has four childern; suitable for dynamic spatial computing.\n"\
        "An R tree is a self balancing, flat search tree; suitable for large spatial data.\n"\
        "A Red Black tree is an unbalanced binary search tree; suitable for frequent insertions / deletions.\n\n",
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
        //if ( tree_b_example(argc, argv) == 0 ) goto failed_to_run_b_tree_example;
        
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
    log_info("╭──────────────────╮\n");
    log_info("│ AVL tree example │\n");
    log_info("╰──────────────────╯\n");
    printf("This example TODO: Describe example.\n\n");

    // Success
    return 1;
}

int tree_b_example ( int argc, const char *argv[] )
{

    // Formatting
    log_info("╭────────────────╮\n");
    log_info("│ B tree example │\n");
    log_info("╰────────────────╯\n");
    printf(
        "This example creates a B tree from an E. Coli genome. Each property stores a \n"\
        "nucleotide sequence of length 8. The B tree is serialized to the disk, loaded,\n"\
        "and the most frequent nucleotide sequences are printed to standard out\n\n"
    );
    
    // Initialized data
    b_tree *p_b_tree = (void *) 0;

    remove("resources/output.b_tree");

    // Construct a B tree
    if ( b_tree_construct(&p_b_tree, "resources/output.b_tree", 0, 2, 64) == 0 ) goto failed_to_create_b_tree;

    b_tree_insert(p_b_tree, (void *) 1);
    b_tree_insert(p_b_tree, (void *) 2);
    b_tree_insert(p_b_tree, (void *) 3);
    b_tree_insert(p_b_tree, (void *) 4);
    b_tree_insert(p_b_tree, (void *) 5);
    b_tree_insert(p_b_tree, (void *) 6);
    b_tree_traverse_inorder(p_b_tree, (void *)1);

    return 1;

    // Example
    {
        // Add data to the B tree
        //goto add_e_coli_genome;

        // Done
        //done_adding_genome:

        // Print the quantity of keys in the B tree
        //printf("%d\n", b_tree_insert(p_b_tree, 1, 1));

        // Write the B tree to the disk
        // if ( b_tree_flush(p_b_tree) == 0 ) goto failed_to_flush_b_tree;

        // Destroy the B tree
        // if ( b_tree_destroy(&p_b_tree) == 0 ) goto failed_to_destroy_b_tree;

        // Load the B tree
        // if ( b_tree_load(&p_b_tree, "output.b_tree") == 0 ) goto failed_to_load_b_tree;

        // Query the B tree
        //
        
        // TODO: More stuff
    }

    // Success
    return 1;

    // Parse and insert the e coli genome into the B tree
    add_e_coli_genome:
    {

        // // Initialized data
        // size_t file_size = load_file("resources/ecoli.genome", 0, false);
        // unsigned long long sequence_id = 0;
        // char  _buffer[B_TREE_EXAMPLE_SEQUENCE_LENGTH + 1] = { 0 },
        //      *file_contents = TREE_REALLOC(0, file_size);

        // // Error check
        // if ( file_contents == (void *) 0 ) goto failed_to_load_file;

        // // Read the file
        // load_file("resources/ecoli.genome", file_contents, false);

        // // Iterate through the file
        // for (size_t i = 0; i < file_size - B_TREE_EXAMPLE_SEQUENCE_LENGTH; i++)
        // {

        //     // Examine the next N bases
        //     for (size_t j = 0; j < B_TREE_EXAMPLE_SEQUENCE_LENGTH; j++)

        //         // Store the character
        //         _buffer[j] = file_contents[i + j];
            
        //     // Produce a value from the sequence
        //     ascii_to_u64_encoded_2_bit_slice(_buffer, &sequence_id);

        //     // Insert the property into the B tree
        //     b_tree_insert(p_b_tree, (void *)sequence_id, (void *)sequence_id);
        // }
        
        // // Done
        // goto done_adding_genome;
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
    log_info("╭─────────────────────╮\n");
    log_info("│ Binary tree example │\n");
    log_info("╰─────────────────────╯\n");
    printf(
        "This example creates a balanced binary tree from a sorted list of keys\n"\
        "in linear time. This balanced binary tree is serialized to the disk,\n"
        "loaded, and a key is searched for at random.\n\n"
    );

    // Initialized data
    binary_tree *p_binary_tree = 0;
    size_t random_index = ( rand() % 15 ) + 1;
    number_and_string *p_result = 0;
    char *keys [BINARY_TREE_EXAMPLE_LIST_LENGTH] =
    { 
        "eight", "four", "twelve", "two", "six", "ten", "fourteen", "one",
        "three", "five", "seven", "nine", "eleven", "thirteen", "fifteen" 
    };
    unsigned long long values [BINARY_TREE_EXAMPLE_LIST_LENGTH] = { 8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 };

    // Log
    fprintf(stderr, "Constructing tree... ");

    // Construct a tree
    if (binary_tree_construct(&p_binary_tree, binary_tree_example_comparator, binary_tree_example_key_accessor, sizeof(number_and_string)) == 0 ) goto failed_to_construct_tree;

    // Log
    fprintf(stderr, "DONE\nInserting properties... ");

    // Iterate over each property
    for (size_t i = 0; i < 15; i++)
    {
        
        // Initialized data
        number_and_string *p_number_and_string = malloc(sizeof(number_and_string));

        // Store the number
        p_number_and_string->number = values[i];

        // Copy the string
        strncpy(p_number_and_string->_string, keys[i], sizeof(p_number_and_string->_string));

        // Store the property in the tree
        (void) binary_tree_insert(p_binary_tree, p_number_and_string);
    }
    
    // Log
    fprintf(stderr, "DONE\nSerializing tree... ");

    // Serialize the binary tree to a file
    if ( binary_tree_serialize(p_binary_tree, "resources/output.binary_tree", binary_tree_example_serializer) == 0 ) goto failed_to_serialize_binary_tree;

    // Log
    fprintf(stderr, "DONE\nDestroying tree... ");

    // Destroy the binary tree
    if ( binary_tree_destroy(&p_binary_tree) == 0 ) goto failed_to_destroy_binary_tree;

    // Log
    fprintf(stderr, "DONE\nParsing tree... ");

    // Load the binary tree from the file
    if ( binary_tree_parse(&p_binary_tree, "resources/output.binary_tree", binary_tree_example_comparator, binary_tree_example_key_accessor, (fn_binary_tree_parse *) binary_tree_example_parser) == 0 ) goto failed_to_parse_binary_tree;
    
    // Log
    fprintf(stderr, "DONE\nPrinting tree... \n\n");
    
    // Traverse the binary tree using the in order technique
    binary_tree_traverse_inorder(p_binary_tree, (fn_binary_tree_traverse *)binary_tree_print_node);

    // Query the binary tree
    if ( binary_tree_search(p_binary_tree, "thirteen", &p_result) == 0 ) goto failed_to_search_binary_tree;

    // Print the random index
    log_info("\nDONE\n\nSearching \"%s\" yields \"%lg\"\n\n", "thirteen", p_result->number);

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
    log_info("╭──────────────────╮\n");
    log_info("│ Quadtree example │\n");
    log_info("╰──────────────────╯\n");
    printf("This example simulates particles in a 2D plane.\n\n");
    
    // Success
    return 1;
}

int tree_r_example ( int argc, const char *argv[] )
{

    // Formatting
    log_info("╭────────────────╮\n");
    log_info("│ R tree example │\n");
    log_info("╰────────────────╯\n");
    printf("This example TODO: Describe example.\n\n");
    
    // Success
    return 1;
}

int tree_red_black_example ( int argc, const char *argv[] )
{

    // Formatting
    log_info("╭────────────────────────╮\n");
    log_info("│ Red black tree example │\n");
    log_info("╰────────────────────────╯\n");
    printf("This example TODO: Describe example.\n\n");
    
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

int binary_tree_example_comparator ( const void *const p_a, const void *const p_b )
{

    // Success
    return strcmp(((number_and_string *)p_b)->_string, ((number_and_string *)p_a)->_string);
}

const void *const binary_tree_example_key_accessor ( const void *const p_value )
{

    // Initialized data
    const number_and_string *p_number_and_string = p_value;

    // Success
    return &p_number_and_string->_string;
}

int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Write the key to the output
    fwrite(p_binary_tree_node->p_value, sizeof(number_and_string), 1, p_file);
    
    // Success
    return 1;
}

int binary_tree_example_parser ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Initialized data
    number_and_string *p_number_and_string = malloc(sizeof(number_and_string));

    // Read a string from the input
    fread(&p_number_and_string->_string, 16, 1, p_file);

    // Read a double from the input
    fread(&p_number_and_string->number, 8, 1, p_file);

    // Allocate memory for the value
    p_binary_tree_node->p_value = p_number_and_string;
    
    // Success
    return 1;
}

int binary_tree_print_node ( void *p_value )
{

    // Print the property
    log_info("%s\n", ((number_and_string *) p_value)->_string);

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
