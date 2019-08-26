#ifndef IPP_MALE_QUANTUM_FUNCTIONS_H
#define IPP_MALE_QUANTUM_FUNCTIONS_H

#include <string.h>
#include <stdint.h>
#include "quantum_tree.h"
#include "defines.h"

void quantum_initialize();

int quantum_cleanup();

/// Helper function which checks if the string is a correct entry for other functions
bool check_input_history(char *string);

/// Every quantum history which is a prefix of given history becomes valid
/// @param history is a string of characters 0, 1, 2, 3, which ends with \0
void declare(char *history);

/// Every quantum history which has a prefix given in parameter becomes invalid
void remove_quantum(char *history);

/// Checks if given history is valid, helper for valid function
bool is_valid(char *history);

/// Prints "YES" if history is valid, "NO" otherwise
void valid(char *history);

/// If node under @param history is valid, the node has its energy changed to value given in energy
void energy_two_param(char *history, uint64_t energy);

/// If @param history is valid and energy of node under given history is not NULL, prints node's energy value
void energy_one_param(char *history);

/// If both histories are valid, and at least one of node_a / node_b has assigned energy
/// its energies are rendered equal and become part of one abstraction class.
/// If both nodes have assigned energy the new energy is equal to arithmetic average, rounded down
/// If nodes already belong to the same abs class, nothing is changed.
void equal(char *history_a, char *history_b);

/// Iterates through tree and returns pointer to a node under given history
node **get_node_under_history(char *history);

#endif //IPP_MALE_QUANTUM_FUNCTIONS_H
