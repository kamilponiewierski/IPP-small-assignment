#ifndef IPP_MALE_QUANTUM_TREE_H
#define IPP_MALE_QUANTUM_TREE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "defines.h"


/// Tree node structure which contains energy value, validity of history, and pointers which are used to loop abs class
/// @param energy positive value between 1 and 2^64 - 1
/// @param valid  represents validity of history in the tree, 0 represents invalid history, 1 means history is valid,
/// -1 is reserved for the root of the tree
typedef struct node
{
    uint64_t energy;
    short valid;
    struct node *prev;
    struct node *next;
    struct node *children[CHILDREN_COUNT];
} node;

/// Create the first (dummy) root
node *create_root();

/// Initializes a node with default values
void init_node(node *n);

/// Create a new node with default values, returns null if malloc failed
node *get_node();


/// Adds a child to node under given index, nothing happens if the pointer is not NULL
/// @param n node
/// @param child_index index of table under which a new node is created
void add_child(node *n, int child_index);

/// Checks if node has children
bool has_children(node *n);

/// Checks if node can be deleted safely
static bool can_be_deleted(node *n);

/// Deletes all children of node recursively going down
/// @param n node where deletion will happen
void delete_children(node *n);

/// Deletes single child of node under given index
/// @param n node which should have its child deleted
/// @param child_index index where deletion will happen
void delete_given_child(node *n, int child_index);


/// Clears whole tree and frees memory
void clear_tree(node **tree_root);

/// Prints all the values in the node @param ptr, along with empty children
void dbg_print_node(node *ptr);

/// Prints address of @param ptr
void dbg_print_node_address(node *ptr);

/// Sets @param energy to whole abstraction class (loop), stops when it encounters @param abs_class again
void set_energy_to_abs_class(node *abs_class, uint64_t energy);

/// Puts @param n between two nodes of @param abs_class, sets its energy to @param energy
void add_node_to_abs_class(node *abs_class, node *n, uint64_t energy);

/// Helper function for @fn equal in ./quantum_functions.c
void equal_nodes(node *node_a, node *node_b);

#endif //IPP_MALE_QUANTUM_TREE_H
