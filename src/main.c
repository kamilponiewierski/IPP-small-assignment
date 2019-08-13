#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#include "quantum_tree.h"

#define CHILDREN_COUNT 4
#define MAXIMUM_VALID_ENERGY_DIGITS 20


int isdigit(int);

int valid_string(const char *c)
{
    int i = 0;
    int valid_string = 1;

    while (*(c + i) != '\n')
    {
        if (*(c + i) < '0' || '3' < *(c + i))
        {
            valid_string = 0;
        }
        i++;
    }

    return valid_string;
}

void VALID(node *n, char *c)
{
    if (n->valid == 1)
    {
        printf("YES\n");
        return;
    } else if (*c == '\n') //end of parameter, none of prefixes was valid
    {
        printf("NO\n");
    } else if ('0' <= *c && *c <= '3')
    {
        int index = *c - '0';
        if (n->children[index] != NULL)
        {
            c++;
            VALID(n->children[index], c);
        }
    } else
    {
//        fprintf( stderr, "ERROR\n");
        printf("ERROR\n");
        return;
    }
}

uint64_t get_energy(const char *c)
{
    uint64_t energy = 0;
    int meaningful_digits = 0;
    int leading_zero_flag = 1;
    int i = 0;
    while ('0' <= *(c + i) && *(c + i) <= '9')
    {
        if (*(c + 1) != '0')
        {
            leading_zero_flag = 0;
        }

        if (leading_zero_flag == 0)
        {
            meaningful_digits++;
        }

        if (meaningful_digits > MAXIMUM_VALID_ENERGY_DIGITS)
        {
            //the number would be too be too big to contain in uint64_t, fun will return 0 as an error
            energy = 0;
            break;
        }

        energy = energy * 10 + (*(c + i) - '0');
        i++;
    }

    //no newline means that the argument is incorrect, fun will return 0 as an error
    if (*(c + i) != '\n')
    {
        energy = 0;
    }

    return energy;
}

void ENERGY(node *n, char *c)
{
    if (*c == '\n' && n->energy != 0 && n->valid == 1)
    {
        printf("%"PRId64 "\n", n->energy);
    } else if (*c == ' ')
    {
        if (n->valid != 1)
        {
            printf("ERROR\n");
            return;
        } else
        {
            c++;
            uint64_t energy_to_set = get_energy(c);

            if (energy_to_set == 0)
                printf("ERROR\n");
            else
            {
                n->energy = energy_to_set;
                printf("OK\n");
            }
            return;
        }
    } else if ('0' <= *c && *c <= '3')
    {
        int index = *c - '0';
        if (n->children[index] != NULL)
        {
            c++;
            ENERGY(n->children[index], c);
        }
    } else
    {
//        fprintf( stderr, "ERROR\n");
        printf("ERROR\n");
    }
}

void DECLARE(node *n, char *c)
{
    if (!valid_string(c))
    {
        printf("ERROR\n");
        return;
    }

    if (n->valid != -1)
        n->valid = 1;
    if (*c == '\n')
    {
        printf("OK\n");
    } else if ('0' <= *c && *c <= '3')
    {
        int index = *c - '0';
        if (n->children[index] == NULL)
            n->children[index] = get_node();
        c++;
        DECLARE(n->children[index], c);
    } else
    {
//        fprintf( stderr, "ERROR\n");
        printf("ERROR\n");
    }
}

/*void set_energy_to_abs_class (struct Node *abs_class, uint64_t set_energy)
{
    //abs class is circular, this guarantees that the loop ends
    abs_class->energy = set_energy;
    struct Node **ptr;
    ptr = (struct Node**) malloc(sizeof(struct Node *));
    if(ptr == NULL)
    {
        printf("EMPTY POINTER");
    }
    ptr = &(abs_class->next);


    int i = 0;

    printf("Before while\n");
    while((*ptr) != abs_class)
    {
        printf("in a loop...\n");
        printf("Memory address of *ptr is %p\n", &*ptr);
        printf("Memory address of *ptr->next is %p\n", &(*ptr)->next);
        printf("Memory address of abs_class is %p\n", &abs_class);
        print_node(*ptr);
        printf("\n\n");
        (*ptr)->energy = set_energy;

        ptr = &((*ptr)->next);



        if (i > 2)
            break;

        i++;
    }
    free(ptr);
}*/

void add_single_node_to_abs_class(node *abs_class, node *n, uint64_t energy)
{
    if (n->valid != 1)
    {
        printf("adding a node to abs class failed, node is not valid\n");
        return;
    }

    abs_class->energy = energy;
    n->energy = energy;

    printf("%p %p\n", &(*(n->next)), &(*(n->prev)));

    n->next = abs_class;
    n->prev = abs_class->prev;

    printf("%p %p\n", &(*(n->next)), &(*(n->prev)));

    abs_class->prev->next = n;
    abs_class->prev = n;

}

void EQUAL(node *a, node *b)
{
    if (a->energy != 0 && b->energy == 0 && a->valid == 1 && b->valid == 1)
    {
        uint64_t abs_class_energy = a->energy;
        b->energy = abs_class_energy;

        //struct Node **b_abs_class;
        //b_abs_class = malloc(8 * sizeof(struct Node*));

        while (&*b != &*b->next)
        {
            printf("relinking...");
            //re-linking of abstraction class
            b->next->next->prev = b;
            node *ptr = b->next;
            b->next = ptr->next;

            add_single_node_to_abs_class(a, ptr, abs_class_energy);
        }


        add_single_node_to_abs_class(a, b, abs_class_energy);

        return;
    } else if (a->energy == 0 && b->energy != 0)
    {
        EQUAL(b, a);
        return;
    } else if (a->energy != 0 && b->energy != 0)
    {

    }
}


int main()
{
    node *node_test = get_node();
    if (node_test == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("%d\n", can_be_deleted(node_test));

    assert(node_test->energy == 0);

    add_child(node_test, 0);
    add_child(node_test, 0);
    add_child(node_test->children[0], 1);

    dbg_print_node(node_test);

    printf("%d\n", can_be_deleted(node_test));
    printf("%d\n", can_be_deleted(node_test->children[0]));
    printf("%d\n", can_be_deleted(node_test->children[0]->children[1]));

    delete_children(node_test);
    dbg_print_node(node_test);

    free(node_test);

    //TODO dynamic input array
    //TODO REMOVE
    //TODO MEMORY FREEING
    //TODO EQUAL

    return 0;
}