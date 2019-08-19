#include "quantum_functions.h"

int char_digit_to_int(char c)
{
    assert('0' <= c && c <= '9');
    return c - '0';
}

void assert_inside_history(char c)
{
    assert(HISTORY_START_CHAR <= c && c <= HISTORY_END_CHAR);
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

void declare(char *history, node *root_node)
{
    // calls helper to avoid printing too many times
    if (check_input_history(history))
    {
        declare_helper(history, root_node);
        fputs(CONFIRM_STRING, stdout);
    } else
    {
        fputs(ERROR_STRING, stdout);
    }

}

bool is_valid(char *history, node *root_node)
{
    node **tmp = get_node_under_history(history, root_node);

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

void valid(char *history, node *root_node)
{
    if (check_input_history(history))
    {
        if (is_valid(history, root_node))
        {
            fputs(YES_STRING, stdout);
        } else
        {
            fputs(NO_STRING, stdout);
        }
    } else
    {
        //TODO errors put out outside the function
        fputs(ERROR_STRING, stdout);
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
            } else
            {
                // TODO
                printf(ERROR_STRING);
            }
        } else
        {
            assert_inside_history(*history);
            energy_two_param_helper(history + 1, energy, node->children[*history - '0']);
        }
    }
}

void energy_two_param(char *history, uint64_t energy, node *root_node)
{
    energy_two_param_helper(history, energy, root_node);
    printf("energy 2 param ended\n");

}

void energy_one_param(char *history, node *root_node)
{
    node **tmp = get_node_under_history(history, root_node);
    if (tmp != NULL && (*tmp)->valid == 1)
    {
        printf("%" PRId64 "\n", (*tmp)->energy);
    } else
    {
        printf(ERROR_STRING);
    }
}

int remove_quantum_helper(char *history, node *node_t)
{
    if (node_t != NULL && *history != '\0')
    {
        int index = char_digit_to_int(*history);
        if (node_t->children[index] != NULL)
        {
            remove_quantum_helper((history + 1), node_t->children[index]);
        }

        if (*(history + 2) == '\0')
        {
            index = char_digit_to_int(*(history + 1));
            delete_children(node_t->children[index]);
            free(node_t->children[index]);
            node_t->children[index] = NULL;
            return 0;
        }
    }
}

void remove_quantum(char *history, node *root_node)
{
    if (check_input_history(history))
    {
        int result = remove_quantum_helper(history, root_node);
        if (result)
        {

        }
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
