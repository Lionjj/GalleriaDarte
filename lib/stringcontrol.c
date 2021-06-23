#include <stdbool.h>
#include <ctype.h>
#include "stringcontrol.h"
#include "../dataType/ArtShow/Artshow.h"
#include "datainput.h"
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

bool verifyemail(char str[]) {
    bool proposition = false, run = false;
    char *ptr = NULL;
    unsigned int i;

    for (i = 0; i < strlen(str); ++i) {
        if (str[i] == '@') {
            run = true;
            break;
        }
    }
    i++;
    while (str[i] != '\0' && run) {
        if (str[i] == '.') {
            if (isalpha(str[i - 1]) && isalpha(str[i + 1])) {
                proposition = true;
            } else {
                proposition = false;
                run = false;
            }
        }
        i++;
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

void stoupper(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = (char) toupper(str[i]);
    }
}

char *separateWithComma(unsigned int *arr, const unsigned int dim) {
    char *string = NULL;
    char strTemp[20];
    size_t i, j = 0, k;

    for (i = 0; i < dim; i++) {
        sprintf(strTemp, "%u", arr[i]);
        j += strlen(strTemp);
    }

    k = i + j;
    string = (char *) malloc(sizeof(char) * (k + 1));

    string[2 * dim] = '\0';
    j = 0;
    for (i = 0; i < dim; i++) {
        k = 0;
        sprintf(strTemp, "%u", arr[i]);
        while (strTemp[k] != '\0') {
            string[j] = strTemp[k];
            j++;
            k++;
        }
        string[j] = ',';
        j++;
    }

    return string;
}

char *reversStrtok(char *str, const char symbol) {
    char *ptr = NULL;
    unsigned int i = 0;

    while (str[i] != symbol) {
        i++;
    }
    i++;
    if (i != strlen(str)) {
        ptr = &str[i];
    }
    return ptr;
}

bool isSubStringExist(char *str, const char *subStr) {
    bool proposition = false;

    if (strstr(str, subStr) != NULL) {
        proposition = true;
    }

    return proposition;
}

unsigned int lineOfFile(FILE *file, const int MAX_LENG) {
    unsigned int l = 0;
    char str[MAX_LENG];
    while (fgets(str, MAX_LENG, file) != NULL) l++;
    return l;
}

unsigned int fgetIdsArtwork(const unsigned int idArtshow, unsigned int idsArtwork[]) {
    FILE *file = NULL;
    bool run = true;
    char str[MAX_LEN_SHOW], *ptr = NULL, *temp = NULL, *ids = NULL;
    unsigned int id, i = 0;

    if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stato possibile aprire il file per la verifica.");
    } else {
        while (run && fgets(str, MAX_LEN_SHOW, file) != NULL) {

            id = strtol(strtok(str, "#"), &ptr, 10);
            if (id == idArtshow) {
                run = false;
            }
        }

        ids = reversStrtok(reversStrtok(reversStrtok(reversStrtok(str, '/'), '#'), '/'), '#');

        temp = strtok(ids, ",");
        while (temp != NULL) {
            idsArtwork[i] = strtoul(temp, &ptr, 10);
            temp = strtok(NULL, ",");
            i++;
        }

        i--;
        fclose(file);
    }

    qsort(idsArtwork, i, sizeof(unsigned int), unsignedIntCompare);

    return i;
}