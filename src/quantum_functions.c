#include "quantum_functions.h"

static node *tree_root = NULL;

void quantum_initialize()
{
    assert(tree_root == NULL);

    tree_root = get_node();
    tree_root->valid = -1;
}

int quantum_remove()
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

void new_declare(char *history)
{
    if (check_input_history(history))
    {
        declare_helper(history, tree_root);
        fputs(OK_STRING, stdout);
    } else
    {
        error_to_stderr();
    }
}

void declare(char *history, node *root_node)
{
    // calls helper to avoid printing too many times
    if (check_input_history(history))
    {
        declare_helper(history, root_node);
        fputs(OK_STRING, stdout);
    } else
    {
        error_to_stderr();
    }

}

bool is_valid(char *history, node *root_node)
{
//    node **tmp = get_node_under_history(history, root_node);
    node **tmp = get_node_under_history(history, tree_root);
    if (tmp == NULL)
        return false;
        // TODO maybe would be better to not care about tree root and just return ->valid ?
    else if ((*tmp)->valid == 1)
    {
        return true;
    } else
    {
        return false;
    }
}

void new_valid(char *history)
{
    if (check_input_history(history))
    {
        if (is_valid(history, tree_root))
        {
            fputs(YES_STRING, stdout);
        } else
        {
            fputs(NO_STRING, stdout);
        }
    } else
    {
        //TODO errors put out outside the function
        error_to_stderr();
    }

}

void valid(char *history, node *root_node)
{
    dbg_print_node(tree_root);
    if (check_input_history(history))
    {
        if (is_valid(history, tree_root))
        {
            fputs(YES_STRING, stdout);
        } else
        {
            fputs(NO_STRING, stdout);
        }
    } else
    {
        //TODO errors put out outside the function
        error_to_stderr();
    }

}


int energy_two_param_helper(char *history, uint64_t energy, node *node)
{
    if (node != NULL)
    {
        if (*history == '\0')
        {
            if (node->valid == 1)
            {
                node->energy = energy;
                return 0;
            } else
            {
                return 1;
            }
        } else
        {
            assert_inside_history(*history);
            return energy_two_param_helper(history + 1, energy, node->children[*history - '0']);
        }
    } else
        return 1;
}

void energy_two_param(char *history, uint64_t energy, node *root_node)
{
    int tmp = energy_two_param_helper(history, energy, root_node);
    if (tmp == 0)
    {
        printf(OK_STRING);
    } else
    {
        error_to_stderr();
    }
}

void energy_one_param(char *history, node *root_node)
{

    node **tmp = get_node_under_history(history, root_node);
    if (tmp != NULL && (*tmp)->valid == 1)
    {
        printf("%" PRId64 "\n", (*tmp)->energy);
    } else
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

        // pointer to that node is needed to delete it, so we stop when we found it two chars ahead
        // it's done before recursive call
        if (*(history + 1) == '\0')
        {
            index = char_digit_to_int(*(history));
            delete_children(node_t->children[index]);
            free(node_t->children[index]);
            node_t->children[index] = NULL;
            return 0;
        }

        if (node_t->children[index] != NULL)
        {
            return remove_quantum_helper((history + 1), node_t->children[index]);
        } else
            return 1;
    } else return 1;
}

void remove_quantum(char *history, node *root_node)
{
    if (check_input_history(history))
    {
        int result = remove_quantum_helper(history, root_node);
        if (result == 0)
        {
            printf(OK_STRING);
        } else
            error_to_stderr();
    } else
    {
        error_to_stderr();
    }
}

node **get_node_under_history(char *history, node *root_node)
{
    node **result = &root_node;
    int index = -1;

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

void equal(char *history_a, char *history_b, node *root_node)
{
    node **node_a = get_node_under_history(history_a, root_node);
    node **node_b = get_node_under_history(history_b, root_node);

    if (node_a != NULL && node_b != NULL)
    {
        if ((*node_a)->valid == 1 && (*node_b)->valid == 1)
        {
            //TODO
        }
    } else
        error_to_stderr();
}

