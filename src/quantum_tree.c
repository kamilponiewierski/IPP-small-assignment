#include "quantum_tree.h"

node *create_root()
{
    node *n = get_node();
    n->valid = -1;
    return n;
}

void init_node(node *n)
{
    n->energy = 0;
    n->valid = 0;
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
        // Allocation of memory failed
        perror("malloc");
        // TODO tree_cleanup here
        exit(1);
    }
    init_node(ptr);
    return ptr;
}

void add_child(node *n, int child_index)
{
    if (n->children[child_index] == NULL)
        n->children[child_index] = get_node();
}

bool has_children(node *n)
{
    if (n == NULL)
    {
        return false;
    }

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
    if (n == NULL)
        return true;

    bool subnodes_exist = has_children(n);

    if (n->energy == 0 && n->prev == n && n->next == n && n->valid == 0 && subnodes_exist == false)
    {
        return true;
    } else
    {
        return false;
    }
}

void remove_node_from_abs_class(node **node_t)
{
    if (*(node_t) != NULL)
    {
        (*node_t)->next->prev = (*node_t)->prev;
        (*node_t)->prev->next = (*node_t)->next;

        (*node_t)->next = *node_t;
        (*node_t)->prev = *node_t;
    }
}

void delete_given_child(node *n, int child_index)
{
    if (child_index < CHILDREN_COUNT && n->children[child_index] != NULL)
    {
        remove_node_from_abs_class(&(n->children[child_index]));
        delete_children(n->children[child_index]);

        n->valid = 0;
        n->energy = 0;

        free(n->children[child_index]);
        n->children[child_index] = NULL;
    }
}

void delete_children(node *n)
{
    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        delete_given_child(n, i);
    }
}

void clear_tree(node **tree_root)
{
    delete_children(*tree_root);
    free(*tree_root);
    *tree_root = NULL;
}

void dbg_print_node(node **n)
{
    if (n == NULL)
    {
        printf(NULL_NODE_ERROR);
        return;
    }

    printf("Energy = %" PRId64 "\n", (*n)->energy);
    fputs("Valid = ", stdout);
    fputs((*n)->valid ? "true\n" : "false\n", stdout);
    printf("Nulls: ");
    for (int i = 0; i < CHILDREN_COUNT; i++)
    {
        if ((*n)->children[i] == NULL)
        {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

void set_energy_to_abs_class(node *abs_class, uint64_t energy)
{
    node *next_node = abs_class;
    node *ptr_to_abs_class = abs_class->prev->next;

    do
    {
        next_node->energy = energy;
        next_node = next_node->next;
    } while (next_node != ptr_to_abs_class);
}
