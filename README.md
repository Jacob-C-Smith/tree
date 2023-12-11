# tree
[![CMake](https://github.com/Jacob-C-Smith/tree/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Jacob-C-Smith/tree/actions/workflows/cmake.yml)

**Dependencies:**\
[![sync](https://github.com/Jacob-C-Smith/sync/actions/workflows/cmake.yml/badge.svg)](https://github.com/Jacob-C-Smith/sync/actions/workflows/cmake.yml)

 Implementation of different tree structures in C
 
 > 1 [Download](#download)
 >
 > 2 [Build](#build)
 >
 > 3 [Example](#example)
 >
 >> 3.1 [Example output](#example-output)
 >
 > 4 [Tester](#tester)
 >
 > 5 [Definitions](#definitions)
 >
 >> 5.1 [Type definitions](#type-definitions)
 >>
 >> 5.2 [Function definitions](#function-definitions)

 ## Download
 To download tree, execute the following command
 ```bash
 $ git clone https://github.com/Jacob-C-Smith/tree
 ```
 ## Build
 To build on UNIX like machines, execute the following commands in the same directory
 ```bash
 $ cd tree
 $ cmake .
 $ make
 ```
  This will build the example program, the tester program, and dynamic / shared libraries

  To build tree for Windows machines, open the base directory in Visual Studio, and build your desired target(s)
 ## Example
 To run the example program, execute this command
 ```
 $ ./tree_example
 ```
 ### Example output
 ```
 TODO
 ```
 [Source](main.c)

## Tester
 TODO: 
 
 ## Definitions
 ### Type definitions
```c
typedef struct binary_tree_s binary_tree;
typedef struct binary_tree_node_s binary_tree_node;

typedef int (tree_equal_fn)           (const void *a, const void *b)
typedef int (binary_tree_serialize_fn)(FILE *p_file, binary_tree_node *p_binary_tree_node);
typedef int (binary_tree_parse_fn)    (FILE *p_file, binary_tree *p_binary_tree, binary_tree_node **pp_binary_tree_node, unsigned long long node_pointer );
```

### Function definitions
 ```c
// Allocators
int binary_tree_create ( binary_tree **const pp_binary_tree );

// Constructors
int binary_tree_construct ( binary_tree **const pp_binary_tree, tree_equal_fn *pfn_is_equal, unsigned long long node_size );

// Accessors
int binary_tree_search ( const binary_tree *const p_binary_tree, const void *const p_key, const void **const pp_value );

// Mutators
int binary_tree_insert ( binary_tree *const p_binary_tree, const void *const p_key, const void  *const p_value );
int binary_tree_remove ( binary_tree *const p_binary_tree, const void *const p_key, const void **const p_value );

// Parser
int binary_tree_parse ( binary_tree **const pp_binary_tree, FILE *p_file, tree_equal_fn *pfn_is_equal, binary_tree_parse_fn *pfn_parse_node );

// Serializer
int binary_tree_serialize ( binary_tree *const p_binary_tree, FILE *p_file, binary_tree_serialize_fn *pfn_serialize_node );

// Destructors
int binary_tree_destroy ( binary_tree **const pp_binary_tree );
 ```
 