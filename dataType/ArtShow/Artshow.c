#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Artshow.h"
#include "../../lib/stringcontrol.h"

#define MAX_LEN 415

void getExhiPlace(exhiPlace *place) {
    printf("\n# Registra luogo esposizione #\n-Inserisci:");

    getStreet(place);

    getHouseNum(place);

    getCity(place);

    getNameStructure(place);
}

bool isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN) {
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN], *fGalCity, *fGalStreet, *fGalHouseN;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\ArtGalleryManager.txt",
                      "r")) == NULL) {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        while (fgets(str, MAX_LEN, file) != NULL && proposition == false) {
            strtok(str, "|");

            fGalCity = strtok(NULL, "#");
            fGalStreet = strtok(NULL, "#");
            fGalHouseN = strtok(NULL, "#");

            if (strcmp(fGalCity, galCity) == 0) {
                if (strcmp(fGalStreet, galStreet) == 0) {
                    if (strcmp(fGalHouseN, galHouseN) == 0) {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: il luogo specificato e' gia' occupato da un'altra galleria!");
                    }
                }
            }
        }
        fclose(file);

        free(fGalHouseN);
        free(fGalStreet);
        free(fGalCity);
    }
    return proposition;
}

void loadGallery(char str[], exhiPlace *place) {
    char *fStreetName = NULL, *fHouseNum = NULL, *fCity = NULL, *fStructure = NULL;

    fCity = strtok(str, "#");
    fStreetName = strtok(NULL, "#");
    fHouseNum = strtok(NULL, "#");
    fStructure = strtok(NULL, "-");

    delatenoalpha(fCity);

    strcpy(place->city, fCity);
    strcpy(place->streetName, fStreetName);
    strcpy(place->houseNum, fHouseNum);
    strcpy(place->structure, fStructure);
}

void getStreet(exhiPlace *place) {
    char str[90];
    int i = 0;

    printf("\n\t>Via/piazza (Il nome della via/piazza non deve contenere numeri, e non deve superare i 90 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: La via/piazza inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 90);

    strcpy(place->streetName, str);
}

void getHouseNum(exhiPlace *place) {
    char str[5];
    int i = 0;
    printf("\n\t>Numero civico (Il numero civico deve contenere esclusivamente numeri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il numero inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisdigit(str));

    strcpy(place->houseNum, str);
}

void getCity(exhiPlace *place) {
    char str[30];
    int i = 0;
    printf("\n\t>Citta (Il nome della citta non deve contenere numeri e non deve superare i 30 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il nome della citta inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    strcpy(place->city, str);
}

void getNameStructure(exhiPlace *place) {
    char str[50];
    int i = 0;
    printf("\n\t>Nome della struttura (Il nome della stru. non deve contenere numeri e non deve superare i 50 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il numero inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 50);

    strcpy(place->structure, str);
}

//loadExhiplace