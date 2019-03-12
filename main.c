#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct QuantumNode_s;

typedef struct QuantumNode_s *Tree;

struct QuantumNode_s {
    int id;
    Tree child_0, child_1, child_2, child_3;


} QuantumNode_default = {3, NULL, NULL, NULL, NULL};

typedef struct QuantumNode_s QuantumNode;

#define N_ELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#define typename(x) _Generic((x),                                                 \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other")


int isdigit(int);

void get_command(const char *begin, char *buf) {
    int i = 0;
    while (*(begin + i) != '\0' && *(begin + i) != '\n' && 'A' <= *(begin + i) && *(begin + i) <= 'Z') {

        i++;
    }
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

//void cmd_VALID ()

//TODO da się scalić?
//void cmd_ENERGY_1_arg
//void cmd_ENERGY_2_arg

//void cmd_DECLARE (char * history, Tree )

//void cmd_REMOVE

//void cmd EQUAL


int main() {
    char line[1024];
    typename(line);
    char *str = line;


    while (fgets(line, 1024, stdin)) {
        QuantumNode history = QuantumNode_default;
        if (str[0] == '\n' || str[0] == ' ' || str[0] == '#')
            continue;

        char *ptr_at_arg = &line[0];
        assert(ptr_at_arg != NULL);
//      TODO poprawka ustawiania wskaźnika
        while (*ptr_at_arg != '\n' && *ptr_at_arg != ' ') {
            printf("%c", *ptr_at_arg);
//            printf("address of ptr_at_arg in decimal is %lld\n", (long long) (__intptr_t) (&ptr_at_arg));
            ptr_at_arg++;
        }


        char *buf = (char *) malloc(32 * sizeof(char));

        //TODO dynamiczna tablica
        char tab[100];

        buf = tab;
        assert(buf != NULL);

        get_parameter(ptr_at_arg, buf);

        for (int i = 0; buf[i] != '\0'; i++) {
            printf("%c", buf[i]);
        }

//        free(buf);
//        free(ptr_at_arg);

//        blok sprawdzenia polecenia
//        char check_valid[7];
//        memcpy(&check_valid, &line[0], 6 * sizeof(char));
//        check_valid[6] = '\0';
//        puts(check_valid);
//
//        if(strcmp(check_valid, "VALID \0") == 0)
//        {
//            printf("POLECENIE VALID\n");


//      passing argument when input starts with "VALID "







//
//
//        for (int i = 0; i < 6; i++)
//        {
//            printf("%d\n", i);
//            printf("%c", check_valid[i]);
//        }
//        printf("\n");
//
//        printf("testOK\n");


    }


}