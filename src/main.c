#include "quantum_tree.h"
#include "quantum_functions.h"

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

/*
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

} */

/*
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
} */

//static node *tree_root = NULL;


int main()
{
    quantum_initialize();

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

    declare("111\0");
    energy_two_param("111\0", 10);
    declare("222\0");
    energy_two_param("222\0", 5);
    declare("333\0");
    energy_two_param("333\0", 60);
    declare("333123\0");
    energy_two_param("333123\0", 52);

    equal("111\0", "222\0");
    equal("111\0", "333\0");
    equal("111\0", "333123\0");

    energy_two_param("333123\0", 999);

    remove_quantum("333123\0");


    quantum_cleanup();
    return 0;
}