#include <stdio.h>
#include <string.h>
#include "../dataType/ArtShow/Artshow.h"
#include "datainput.h"
#include "../lib/search.h"
#include "../dataType/User/Users.h"

void research() {
    FILE *file = NULL;
    unsigned int choice;
    do {
        printf("\n\t>Scegliere criterio di ricerca:\n\t\t-1] Nome opera;\n\t\t-2] Autore opera;"
               "\n\t\t-3] Tipo opera;\n\t\t-4] Genere opera;\n\t\t-5] Periodo storico opera;"
               "\n\t\t-6] Anno produzione opera\n\t-");
        choice = getUInt(10);
        if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) ==
            NULL) {
            printf("\n\t-ATTENZIONE: non e' stata possibile effettuare l'operazione!");
        } else {
            switch (choice) {
                case 1:

                    printf("\n\t-Ricerca tramite nome\n");
                    searchName(file);
                    break;

                case 2:

                    printf("\n\t-Ricerca tramite autore\n");
                    searchArtAuthor(file);
                    break;

                case 3:

                    printf("\n\t-Ricerca tramite tipo di opera\n");
                    searchArtType(file);
                    break;

                case 4:

                    printf("\n\t-Ricerca tramite genere di opera\n");
                    searchArtKind(file);
                    break;

                case 5:

                    printf("\n\t-Ricerca tramite periodo storico\n");
                    searchArtHistorPeriod(file);
                    break;

                case 6:

                    printf("\n\t-Ricerca tramite anno di produzione\n");
                    searchArtProdYear(file);
                    break;

                default:
                    printf("\n\t-Azione di ricerca interrotta!\n");
                    break;
            }
            fclose(file);
        }
    } while (choice < 1 || choice > 6);
}

void searchName(FILE *file) {
    char name[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire nome da ricercare\n\t-");
    gets(name);
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (strstr(artwork.name, name) != 0) {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtAuthor(FILE *file) {
    char authorName[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire il nome, il cognome o nome e cognome dell'autore\n\t-");
    gets(authorName);
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (strcmp(artwork.authorName, authorName) == 0) {
            num++;
            printArtwork(num, &artwork);
        } else {
            if (strcmp(artwork.authorSurname, authorName) == 0) {
                num++;
                printArtwork(num, &artwork);
            }
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtType(FILE *file) {
    char str[MAX_LEN];
    unsigned int artType;
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire un tipo tra i disponibili:\n\t\t-0] Dipinto;\n\t\t-1] Scultura;\n\t\t-2] Disegno;\n\t-");
    artType = getUInt(10);
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (artwork.operaType == artType) {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtKind(FILE *file) {
    char artKind[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire genere\n\t-");
    gets(artKind);
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (strstr(artwork.kind, artKind) != 0) {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtHistorPeriod(FILE *file) {
    char artHistorPeriod[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo storico (a lettere)\n\t-");
    gets(artHistorPeriod);
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (strstr(artwork.historPeriod, artHistorPeriod) != 0) {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtProdYear(FILE *file) {
    char str[MAX_LEN];
    int min, max, c;
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo di produzione");
    printf("\n\t>Primo anno:\n\t-");
    min = getInt(10);
    printf("\n\t>Secondo anno:\n\t-");
    max = getInt(10);
    if (min > max) {
        c = min;
        min = max;
        max = c;
    }
    while (fgets(str, MAX_LEN, file) != NULL) {
        loadArtwork(str, &artwork);
        if (artwork.prodYear >= min && artwork.prodYear <= max) {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}