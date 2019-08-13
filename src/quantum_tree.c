//
// Created by kamil on 24.07.19.
//

#include "quantum_tree.h"


void init_tree(node *n)
{
    init_node(n);
    n->valid = -1;
}

void init_node(node *n)
{
    n->energy = 0;
    n->valid = false;
    n->prev = n;
    n->next = n;

    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        n->children[i] = NULL;
    }
}

node *get_node()
{
    node *ptr = NULL;
    ptr = (node *) malloc(sizeof(node));
    if (!ptr)
    {
        // Allocation of memory failed, program will exit
        perror("malloc");
        return NULL;
    }
    init_node(ptr);
    return ptr;
}

void dbg_print_node(node *n)
{
    if (n == NULL)
    {
        printf(NULL_NODE_ERROR);
        return;
    }

    printf("Energy = %" PRId64 "\n", n->energy);
    fputs("Valid = ", stdout);
    fputs(n->valid ? "true\n" : "false\n", stdout);
    printf("Nulls: ");
    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        if (n->children[i] == NULL)
        {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

void add_child(node *n, int child_index)
{
    if (n->children[child_index] == NULL)
        n->children[child_index] = get_node();
}

bool has_children(node *n)
{
    int count_null_nodes = 0;
    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        if (n->children[i] == NULL)
            count_null_nodes++;
    }

    if (count_null_nodes == CHILDREN_COUNT)
        return false;
    else
        return true;
}

bool can_be_deleted(node *n)
{
    bool subnodes_exist = has_children(n);

    if (n->energy == 0 && n->prev == n && n->next == n && n->valid == false && subnodes_exist == false)
    {
        return true;
    } else
    {
        return false;
    }
}

void delete_given_child(node *n, int child_index)
{
    if (child_index < CHILDREN_COUNT && n->children[child_index] != NULL)
    {
        if (can_be_deleted(n->children[child_index]))
        {
            free(n->children[child_index]);
            n->children[child_index] = NULL;
        } else
        {
            delete_children(n->children[child_index]);
            delete_given_child(n, child_index);
        }
    }
}

void delete_children(node *n)
{
    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        delete_given_child(n, i);
    }
}

void dbg_print_node_address(node *ptr)
{
    printf("%p\n", &ptr);
}