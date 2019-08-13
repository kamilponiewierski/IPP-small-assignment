#ifndef IPP_MALE_QUANTUM_TREE_H
#define IPP_MALE_QUANTUM_TREE_H

#include <stdint-gcc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#define CHILDREN_COUNT 4
#define MAXIMUM_VALID_ENERGY_DIGITS 20

//Text constants
#define NULL_NODE_ERROR "Node is null, error\n"

/// Tree node structure which contains energy value, validity of history, and pointers which are used to loop abs class
/// @param energy positive value between 1 and 2^64 - 1
/// @param valid bool which represents validity of history in the tree
typedef struct node
{
    uint64_t energy;
    bool valid;
    struct node *prev;
    struct node *next;
    struct node *children[CHILDREN_COUNT];
} node;

/// Create the first (dummy) root
void init_tree(node *n);


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
bool can_be_deleted(node *n);

/// Deletes all children of node recursively going down
/// @param n node where deletion will happen
void delete_children(node *n);

/// Deletes single child of node under given index
/// @param n node which should have its child deleted
/// @param child_index index where deletion will happen
void delete_given_child(node *n, int child_index);

/// Checks if given history is valid
bool is_valid(node *root, char *history);

/// Prints all the values in the node @param ptr, along with empty children
void dbg_print_node(node *ptr);

/// Prints address of @param ptr
void dbg_print_node_address(node *ptr);

/// If node under @param history is valid, the node has its energy changed to value given in @param energy
void energy_two_param(char *history, uint64_t energy);

/// If @param history is valid and energy of node under given history is not NULL, prints node's energy value
void energy_one_param(char *history);

/// Every node which is a prefix of @param history is rendered valid
void declare(char *history);

/// Sets @param energy to whole abstraction class (loop), stops when it encounters @param abs_class again
void set_energy_to_abs_class(node *abs_class, uint64_t energy);

/// Puts @param n between two nodes of @param abs_class, sets its energy to @param energy
void add_node_to_abs_class(node *abs_class, node *n, uint64_t energy);

/// If both histories are valid, and at least one of @param node_a / @param node_b has assigned energy
/// its energies are rendered equal and become part of one abstraction class.
/// If both nodes have assigned energy the new energy is equal to arithmetic average, rounded down
/// If nodes already belong to the same abs class, nothing is changed.
void equal_nodes(node *node_a, node *node_b);


#endif //IPP_MALE_QUANTUM_TREE_H
