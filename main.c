#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct QuantumNode_s;

typedef struct QuantumNode_s *Tree;

struct QuantumNode_s
{
    int id;
    Tree child_0, child_1, child_2, child_3;
} QuantumNode_default = {3, NULL, NULL, NULL, NULL};

typedef struct QuantumNode_s QuantumNode;


int isdigit(int);

void get_command(const char *begin, char *buf)
{
    int i = 0;
    while (*(begin + i) != '\0' && *(begin + i) != '\n' &&
    (('A' <= *(begin + i) && *(begin + i) <= 'Z') || *(begin + i) == ' ' ))
    {
        buf[i] = *(begin + i);
        i++;
    }
    buf[i] = '\0';
}

void get_parameter(const char *begin, char *buf) {
    int i = 0;
    while (isdigit(*(begin + i)) && '0' <= *(begin + i) && *(begin + i) <= '3') {
        printf("%d", *(begin + i) - '0');
        buf[i] = *(begin + i);
        i++;
    }


    if (*begin == '\n') {
        printf("\nZnaleziono koniec linii, wcześniejsze znaki to 0-3, argument jest poprawny\n");
//        return buf;
    } else {
        printf("\nNatrafiono na coś innego niż 0-3 przed nową linią, kończymy, przekazujemy pusty wskaźnik\n");
//        return NULL;
    }
}

int match_parameter(char *arg)
{

    if(arg == NULL)
        return -1;
    else if(strcmp(arg, "DECLARE \0") == 0)
        return 1;
    else if(strcmp(arg, "REMOVE \0") == 0)
        return 2;
    else if(strcmp(arg, "VALID \0") == 0)
        return 3;
    else if(strcmp(arg, "ENERGY \0") == 0)
        return 4;
    else if(strcmp(arg, "EQUAL \0") == 0)
        return 5;
    else
        return 0;
}

//void cmd_VALID ()

//TODO da się scalić?
//void cmd_ENERGY_1_arg
//void cmd_ENERGY_2_arg

//void cmd_DECLARE (char * history, Tree )

//void cmd_REMOVE

//void cmd EQUAL


int main()
{
    char line[1024];
    char *str = line;


    while (fgets(line, 1024, stdin))
    {
        //QuantumNode history = QuantumNode_default;

        if (str[0] == '\n' || str[0] == ' ' || str[0] == '#')
            continue;

        //TODO dynamic array
        char cmd[10];

        char *buf = cmd;
        char *ptr_at_arg = &line[0];
        assert(ptr_at_arg != NULL);

        get_command(ptr_at_arg, buf);

        puts(buf);

        switch (match_parameter(buf))
        {
            case 1:
//                cmd_DECLARE();
                printf("FOUND DECLARE COMMAND\n");
                break;
            case 2:
//                cmd_REMOVE();
                printf("FOUND REMOVE COMMAND\n");

                break;
//            TODO all functions
        }



        printf("\n");
    }


}