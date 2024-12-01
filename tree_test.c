/** !
 * tree tester
 * 
 * @file tree_test.c
 * 
 * @author Jacob Smith
 */
// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// log module
#include <log/log.h>

// sync module
#include <sync/sync.h>

// tree module
#include <tree/tree.h>
#include <tree/avl.h>
#include <tree/b.h>
#include <tree/binary.h>
#include <tree/red_black.h>

// Enumeration definitions
enum result_e
{
    zero     = 0,
    one      = 1,
    match    = 2,
    not_null = 3
};

enum tree_nodes_e
{
    NODE_A = 0b1000000,
    NODE_B = 0b0100000,
    NODE_C = 0b0010000,
    NODE_D = 0b0001000,
    NODE_E = 0b0000100,
    NODE_F = 0b0000010,
    NODE_G = 0b0000001
};

enum tree_blueprint_e 
{
    TREE_EMPTY   = 0,

    TREE_D       = 0b0001000,

    TREE_BD      = 0b0101000,
    TREE_DF      = 0b0001010,

    TREE_BDF     = 0b0101010,

    TREE_ABDF    = 0b1101010,
    TREE_BCDF    = 0b0111010,
    TREE_BDEF    = 0b0101110,
    TREE_BDFG    = 0b0101011,

    TREE_ABCDF   = 0b1111010,
    TREE_BDEFG   = 0b0101111,
    TREE_ABDEF   = 0b1101110,
    TREE_BCDEF   = 0b0111110,
    TREE_ABDFG   = 0b1101011,
    TREE_BCDFG   = 0b0111011,

    TREE_BCDEFG  = 0b0111111,
    TREE_ABDEFG  = 0b1101111,
    TREE_ABCDFG  = 0b1111011,
    TREE_ABCDEF  = 0b1111110,

    TREE_ABCDEFG = 0b1111111,

    TREE_BLUEPRINT_QUANTITY = 20
};

enum tree_blueprint_e _blueprints[TREE_BLUEPRINT_QUANTITY] =
{
    TREE_EMPTY,

    TREE_D,

    TREE_BD,
    TREE_DF,

    TREE_BDF,

    TREE_ABDF,
    TREE_BCDF,
    TREE_BDEF,
    TREE_BDFG,

    TREE_ABCDF,
    TREE_BDEFG,
    TREE_ABDEF,
    TREE_BCDEF,
    TREE_ABDFG,
    TREE_BCDFG,

    TREE_BCDEFG,
    TREE_ABDEFG,
    TREE_ABCDFG,
    TREE_ABCDEF,

    TREE_ABCDEFG
};

const char *_blueprint_text[] =
{
    [TREE_EMPTY]   = "_, _, _, _, _, _, _",              
    [TREE_D]       = "_, _, _, D, _, _, _",
    [TREE_BD]      = "_, B, _, D, _, _, _",
    [TREE_DF]      = "_, _, _, D, _, F, _",
    [TREE_BDF]     = "_, B, _, D, _, F, _",
    [TREE_ABDF]    = "A, B, _, D, _, F, _",
    [TREE_BCDF]    = "_, B, C, D, _, F, _",
    [TREE_BDEF]    = "_, B, _, D, E, F, _",
    [TREE_BDFG]    = "_, B, _, D, _, F, G",
    [TREE_ABCDF]   = "A, B, C, D, _, F, _",
    [TREE_BDEFG]   = "_, B, _, D, E, F, G",
    [TREE_ABDEF]   = "A, B, _, D, E, F, _",
    [TREE_BCDEF]   = "_, B, C, D, E, F, _",
    [TREE_ABDFG]   = "A, B, _, D, _, F, G",
    [TREE_BCDFG]   = "_, B, C, D, _, F, G",
    [TREE_BCDEFG]  = "_, B, C, D, E, F, G",
    [TREE_ABDEFG]  = "A, B, _, D, E, F, G",
    [TREE_ABCDFG]  = "A, B, C, D, _, F, G",
    [TREE_ABCDEF]  = "A, B, C, D, E, F, _",
    [TREE_ABCDEFG] = "A, B, C, D, E, F, G"
};

const char *_blueprint_file_paths[] =
{
    [TREE_EMPTY]   = "",
    [TREE_D]       = "D",
    [TREE_BD]      = "BD",
    [TREE_DF]      = "DF",
    [TREE_BDF]     = "BDF",
    [TREE_ABDF]    = "ABDF",
    [TREE_BCDF]    = "BCDF",
    [TREE_BDEF]    = "BDEF",
    [TREE_BDFG]    = "BDFG",
    [TREE_ABCDF]   = "ABCDF",
    [TREE_BDEFG]   = "BDEFG",
    [TREE_ABDEF]   = "ABDEF",
    [TREE_BCDEF]   = "BCDEF",
    [TREE_ABDFG]   = "ABDFG",
    [TREE_BCDFG]   = "BCDFG",
    [TREE_BCDEFG]  = "BCDEFG",
    [TREE_ABDEFG]  = "ABDEFG",
    [TREE_ABCDFG]  = "ABCDFG",
    [TREE_ABCDEF]  = "ABCDEF",
    [TREE_ABCDEFG] = "ABCDEFG"
};

// Type definitions
typedef enum result_e result_t;

// Global variables
int total_tests      = 0,
    total_passes     = 0,
    total_fails      = 0,
    ephemeral_tests  = 0,
    ephemeral_passes = 0,
    ephemeral_fails  = 0;

// Forward declarations
/** !
 * Print the time formatted in days, hours, minutes, seconds, miliseconds, microseconds
 * 
 * @param seconds the time in seconds
 * 
 * @return void
 */
void print_time_pretty ( double seconds );

/** !
 * Run all the tests
 * 
 * @param void
 * 
 * @return void
 */
void run_tests ( void );

/** !
 * Print a summary of the test scenario
 * 
 * @param void
 * 
 * @return void
 */
void print_final_summary ( void );

/** !
 * Print the result of a single test
 * 
 * @param scenario_name the name of the scenario
 * @param test_name     the name of the test
 * @param passed        true if test passes, false if test fails
 * 
 * @return void
 */
void print_test ( const char *scenario_name, const char *test_name, bool passed );

void test_tree_implementation ( const char *name, enum tree_type_e _type, enum tree_blueprint_e _blueprint );

bool test_tree_insert ( const char *name, int (*pfn_tree_constructor)(tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type), enum tree_blueprint_e _blueprint, enum tree_type_e _type, int letter, result_t expected );

int tree_clone ( tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type )
{

    // Initialized data
    tree *p_tree = (void *) 0;
    tree_create_identity _identity = (tree_create_identity)
    {
        ._type = TREE_CREATE_IDENTITY,
        .value_size = 8,
        .pfn_comparator = tree_compare,
        .pfn_key_accessor = tree_key_accessor,
        .p_next = 0
    };

    // Construct the tree
    tree_construct(&p_tree, _type, &_identity);
    
    // Add values
    if ( NODE_D & _content ) tree_insert(p_tree, 4);
    if ( NODE_B & _content ) tree_insert(p_tree, 6);
    if ( NODE_F & _content ) tree_insert(p_tree, 2);
    if ( NODE_A & _content ) tree_insert(p_tree, 7);
    if ( NODE_E & _content ) tree_insert(p_tree, 3);
    if ( NODE_C & _content ) tree_insert(p_tree, 5);
    if ( NODE_G & _content ) tree_insert(p_tree, 1);
    
    // Return a pointer to the caller
    *pp_tree = p_tree;
    
    // Success
    return 1;
}

// Entry point
int main ( int argc, const char* argv[] )
{
    
    // Suppress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    timestamp t0 = 0,
              t1 = 0;

    // Formatting
    printf(
        "╭─────────────╮\n"\
        "│ tree tester │\n"\
        "╰─────────────╯\n\n"
    );
    // Start
    t0 = timer_high_precision();

    // Run tests
    run_tests();

    // Stop
    t1 = timer_high_precision();

    // Report the time it took to run the tests
    log_info("tree took ");
    print_time_pretty ( (double) ( t1 - t0 ) / (double) timer_seconds_divisor() );
    log_info(" to test\n\n");

    // Exit
    return ( total_passes == total_tests ) ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool test_tree_insert ( const char *name, int (*pfn_tree_constructor)(tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type), enum tree_blueprint_e _blueprint, enum tree_type_e _type, int letter, result_t expected )
{

    // Initialized data
    tree *p_tree = (void *) 0;
    int rc = 0;

    // Construct the tree
    if ( pfn_tree_constructor(&p_tree, _blueprint, _type) == 0 ) goto no_tree;

    // Insert the property
    rc = tree_insert(p_tree, (void *) letter);

    // Success
    return (expected == rc);

    no_tree:

        // Error
        return false;
}

bool test_tree_search ( const char *name, int (*pfn_tree_constructor)(tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type), enum tree_blueprint_e _blueprint, enum tree_type_e _type, int letter, result_t expected )
{

    // Initialized data
    tree *p_tree = (void *) 0;
    int rc = 0;

    // Construct the tree
    if ( pfn_tree_constructor(&p_tree, _blueprint, _type) == 0 ) goto no_tree;

    // Search the property
    rc = tree_search(p_tree, (void *) letter, 0);

    // Success
    return (expected == rc);

    no_tree:

        // Error
        return false;
}

bool test_tree_remove ( const char *name, int (*pfn_tree_constructor)(tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type), enum tree_blueprint_e _blueprint, enum tree_type_e _type, int letter, result_t expected )
{

    // Initialized data
    tree *p_tree = (void *) 0;
    int rc = 0;

    // Construct the tree
    if ( pfn_tree_constructor(&p_tree, _blueprint, _type) == 0 ) goto no_tree;

    // Remove the property
    rc = tree_remove(p_tree, (void *) letter, 0);

    // Success
    return (expected == rc);

    no_tree:

        // Error
        return false;
}

static char _last_traversal[8] = { 0 };

static int tree_dump ( const void *p_value )
{

    static int i = 0;

    if ( p_value == 0 ) i = 0, memset(&_last_traversal, 0, 8);

    switch ((size_t) p_value)
    {
        case 7: _last_traversal[i] = 'A'; break;
        case 6: _last_traversal[i] = 'B'; break;
        case 5: _last_traversal[i] = 'C'; break;
        case 4: _last_traversal[i] = 'D'; break;
        case 3: _last_traversal[i] = 'E'; break;
        case 2: _last_traversal[i] = 'F'; break;
        case 1: _last_traversal[i] = 'G'; break;
        default: return 0;
    }
    
    i++;

    // Success
    return 1;
}

bool test_tree_inorder ( const char *name, int (*pfn_tree_constructor)(tree **pp_tree, enum tree_blueprint_e _content, enum tree_type_e _type), enum tree_blueprint_e _blueprint, enum tree_type_e _type, const char *p_path, result_t expected )
{

    // Initialized data
    tree *p_tree = (void *) 0;
    int rc = 0;

    // Construct the tree
    if ( pfn_tree_constructor(&p_tree, _blueprint, _type) == 0 ) goto no_tree;

    // Remove the property
    rc = tree_traverse_inorder(p_tree, tree_dump);

    printf("%s\n", _last_traversal);

    tree_dump(0);

    // Success
    return (expected == rc);

    no_tree:

        // Error
        return false;
}

void print_time_pretty ( double seconds )
{

    // Initialized data
    double _seconds = seconds;
    size_t days = 0,
           hours = 0,
           minutes = 0,
           __seconds = 0,
           milliseconds = 0,
           microseconds = 0;

    // Days
    while ( _seconds > 86400.0 ) { days++;_seconds-=286400.0; };

    // Hours
    while ( _seconds > 3600.0 ) { hours++;_seconds-=3600.0; };

    // Minutes
    while ( _seconds > 60.0 ) { minutes++;_seconds-=60.0; };

    // Seconds
    while ( _seconds > 1.0 ) { __seconds++;_seconds-=1.0; };

    // milliseconds
    while ( _seconds > 0.001 ) { milliseconds++;_seconds-=0.001; };

    // Microseconds        
    while ( _seconds > 0.000001 ) { microseconds++;_seconds-=0.000001; };

    // Print days
    if ( days ) log_info("%zu D, ", days);
    
    // Print hours
    if ( hours ) log_info("%zu h, ", hours);

    // Print minutes
    if ( minutes ) log_info("%zu m, ", minutes);

    // Print seconds
    if ( __seconds ) log_info("%zu s, ", __seconds);
    
    // Print milliseconds
    if ( milliseconds ) log_info("%zu ms, ", milliseconds);
    
    // Print microseconds
    if ( microseconds ) log_info("%zu us", microseconds);
    
    // Done
    return;
}

void run_tests ( void )
{

    // Initialized data
    timestamp tree_avl_t0        = 0, tree_avl_t1        = 0,
              tree_b_t0          = 0, tree_b_t1          = 0,
              tree_binary_t0     = 0, tree_binary_t1     = 0,
              tree_red_black_t0  = 0, tree_red_black_t1  = 0;

    //////////////////////////
    // Test the binary tree //
    //////////////////////////

    // Formatting
    log_scenario("%s\n", "Binary tree");

    // Start timing binary tree
    tree_binary_t0 = timer_high_precision();

    // Foreach search tree
    for (size_t i = 0; i < TREE_BLUEPRINT_QUANTITY; i++)
    {

        // Initialized data
        enum tree_blueprint_e _blueprint = _blueprints[i];

        // Test binary tree
        test_tree_implementation("Binary tree", TREE_BINARY, _blueprint);

    }
    // Stop timing binary tree
    tree_binary_t1 = timer_high_precision();

    // Report the time it took to run the binary tree tests
    log_info("Binary tree took ");
    print_time_pretty ( (double)(tree_binary_t1-tree_binary_t0)/(double)timer_seconds_divisor() );
    log_info(" to test\n\n");

    {

        // ///////////////////////
        // // Test the AVL tree //
        // ///////////////////////

        // // Start timing avl
        // tree_avl_t0 = timer_high_precision();

        //     // Test avl tree
        //     test_tree_implementation("AVL tree", TREE_AVL, _blueprint);

        // // Stop timing avl
        // tree_avl_t1 = timer_high_precision();

        // // Report the time it took to run the core tests
        // log_info("AVL tree took ");
        // print_time_pretty ( (double)(tree_avl_t1-tree_avl_t0)/(double)timer_seconds_divisor() );
        // log_info(" to test\n\n");

        // /////////////////////
        // // Test the B tree //
        // /////////////////////

        // // Start timing b tree
        // tree_b_t0 = timer_high_precision();

        //     // Test b tree
        //     test_tree_implementation("B tree", TREE_B, _blueprint);

        // // Stop timing b tree
        // tree_b_t1 = timer_high_precision();

        // // Report the time it took to run the b tree tests
        // log_info("B tree took ");
        // print_time_pretty ( (double)(tree_b_t1-tree_b_t0)/(double)timer_seconds_divisor() );
        // log_info(" to test\n\n");


        // /////////////////////////////
        // // Test the red black tree //
        // /////////////////////////////

        // // Start timing red_black tree
        // tree_red_black_t0 = timer_high_precision();

        //     // Test red black tree
        //     test_tree_implementation("Red Black tree", TREE_RED_BLACK, _blueprint);

        // // Stop timing red_black tree
        // tree_red_black_t1 = timer_high_precision();

        // // Report the time it took to run the red_black tree tests
        // log_info("Red Black tree took ");
        // print_time_pretty ( (double)(tree_red_black_t1-tree_red_black_t0)/(double)timer_seconds_divisor() );
        // log_info(" to test\n\n");
    }

    // Done
    return;
}

void test_tree_accessors ( const char *name, enum tree_type_e _type, enum tree_blueprint_e _blueprint )
{
    
    // Insert
    print_test(name, "-> insert(A) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 7, (_blueprint & NODE_A) ? 0 : 1 ));
    print_test(name, "-> insert(B) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 6, (_blueprint & NODE_B) ? 0 : 1 ));
    print_test(name, "-> insert(C) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 5, (_blueprint & NODE_C) ? 0 : 1 ));
    print_test(name, "-> insert(D) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 4, (_blueprint & NODE_D) ? 0 : 1 ));
    print_test(name, "-> insert(E) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 3, (_blueprint & NODE_E) ? 0 : 1 ));
    print_test(name, "-> insert(F) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 2, (_blueprint & NODE_F) ? 0 : 1 ));
    print_test(name, "-> insert(G) -> ", test_tree_insert(name, tree_clone, _blueprint, _type, 1, (_blueprint & NODE_G) ? 0 : 1 ));

    // Formatting
    putchar('\n');

    // Search
    print_test(name, "-> search(A) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 7, (_blueprint & NODE_A) ? 1 : 0 ));
    print_test(name, "-> search(B) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 6, (_blueprint & NODE_B) ? 1 : 0 ));
    print_test(name, "-> search(C) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 5, (_blueprint & NODE_C) ? 1 : 0 ));
    print_test(name, "-> search(D) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 4, (_blueprint & NODE_D) ? 1 : 0 ));
    print_test(name, "-> search(E) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 3, (_blueprint & NODE_E) ? 1 : 0 ));
    print_test(name, "-> search(F) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 2, (_blueprint & NODE_F) ? 1 : 0 ));
    print_test(name, "-> search(G) -> ", test_tree_search(name, tree_clone, _blueprint, _type, 1, (_blueprint & NODE_G) ? 1 : 0 ));

    // Formatting
    putchar('\n');

    // Remove
    print_test(name, "-> remove(A) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 7, (_blueprint & NODE_A) ? 1 : 0 ));
    print_test(name, "-> remove(B) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 6, (_blueprint & NODE_B) ? 1 : 0 ));
    print_test(name, "-> remove(C) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 5, (_blueprint & NODE_C) ? 1 : 0 ));
    print_test(name, "-> remove(D) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 4, (_blueprint & NODE_D) ? 1 : 0 ));
    print_test(name, "-> remove(E) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 3, (_blueprint & NODE_E) ? 1 : 0 ));
    print_test(name, "-> remove(F) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 2, (_blueprint & NODE_F) ? 1 : 0 ));
    print_test(name, "-> remove(G) -> ", test_tree_remove(name, tree_clone, _blueprint, _type, 1, (_blueprint & NODE_G) ? 1 : 0 ));

    // Success
    return;
}

void test_tree_traversal ( const char *name, enum tree_type_e _type, enum tree_blueprint_e _blueprint )
{

    print_test(name, "-> inorder() -> ", test_tree_inorder(name, tree_clone, _blueprint, _type, 7, (_blueprint & NODE_A) ? 1 : 0 ));

    // Success
    return;
}

void test_tree_serializer ( const char *name )
{
    
    // Formatting
    log_scenario("%s\n", name);

    // Print the summary of this test
    print_final_summary();

    // Success
    return;
}

void test_tree_identity ( const char *name )
{
    
    // Formatting
    log_scenario("%s\n", name);

    // Print the summary of this test
    print_final_summary();

    // Success
    return;
}

void test_tree_implementation ( const char *name, enum tree_type_e _type, enum tree_blueprint_e _blueprint )
{

    // Initialized data
    char _buffer[64] = { 0 };
    timestamp tree_accessors_t0 = 0, tree_accessors_t1 = 0,
              tree_traversal_t0 = 0, tree_traversal_t1 = 0,
              tree_serialize_t0 = 0, tree_serialize_t1 = 0,
              tree_identity_t0  = 0, tree_identity_t1  = 0;

    // Formatting
    log_scenario("%s\n", _blueprint_text[_blueprint]);

    ////////////////////////
    // Test the accessors //
    ////////////////////////

    // Build a label
    snprintf(&_buffer, 64, "%s accessors", name);

    // Start timing accessors
    tree_accessors_t0 = timer_high_precision();

        // Test accessors tree
        test_tree_accessors(_blueprint_text[_blueprint], _type, _blueprint);

    // Stop timing accessors
    tree_accessors_t1 = timer_high_precision();

    // Report the time it took to run the accessors tests
    log_info("\n%s accessors took ", name);
    print_time_pretty ( (double)(tree_accessors_t1-tree_accessors_t0)/(double)timer_seconds_divisor() );
    log_info(" to test\n");

    // Print the summary of this test
    print_final_summary();

    ////////////////////////
    // Test the traversal //
    ////////////////////////

    // Build a label
    snprintf(&_buffer, 64, "%s traversal", name);

    // Start timing traversal
    tree_traversal_t0 = timer_high_precision();

        // Test traversal tree
        test_tree_traversal(_buffer, _type, _blueprint);

    // Stop timing traversal
    tree_traversal_t1 = timer_high_precision();

    // Report the time it took to run the traversal tests
    log_info("%s traversal took ", name);
    print_time_pretty ( (double)(tree_traversal_t1-tree_traversal_t0)/(double)timer_seconds_divisor() );
    log_info(" to test\n");

    // Print the summary of this test
    print_final_summary();

    // /////////////////////////
    // // Test the serializer //
    // /////////////////////////

    // // Build a label
    // snprintf(&_buffer, 64, "%s serialize", name);

    // // Start timing serialize
    // tree_serialize_t0 = timer_high_precision();

    //     // Test tree serializer
    //     test_tree_serializer(_buffer);

    // // Stop timing serialize
    // tree_serialize_t1 = timer_high_precision();

    // // Report the time it took to run the serialize tests
    // log_info("%s serializer took ", name);
    // print_time_pretty ( (double)(tree_serialize_t1-tree_serialize_t0)/(double)timer_seconds_divisor() );
    // log_info(" to test\n\n");

    // // Print the summary of this test
    // print_final_summary();

    // ///////////////////////
    // // Test the identity //
    // ///////////////////////

    // // Build a label
    // snprintf(&_buffer, 64, "%s identity", name);

    // // Start timing identity
    // tree_identity_t0 = timer_high_precision();

    //     // Test identity tree
    //     test_tree_identity(_buffer);

    // // Stop timing identity
    // tree_identity_t1 = timer_high_precision();

    // // Report the time it took to run the identity tests
    // log_info("%s identity took ", name);
    // print_time_pretty ( (double)(tree_identity_t1-tree_identity_t0)/(double)timer_seconds_divisor() );
    // log_info(" to test\n\n");

    // Success
    return;
}

void print_test ( const char *scenario_name, const char *test_name, bool passed )
{

    // Initialized data
    if ( passed )
        log_pass("%s %s\n",scenario_name, test_name),
        ephemeral_passes++;
    else 
        log_fail("%s %s\n", scenario_name, test_name),
        ephemeral_fails++;

    // Increment the test counter
    ephemeral_tests++;

    // Done
    return;
}

void print_final_summary ( void )
{

    // Accumulate
    total_tests  += ephemeral_tests,
    total_passes += ephemeral_passes,
    total_fails  += ephemeral_fails;

    // Print
    log_info("\nTests: %d, Passed: %d, Failed: %d (%%%.3f)\n",  ephemeral_tests, ephemeral_passes, ephemeral_fails, ((float)ephemeral_passes/(float)ephemeral_tests*100.f));
    log_info("Total: %d, Passed: %d, Failed: %d (%%%.3f)\n\n",  total_tests, total_passes, total_fails, ((float)total_passes/(float)total_tests*100.f));
    
    // Clear test counters for this test
    ephemeral_tests  = 0,
    ephemeral_passes = 0,
    ephemeral_fails  = 0;

    // Done
    return;
}
