//
// Created by kamil on 25.08.2019.
//

#ifndef IPP_MALE_DEFINES_H
#define IPP_MALE_DEFINES_H

#define serr(args...) fprintf(stderr, args)

#define OK_STRING "OK\n"
#define ERROR_STRING "ERROR\n"
#define YES_STRING "YES\n"
#define NO_STRING "NO\n"
#define NULL_NODE_ERROR "Node is null, error\n"

// input commands
#define CMD_DECLARE "DECLARE"
#define CMD_VALID "VALID"
#define CMD_ENERGY "ENERGY"
#define CMD_EQUAL "EQUAL"
#define CMD_REMOVE "REMOVE"

#define HISTORY_START_CHAR '0'
#define HISTORY_END_CHAR '3'

#define CHILDREN_COUNT 4

// maximum number of digits which can be stored in uint64
#define MAXIMUM_VALID_ENERGY_DIGITS 20

#define STARTING_BUFFER_SIZE 32

#endif //IPP_MALE_DEFINES_H
