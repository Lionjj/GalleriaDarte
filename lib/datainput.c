#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"

int getInt(int representation) {
    int val;
    char str[11], *ptr = NULL;
    gets(str);

    val = strtol(str, &ptr, representation);

    free(ptr);
    return val;
}

unsigned int getUInt(int representation) {
    unsigned int val;
    char str[11], *ptr = NULL;
    gets(str);

    val = strtoul(str, &ptr, representation);
    return val;
}

int intCompare(const void *p1, const void *p2) {
    int int_a = *((int *) p1);
    int int_b = *((int *) p2);

    if (int_a == int_b) { return 0; }
    else if (int_a < int_b) { return -1; }
    else { return 1; }
}