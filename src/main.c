#include "quantum_tree.h"
#include "quantum_functions.h"

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

    node **ptr = get_node_under_history("00\0", tree_root);
    dbg_print_node(*ptr);

    clear_tree(&tree_root);

    free(buf1);
    free(buf2);
    free(buf3);

    free(test_null_string);
    free(test_percentage);

    return 0;
}