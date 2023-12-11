// Standard library 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Tree
#include <tree/tree.h>
#include <tree/binary.h>

// Preprocessor defines
#define VALUE_COUNT 15

int serialize ( FILE *p_file, binary_tree_node *p_binary_tree_node )
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

// Entry point
int main ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    binary_tree *p_binary_tree           = 0,
                *p_binary_tree_from_disk = 0;
    char *values [VALUE_COUNT] =
    { 
        "eight", "four", "twelve", "two", "six", "ten", "fourteen", "one",
        "three", "five", "seven", "nine", "eleven", "thirteen", "fifteen" 
    };
    unsigned long long keys [VALUE_COUNT] = 
    {
        8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
    };
    FILE *p_file = fopen("output.binary_tree", "wb+");

    // Construct a tree
    if ( binary_tree_construct(&p_binary_tree, 0, 16) == 0 ) goto failed_to_construct_tree;

    // Iterate over each property
    for (size_t i = 0; i < VALUE_COUNT; i++)

        // Store each property in the tree
        binary_tree_insert(p_binary_tree, &keys[i], values[i]);
    
    // Serialize the binary tree to a file
    if ( binary_tree_serialize(p_binary_tree, p_file, serialize) == 0 ) goto failed_to_serialize_binary_tree;
    
    // Close the file
    fclose(p_file);

    // Open the file
    // p_file = fopen("output.binary_tree", "rb");

    // Construct a binary tree from a file
    // if ( binary_tree_parse(&p_binary_tree_from_disk, p_file, tree_compare_function, binary_tree_parse_function) == 0 ) goto failed_to_parse_binary_tree;

    // Close the file
    // fclose(p_file);

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {

        // Argument check
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
