#include "quantum_functions.h"

bool read_line(char **buffer, size_t *buffer_size)
{
    int c;
    unsigned int pos = 0;

    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        if (pos + 1 > *buffer_size)
        {
            *buffer_size *= 2;
            *buffer = realloc(*buffer, *buffer_size);

            if (*buffer == NULL)
            {
                fputs("realloc\n", stderr);
                exit(EXIT_FAILURE);
            }
        }

        (*buffer)[pos++] = (char) c;
    }

    (*buffer)[pos] = '\0';

    return c != EOF;
}

void energy_two_param_wrapper(char *arg1_str, char *arg2_str);

void process_line(char *buffer)
{
    size_t input_length = strlen(buffer) + 1;

    if (input_length == 1)
        return;

    if (buffer[0] == '#')
        return;

    char *command = strtok(buffer, " \n");
    char *arg1_str = strtok(NULL, " \n");
    char *arg2_str = strtok(NULL, " \n");
    char *remains = strtok(NULL, " \n");

    size_t cleaned_length = 0;

    if (command != NULL)
        cleaned_length += strlen(command) + 1;

    if (arg1_str != NULL)
        cleaned_length += strlen(arg1_str) + 1;

    if (arg2_str != NULL)
        cleaned_length += strlen(arg2_str) + 1;

    // extra characters or multiple whitespace
    if (remains != NULL || cleaned_length != input_length)
    {
        fputs(ERROR_STRING, stderr);
        return;
    }


    bool error_flag = 0;

    if (strcmp(command, CMD_EQUAL) == 0)
    {
        if (arg1_str != NULL && arg2_str != NULL)
            return equal(arg1_str, arg2_str);
        else
            error_flag = 1;
    }
    else if (strcmp(command, CMD_DECLARE) == 0)
    {
        if (arg1_str != NULL && arg2_str == NULL)
            return declare(arg1_str);
        else
            error_flag = 1;
    }
    else if (strcmp(command, CMD_REMOVE) == 0)
    {
        if (arg1_str != NULL && arg2_str == NULL)
            return remove_quantum(arg1_str);
        else
            error_flag = 1;
    }
    else if (strcmp(command, CMD_VALID) == 0)
    {
        if (arg1_str != NULL && arg2_str == NULL)
            return valid(arg1_str);
        else
            error_flag = 1;
    }
    else if (strcmp(command, CMD_ENERGY) == 0)
    {
        if (arg1_str != NULL)
        {
            if (arg2_str == NULL)
                energy_one_param(arg1_str);
            else
                energy_two_param_wrapper(arg1_str, arg2_str);
        }
        else
            error_flag = 1;
    }
    else
    {
        error_flag = 1;
    }

    if (error_flag)
        serr(ERROR_STRING);
}

void energy_two_param_wrapper(char *arg1_str, char *arg2_str)
{
    uint64_t energy = 0;

    if (arg2_str != NULL && '0' <= *arg2_str && *arg2_str <= '9')
        energy = strtoull(arg2_str, NULL, 10);

    energy_two_param(arg1_str, energy);
}

void initialize(char **buffer, size_t *buffer_size)
{
    *buffer_size = STARTING_BUFFER_SIZE;
    *buffer = malloc(*buffer_size * sizeof(char));

    quantum_initialize();
}

void cleanup(char **buffer, size_t *buffer_size)
{
    free(*buffer);
    *buffer = NULL;
    *buffer_size = 0;

    quantum_cleanup();
}

int main()
{
    size_t buffer_size;
    char *buffer;

    initialize(&buffer, &buffer_size);

    while (read_line(&buffer, &buffer_size))
    {
        process_line(buffer);
    }

    declare("0123\0");
    valid("0\0");
    valid("01\0");
    valid("012\0");
    valid("0123\0");
    valid("1\0");
    valid("01232\0");

    declare("0123210\0");
    valid("0123\0");
    valid("01232\0");
    valid("012321\0");
    valid("0123210\0");
    valid("01232101\0");

    declare("01\0");
    valid("0\0");
    valid("01\0");
    valid("012\0");
    valid("0123210\0");
    valid("01232101\0");

    remove_quantum("012321\0");
    valid("0\0");
    valid("01\0");
    valid("012\0");
    valid("0123\0");
    valid("01232\0");
    valid("012321\0");
    valid("0123210\0");
    valid("01232101\0");

    remove_quantum("01232101232\0");
    valid("0\0");
    valid("01232\0");
    valid("012321\0");

    energy_two_param_wrapper("0\0", "3");
    energy_two_param_wrapper("01\0", "6");
    energy_one_param("0\0");
    energy_one_param("01\0");

    equal("0\0", "01\0");
    energy_one_param("0\0");
    energy_one_param("01\0");

    equal("01\0", "012\0");
    energy_one_param("012\0");

    energy_two_param_wrapper("0\0", "7");
    energy_one_param("0\0");
    energy_one_param("01\0");
    energy_one_param("012\0");

    energy_two_param_wrapper("30\0", "30");

    equal("012\0", "33\0");
    equal("31\0", "32\0");

    valid("01232\0");
    valid("0123\0");
    energy_one_param("01232\0");
    energy_one_param("0123\0");
    equal("01232\0", "0123\0");

    cleanup(&buffer, &buffer_size);
    return 0;
}