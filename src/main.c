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



int main()
{
    node *tree_root = create_root();
    if (tree_root == NULL)
    {
        return EXIT_FAILURE;
    }

    char *buf1 = strdup("0012\0");
    char *buf2 = strdup("012311\0");
    char *buf3 = strdup("1231210\0");

    char *test_null_string = strdup("\0");
    char *test_percentage = strdup("\\ %d\0");

    assert(check_input_history("01123211232\0") == true);
    assert(check_input_history("%d121aadds\0") == false);
    assert(check_input_history("unsigned long\0") == false);
    assert(check_input_history("0\0") == true);

    declare(test_null_string, tree_root);
    declare(test_percentage, tree_root);


    declare(buf1, tree_root);
    valid(buf1, tree_root);
    energy_two_param("0012\0", 12312343, tree_root);
    energy_one_param(buf1, tree_root);

    node **ptr = get_node_under_history("0012\0", tree_root);

    if (ptr != NULL)
        dbg_print_node(*ptr);

    clear_tree(&tree_root);

    free(buf1);
    free(buf2);
    free(buf3);

    free(test_null_string);
    free(test_percentage);

    return 0;
}