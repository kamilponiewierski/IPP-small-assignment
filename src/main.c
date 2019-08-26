#include "quantum_tree.h"
#include "quantum_functions.h"

int main()
{
    quantum_initialize();

    node **tmp = get_node_under_history("\0");

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
    declare("222\0");
    declare("333\0");
    declare("333123\0");

    energy_two_param("111\0", 3);
    energy_two_param("333\0", 63);
    energy_two_param("333123\0", 52);

    equal("111\0", "222\0");
    energy_one_param("111\0");
    energy_one_param("222\0");
    equal("111\0", "333\0");
    energy_one_param("111\0");
    energy_one_param("333123\0");
    equal("111\0", "333123\0");
    energy_one_param("333123\0");
    energy_one_param("222\0");

    energy_two_param("333123\0", 999);

    remove_quantum("333123\0");


    quantum_cleanup();
    return 0;
}