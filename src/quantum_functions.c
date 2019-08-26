#include "quantum_functions.h"

static node *tree_root = NULL;

void quantum_initialize()
{
    assert(tree_root == NULL);
    tree_root = create_root();

    if (tree_root == NULL)
        exit(1);
}

int quantum_cleanup()
{
    delete_children(tree_root);
    free(tree_root);
    return 0;
}

int char_digit_to_int(char c)
{
    assert('0' <= c && c <= '9');
    return c - '0';
}

void assert_inside_history(char c)
{
    assert(HISTORY_START_CHAR <= c && c <= HISTORY_END_CHAR);
}

void error_to_stderr()
{
    fputs(ERROR_STRING, stderr);
}

bool check_input_history(char *string)
{
    for (unsigned long i = 0; i < strlen(string); i++)
    {
        if (*(string + i) == '\0')
            return true;

        if (*(string + i) < HISTORY_START_CHAR || HISTORY_END_CHAR < *(string + i))
            return false;
    }
}

void declare_helper(char *history, node *node)
{
    if (node != NULL && *history != '\0')
    {
        assert_inside_history(*history);
        int index = *history - '0';
        add_child(node, index);
        node->children[index]->valid = 1;
        declare_helper((history + 1), node->children[index]);
    }
}

void declare(char *history)
{
    // calls helper to avoid printing too many times
    if (check_input_history(history))
    {
        declare_helper(history, tree_root);
        fputs(OK_STRING, stdout);
    }
    else
    {
        error_to_stderr();
    }

}

bool is_valid(char *history)
{
    node **tmp = get_node_under_history(history);
    if (tmp == NULL)
        return false;
        // checking eq 1 assures we won't have valid return true on tree_root
    else if ((*tmp)->valid == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void valid(char *history)
{
    if (check_input_history(history))
    {
        if (is_valid(history))
        {
            fputs(YES_STRING, stdout);
        }
        else
        {
            fputs(NO_STRING, stdout);
        }
    }
    else
    {
        error_to_stderr();
    }

}


int energy_two_param_helper(char *history, uint64_t energy)
{
    node *tmp = *get_node_under_history(history);

    if (tmp != NULL)
    {
        if (tmp->valid == 1)
        {
            if (energy != tmp->energy)
                set_energy_to_abs_class(tmp, energy);

            return 0;
        }
        else
            return 1;
    }
    else
        return 1;
}

void energy_two_param(char *history, uint64_t energy)
{
    int tmp = energy_two_param_helper(history, energy);
    if (tmp == 0)
    {
        printf(OK_STRING);
    }
    else
    {
        error_to_stderr();
    }
}

void energy_one_param(char *history)
{
    node **tmp = get_node_under_history(history);
    if (tmp != NULL && (*tmp)->valid == 1)
    {
        printf("%" PRId64 "\n", (*tmp)->energy);
    }
    else
    {
        error_to_stderr();
    }
}

// returns 0 if successful, 1 otherwise
int remove_quantum_helper(char *history, node *node_t)
{
    if (node_t != NULL && *history != '\0')
    {
        int index = char_digit_to_int(*history);

        // pointer to that node is needed to delete it, so we stop when we find null one char ahead
        // it's done before recursive call
        if (*(history + 1) == '\0')
        {
            index = char_digit_to_int(*(history));
            delete_given_child(node_t, index);
            return 0;
        }

        if (node_t->children[index] != NULL)
        {
            return remove_quantum_helper((history + 1), node_t->children[index]);
        }
        else
            return 1;
    }
    else return 1;
}

void remove_quantum(char *history)
{
    if (check_input_history(history))
    {
        int result = remove_quantum_helper(history, tree_root);
        if (result == 0)
        {
            printf(OK_STRING);
        }
        else
            error_to_stderr();
    }
    else
    {
        error_to_stderr();
    }
}

node **get_node_under_history(char *history)
{
    node **result = &tree_root;
    int index;

    for (; *history != '\0'; history++)
    {
        if (*history < '0' || '3' < *history)
        {
            return NULL;
        }

        index = char_digit_to_int(*history);

        // if we have to go through null node, we can't get a valid node after that
        if ((*result)->children[index] == NULL)
            return NULL;

        result = &(*result)->children[index];
    }

    return result;
}

void join_abs_class(node **node_a, node **node_b)
{
    if (node_a != NULL && node_b != NULL)
    {
        (*node_a)->prev->next = (*node_b)->next;
        (*node_b)->next->prev = (*node_a)->prev;

        (*node_a)->prev = (*node_b);
        (*node_b)->next = (*node_a);
    }
}

void equal(char *history_a, char *history_b)
{
    node **node_a = get_node_under_history(history_a);
    node **node_b = get_node_under_history(history_b);

    if (node_a != NULL && node_b != NULL)
    {
        // both histories are valid and have assigned energy
        if ((*node_a)->valid == 1 && (*node_b)->valid == 1 && (*node_a)->energy > 0 && (*node_b)->energy > 0)
        {
            join_abs_class(node_a, node_b);

            // new energy is equal to arithmetic mean of energy of both nodes
            uint64_t energy = ((*node_a)->energy + (*node_b)->energy) / 2;
            set_energy_to_abs_class(*node_a, energy);
        }
        else if ((*node_a)->valid == 1 && (*node_a)->energy > 0 && (*node_b)->valid == 1)
        {
            join_abs_class(node_a, node_b);
            set_energy_to_abs_class(*node_a, (*node_a)->energy);
        }
        else if ((*node_b)->valid == 1 && (*node_b)->energy > 0 && (*node_a)->valid == 1)
        {
            join_abs_class(node_a, node_b);
            set_energy_to_abs_class(*node_b, (*node_b)->energy);
        }
        fputs(OK_STRING, stdout);
    }
    else
        error_to_stderr();
}

