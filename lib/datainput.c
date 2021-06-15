#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"

// Funzione utilizzata per prendere come valore in input un intero
// representation: è la base di rappresentazione del numero (valori ammessi 0, 2<=x<=32)
int getInt(int representation) {
    int val;
    char str[11], *ptr;
    gets(str);

    val = strtol(str, &ptr, representation);

    free(ptr);
    return val;
}

unsigned int getUInt(int representation) {
    unsigned int val;
    char str[11], *ptr = NULL;
    gets(str);

    val = strtol(str, &ptr, representation);
    return val;
}

int getShort(int representation) {
    int val;
    char str[5], *ptr;
    gets(str);

    val = strtol(str, &ptr, representation);

    free(ptr);
    return val;
}

float getFloat( ) {
    float val;
    char str[13], *ptr;
    gets(str);

    val = strtof(str, &ptr);

    free(ptr);
    return val;
}

double getDouble( ) {
    double val;
    char str[13], *ptr;
    gets(str);

    val = strtod(str, &ptr);

    free(ptr);
    return val;
}