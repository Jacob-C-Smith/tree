// Standard library 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// tree
#include <tree/tree.h>
#include <tree/binary.h>

// Function declarations
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
 * Binary tree example program
 * 
 * @param argc argument count from entry point
 * @param argv argument vector from entry point
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example ( int argc, const char *argv[] );

// Entry point
int main ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Run the binary tree example
    if ( binary_tree_example(argc, argv) == 0 ) goto failed_to_run_binary_tree_example;

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        failed_to_run_binary_tree_example:
            
            // Write an error message to standard out
            printf("Error: Failed to run binary tree example!\n");

            // Error
            return EXIT_FAILURE;
    }
}

int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Write the key to the output
    fwrite(p_binary_tree_node->p_key, sizeof(void *), 1, p_file);

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

int binary_tree_example ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    binary_tree *p_binary_tree           = 0,
                *p_binary_tree_from_disk = 0;
    char *values [15] =
    { 
        "eight", "four", "twelve", "two", "six", "ten", "fourteen", "one",
        "three", "five", "seven", "nine", "eleven", "thirteen", "fifteen" 
    };
    unsigned long long keys [15] = 
    {
        8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
    };
    FILE *p_file = (void *) 0;

    // Construct a tree
    if ( binary_tree_construct(&p_binary_tree, 0, 16) == 0 ) goto failed_to_construct_tree;

    // Iterate over each property
    for (size_t i = 0; i < 15; i++)

        // Store each property in the tree
        binary_tree_insert(p_binary_tree, &keys[i], values[i]);

    // Open a file
    p_file = fopen("output.binary_tree", "wb+");

    // Serialize the binary tree to the file
    if ( binary_tree_serialize(p_binary_tree, p_file, binary_tree_example_serializer) == 0 ) goto failed_to_serialize_binary_tree;
    
    // Close the file
    fclose(p_file);

    // Success
    return 1;

    // Error handling
    {

        // Tree errors
        {
            failed_to_construct_tree:
                
                // Write an error message to standard out
                printf("Error: Failed to construct binary tree!\n");

                // Error
                return EXIT_FAILURE;
            
            failed_to_serialize_binary_tree:
                                
                // Write an error message to standard out
                printf("Error: Failed to serialize binary tree!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_parse_binary_tree:

                // Write an error message to standard out
                printf("Error: Failed to parse binary tree!\n");

                // Error
                return EXIT_FAILURE;
        }
    }
}
