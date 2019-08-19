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
    if (root_node != NULL && *history != '\0')
    {
        assert_inside_history(*history);

        int index = *history - '0';

        if (root_node->children[index] == NULL)
        {
            return false;
        } else
        {
            if (*(history + 1) == '\0')
            {
                // TODO maybe would be better to not care about tree root and just return ->valid ?
                if (root_node->children[index]->valid == 1)
                {
                    return true;
                } else
                {
                    return false;
                }
            } else
            {
                return is_valid((history + 1), root_node->children[index]);
            }
        }
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
    if (root_node != NULL && *history != '\0')
    {
        assert_inside_history(*history);
        int index = *history - '0';
        if (root_node->children[index] != NULL)
        {
            energy_one_param((history + 1), root_node->children[index]);
        }
    } else if (root_node != NULL && *history == '\0')
    {
        if (root_node->valid == 1)
        {
            printf("%" PRId64 "\n", root_node->energy);
        }
    }
}
