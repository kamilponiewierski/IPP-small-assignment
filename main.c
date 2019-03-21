#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#define CHILDREN_COUNT 4

struct node;

typedef struct node *Tree;

struct node
{
    uint64_t energy;
    struct node *next;
    struct node *prev;
    int valid;
    Tree children[CHILDREN_COUNT];
};

void initNode(struct node *n)
{
    struct node temp;
    temp.energy = 0;
    //do FU, trzeba zamienic sobie, petla wskaznikow, wlaczanie miedzy dwa
    temp.prev = &temp;
    temp.next = &temp;
    temp.valid = 0;

    for(int i = 0; i < CHILDREN_COUNT; i++)
    {
        temp.children[i] = NULL;
    }

    *n = temp;
}

struct node* getNode()
{
    struct node* ptr = (struct node*) malloc(sizeof(struct node));
    initNode(ptr);
    return ptr;
}

void printNode(struct node *n)
{
    if (n == NULL)
    {
        printf("node is null, error\n");
        return;
    }

    printf("Energy = %" PRId64 "\n", n->energy);
    printf("Valid = %d\n", n->valid);
    printf("Nulls: ");
    for(int i = 0; i < CHILDREN_COUNT; i++)
    {
        if(n->children[i] == NULL)
        {
            printf("%d, ", i);
        }
    }
    printf("\n");
}


int isdigit(int);

void get_command(const char *begin, char *buf) //TODO rewrite
{
    int i = 0;
    while (*(begin + i) != '\0' && *(begin + i) != '\n' &&
    (('A' <= *(begin + i) && *(begin + i) <= 'Z') || *(begin + i) == ' ' ))
    {
        if(i > 1 && *(buf - 1) == ' ' && *buf == ' ')
        {
            break;
        }
        *(buf + i) = *(begin + i);
        i++;
    }


    *(buf + i) = '\0';
}

void get_parameter(const char *begin, char *buf) //TODO rewrite
{
    int i = 0;
    while (*(begin + i) != '\0' && *(begin + i) != '\n' && *(begin + i) != ' ' &&
           (('0' <= *(begin + i) && *(begin + i) <= '3')))
    {
        *(buf + i) = *(begin + i);
        i++;
    }
    *(buf + i) = '\0';
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


int main()
{
    struct node *quantumPtr, quantum;
    quantumPtr = &quantum;

//    printf("%"PRId64 "\n", sizeof(struct node));

//    printf("%d\n", sizeof(struct node));



    initNode(quantumPtr);
    quantumPtr->valid = -1;

    quantumPtr->children[0] = getNode();
    quantumPtr->children[0]->energy = 5;
    quantumPtr->children[0]->children[1] = getNode();
    quantumPtr->children[0]->children[1]->children[3] = getNode();
    quantumPtr->children[0]->children[1]->children[3]->energy = 42;

    char *buf;
    buf = (char*) malloc(4 * sizeof(char));
    buf[0] = '0';
    buf[1] = '1';
    buf[2] = '3';
    buf[3] = ' ';

    char *buf2;
    buf2 = (char*) malloc (3 * sizeof(char));
    buf2[0] = '0';
    buf2[1] = '1';
    buf2[2] = ' ';

//    VALID(quantumPtr, buf);
//    DECLARE(quantumPtr, buf);
//    VALID(quantumPtr, buf);
//    ENERGY(quantumPtr, buf);
//    ENERGY(quantumPtr, buf2);
//    printf("%d\n", quantumPtr->child_0->child_1->valid);
//    REMOVE(quantumPtr, buf2);
//    printf("%d\n", quantumPtr->child_0->child_1->valid);

    printNode(quantumPtr->children[0]->children[1]);
    quantumPtr->children[0]->children[0]->children[3]->valid = 1;
//    VALID(quantumPtr, buf2);
//    VALID(quantumPtr, buf2);


    return 0;
}

//
//int main()
//{
//    char line[1024];
//    char *str = line;
//
//    //declare structure
//
//    while (fgets(line, 1024, stdin))
//    {
//        if (str[0] == '\n' || str[0] == ' ' || str[0] == '#')
//            continue;
//
//        //find places to look for arguments of functions, -1 means it was not found, -2 means the line is invalid
//        int first_space = -1;
//        int *ptr_first_space = &first_space;
//        int second_space = -1;
//        int *ptr_second_space = &second_space;
//        char *ptr_line_0 = &line[0];
//
//        look_for_spaces(ptr_first_space, ptr_second_space, ptr_line_0, sizeof(line) / sizeof(line[0]));
////        printf("%d, %d the end\n", first_space, second_space);
//
//        if(second_space == -2)
//            continue;
//
//        char *first_param;
//        first_param = (char*) malloc(100 * sizeof(char)); //TODO change size
//
//        //TODO dynamic array
//        char cmd[10];
//
//        char *buf;
//        buf = (char*) malloc(sizeof(char));
//        buf = &cmd[0];
//        assert(buf != NULL);
//        char *ptr_at_arg = &line[0];
//        assert(ptr_at_arg != NULL);
//
//
//        get_command(ptr_at_arg, buf);
////        for (int i = 0; i < 10; i++)
////        {
////            printf("%c", cmd[i]);
////        }
////        printf("\n");
//
//        char param_1[100];
//        char *ptr_param_1 = &param_1[0];
//        char *ptr_param_1_begin = &line[first_space + 1];
//        get_parameter(ptr_param_1_begin, ptr_param_1);
////        for (int i = 0; i < 100 && param_1[i] != '\0'; i++)
////        {
////            printf("%c", param_1[i]);
////        }
////        printf("\n");
//
//
//        //puts(buf);
//
//        switch (match_parameter(buf))
//        {
//            case 1:
////                cmd_DECLARE();
////                printf("FOUND DECLARE COMMAND\n");
//                break;
//            case 2:
////                cmd_REMOVE();
////                printf("FOUND REMOVE COMMAND\n");
//                break;
//            case 3:
////                cmd_VALID();
//                break;
//            case 4:
////                cmd_ENERGY();
//                break;
//            case 5:
////                cmd_EQUAL();
//                break;
//            default:
//                break;
//        }
//
//
//
//        printf("\n");
//    }
//
//
//}