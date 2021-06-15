#include <stdbool.h>
#include <ctype.h>
#include "stringcontrol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool sisalpha(char *str) {
    bool proposition;
    unsigned int i = 0;

    while (str[i] != '\0') {
        proposition = (bool) isalpha(str[i]);
        i++;
    }

    return proposition;
}

bool sisdigit(char *str) {
    bool proposition;
    unsigned int i = 0;

    while (str[i] != '\0') {
        proposition = (bool) isdigit(str[i]);
        i++;
    }

    return proposition;
}

bool sisalnum(char str[]) {
    bool proposition;
    unsigned int i = 0;

    while (str[i] != '\0') {
        proposition = (bool) isalnum(str[i]);
        i++;
    }

    return proposition;
}

bool shaveanumber(char str[]) {
    bool proposition = false;
    unsigned int i = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            proposition = true;
            break;
        } else { i++; }
    }
    return proposition;
}

bool shaveaspecial(char str[]) {
    bool proposition = false;
    unsigned int i = 0;

    while (str[i] != '\0') {
        // inserie la funzione per verificre se il singolo carattere è un carattere speciale
        if ((str[i])) {
            proposition = true;
            break;
        } else { i++; }
    }
    return proposition;
}

bool verifyemail(char str[]) {
    bool proposition = false;
    char *ptr = NULL;

    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '@') {
            proposition = true;
            break;
        }
    }

    free(ptr);
    return proposition;
}

bool sisspace(char str[]) {
    bool proposition = false;
    unsigned int i = 0;

    while (str[i] != '\0') {
        if (isspace(str[i])) {
            proposition = true;
            break;
        } else { i++; }
    }
    return proposition;
}

void deletespaces(char str[]) {
    int i = 0, j = 1;
    char *formattedString = NULL;

    if (sisspace(str)) {
        while (str[i] != '\0') {
            if (!isspace(str[i])) {
                j++;
            }
            i++;
        }

        formattedString = (char *) malloc(sizeof(char) * j);

        i = 0;
        while (str[i] != '\0') {
            if (!isspace(str[i])) {

                formattedString[i] = str[i];
            }
            i++;
        }


        strcpy(str, formattedString);
        free(formattedString);
    }
}

void stoupper(char str[]){
    for (int i = 0; i < strlen(str); i++){
        str[i] = (char) toupper(str[i]);
    }
}

char* separateWithComma(unsigned int* arr, const unsigned int dim){
    char* string = NULL;
    char strTemp[20];
    size_t i, j = 0, k;

    for (i = 0; i < dim; i++){
        itoa((int) arr[i], strTemp, 10);
        j += strlen(strTemp);
    }


    k = i + j;
    string = (char*) malloc(sizeof(char) * k);

    j = 0;
    for (i = 0; i < dim; i++){
        k = 0;
        itoa((int)arr[i], strTemp, 10);
        while (strTemp[k] != '\0'){
            string[j] = strTemp[k];
            j++;
            k++;
        }
        string[j] = ',';
        j++;
    }

    string[j] = '\0';
    return string;
}