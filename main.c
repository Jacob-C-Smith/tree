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

// Entry point
int main ( int argc, const char *argv[] )
{

    // Initialized data
    binary_tree *p_binary_tree = 0;
    char *p_value = 0;
    char *values [VALUE_COUNT] =
    { 
        "eight", "four", "twelve", "two", "six", "ten", "fourteen", "one",
        "three", "five", "seven", "nine", "eleven", "thirteen", "fifteen" 
    };
    int keys [VALUE_COUNT] = 
    {
        8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
    };

    // Construct a tree
    if ( binary_tree_construct(&p_binary_tree, 0) == 0 ) goto failed_to_construct_tree;

    // Iterate over each property
    for (size_t i = 0; i < VALUE_COUNT; i++)

        // Store each property in the tree
        binary_tree_insert(p_binary_tree, keys[i], values[i]);
    
    // Remove '7'
    binary_tree_remove(p_binary_tree, 7, &p_value);

    // Print the value
    printf("removed: %s\n", p_value);

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
        }
    }
}
