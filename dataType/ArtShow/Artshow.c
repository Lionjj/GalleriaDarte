#include <stddef.h>
#include <stdio.h>

#include <stdlib.h>
#include "Artshow.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "../User/Users.h"
#include "../../lib/search.h"
#include "../Users/Client.h"
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define MAX_LEN_MANAGER 415

void getStreet(char *streetName) {
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

    strcpy(streetName, str);
}

void getHouseNum(char *houseNum) {
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

    strcpy(houseNum, str);
}

void getCity(char *city) {
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

    strcpy(city, str);
}

void getNameStructure(char *structure) {
    char str[50];
    int i = 0;
    printf("\n\t>Nome della struttura (Il nome della stru. non deve contenere numeri e non deve superare i 50 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il nome della struttura inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 50);

    strcpy(structure, str);
}

void getExhiPlace(exhiPlace *place) {
    printf("\n# Registra sede galleria #\n-Inserisci:");

    getStreet(place->streetName);

    getHouseNum(place->houseNum);

    getCity(place->city);

    getNameStructure(place->structure);
}

void loadGallery(char str[], exhiPlace *place) {
    char *fStreetName = NULL, *fHouseNum = NULL, *fCity = NULL, *fStructure = NULL;

    fCity = strtok(str, "<");
    fStreetName = strtok(NULL, "<");
    fHouseNum = strtok(NULL, "<");
    fStructure = strtok(NULL, "-");

    strcpy(place->city, fCity);
    strcpy(place->streetName, fStreetName);
    strcpy(place->houseNum, fHouseNum);
    strcpy(place->structure, fStructure);
}

bool isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN) {
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_MANAGER], *fGalCity, *fGalStreet, *fGalHouseN;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\ArtGalleryManager.txt",
                      "r")) == NULL) {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        /*
        * Questo ciclo di controlli, continua fintato che, non è terminato il file, oppure termina se e solo se la
        * variabile proposition, che rappresenta il risultato finale del triplice controllo, è posta a true, ossia
        * esiste una galleria già registrata nel file ArtGalleryManager.txt con il medesimo indirizzo della galleria,
        * i cui valori sono stati passati alla funzione.
        */
        while (fgets(str, MAX_LEN_MANAGER, file) != NULL && proposition == false) {

            // recupera dal file ArtGalleryManager.txt tre sottostringhe: fGalCity, fGalStreet, fGalHouseN
            fGalCity = strtok(str, "<");
            fGalStreet = strtok(NULL, "<");
            fGalHouseN = strtok(NULL, "<");



            /* solo nel caso in cui, due sedi della galleria, si trovino nella stessa città bisonga verificare se si
             * trovino nella stessa via è in tale caso verificare anche se il numero civico è lo stesso.
             */

            //se le due sedi si trovano nella stessa citta
            if (strcmp(fGalCity, galCity) == 0) {
                // se si trovano nella stessa via
                if (strcmp(fGalStreet, galStreet) == 0) {
                    // se si trovano allo stesso numero
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

void getCurrentDate(date *d) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    d->day = tm.tm_mday;
    d->month = tm.tm_mon + 1;
    d->year = tm.tm_year + 1900;
}

void getYear(date *time, const unsigned int current) {
    unsigned int t;
    int i = 0;

    printf("\n\t>Anno (L'anno deve essere maggiore o uguale a quello corrente):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: L'anno inserito non e' conforme con le specifiche richieste, riprova:");
        }
        t = getUInt(10);
        i++;
    } while (t < current);

    time->year = t;
}

void getMonth(date *time, date *current) {
    unsigned int t;
    int i = 0;

    printf("\n\t>Mese (Il mese deve essere maggiore o uguale a quello corrente):");
    do {
        if (i != 0) {
            if (current->month > t && current->year == time->year) {
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12 e "
                       "\n\tdeve essere maggiore o guale a %u, riprova:", current->month);
            } else {
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12, riprova:");
            }
        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > 12) || (current->month > t && current->year == time->year));
    time->month = t;
}

void getDay(date *time, date *current) {
    unsigned int t, lim;
    int i = 0;

    /*
     * verifica innanzituto il lim che corrisponde al numero massimo, rappresentante il giorno,
     * rispetto al mese specificato dal puntatore time->month. Nel caso in cui il mese è di 30 giorni allora la
     * variabile lim connterrà il valore 30 e così via per gli altri mesi.
     */
    if (time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11) {
        lim = 30;

        /*
         * Nel caso il mese corrisponde a febbraio, si verifica se l'anno, specificato dal puntatore time->year sia
         * bisestile attraverso la funzione isLeapYear(unsigned int year) che data un'annata verifica se essa è bisestile.
         * Nel caso l'anno sia bisestile allora lim conterrà il valore 29, altrimenti il valore 28.
         */
    } else if (time->month == 2) {
        if (isLeapYear(time->year)) {
            lim = 29;
        } else {
            lim = 28;
        }
    } else {
        lim = 31;
    }

    printf("\n\t>Giorno (il giorno deve essere maggiore o uguale a quello corrente):");
    do {
        if (i != 0) {
            if (t < current->day && current->month == time->month && current->year == time->year) {
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d e"
                       "\n\tdeve essere maggiore o guale a %u, riprova:", lim, current->day);
            } else {
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d, riprova:", lim);
            }
        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > lim) || (t < current->day && current->month == time->month && current->year == time->year));

    time->day = t;
}

void getDate(date *time) {
    date current;
    getCurrentDate(&current);

    printf("\n-Inserisci:");
    getYear(time, current.year);
    getMonth(time, &current);
    getDay(time, &current);
}

void getExpositionTime(date *timeStart, date *timeEnd) {
    int i = 0;
    bool isTemp = false;

    printf("\n>E' una mostra temporanea?(s/n)\n\t-");
    if (toupper(getch()) == 'S') {
        isTemp = true;
    }
    getch();

    printf("\n- Inizio data esposizione -");
    getDate(timeStart);

    if (isTemp) {
        printf("\n- Fine data esposizione -");
        do {
            if (i > 0) {
                printf("\n\t-ATTENZIONE: La data di conclusione della mostra non deve essere precedente "
                       "alla data di inzio, riprova.");
            }
            getDate(timeEnd);
            i++;
            // la data timeEnd non deve precedere la data di partenza della mostra.
        } while (!isPrevious(timeStart, timeEnd));

    } else {
        timeEnd->day = 0;
        timeEnd->month = 0;
        timeEnd->year = 0;
    }
}

void fgetDateEnd(date *timeEnd, const unsigned int id) {
    FILE *file = NULL;
    char artShow[MAX_LEN_SHOW], *date = NULL, *ptr = NULL;
    unsigned int fid;
    bool run = true;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");
    } else {

        while (fgets(artShow, MAX_LEN_SHOW, file) != NULL && run) {
            fid = strtol(strtok(artShow, "#"), &ptr, 10);

            if (id == fid) {
                strtok(NULL, "#");
                strtok(NULL, "#");
                strtok(NULL, "#");

                date = strtok(NULL, "#");

                timeEnd->day = strtol(strtok(date, "/"), &ptr, 10);
                timeEnd->month = strtol(strtok(NULL, "/"), &ptr, 10);
                timeEnd->year = strtol(strtok(NULL, "/"), &ptr, 10);
                run = false;
            }
        }
        fclose(file);
    }
}

void listenerTimeExpired() {
    FILE *file = NULL;
    unsigned int len = 0;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");
    } else {
        len = lineOfFile(file, MAX_LEN_SHOW);

        fclose(file);
    }
    for (int i = 0; i < len; ++i) {
        // se l'i-esima mostra è terminata
        if (isShowOver(i)) {
            // eliminala
            delateArtshow(i);
        }
    }
}

bool isLeapYear(unsigned int year) {
    bool proposition = false;

    if (year % 400 == 0) {
        proposition = true;
    } else {
        if ((year % 4 == 0) && !(year % 100 == 0)) {
            proposition = true;
        }
    }

    return proposition;
}

bool isPrevious(date *timeStart, date *timeEnd) {
    bool proposition = false;

    // Nel caso sia una mostra temporanea procedi
    if (timeStart->day != 0) {
        if (timeStart->year < timeEnd->year) {
            proposition = true;
        } else if (timeStart->year == timeEnd->year) {
            if (timeStart->month < timeEnd->month) {
                proposition = true;
            } else if (timeStart->month == timeEnd->month) {
                if (timeStart->day <= timeEnd->day) {
                    proposition = true;
                }
            }
        }
    }

    return proposition;
}

void getFiscalCode(char *fiscalCode) {
    char str[17];
    int i = 0;
    printf("\n\t>Codice fiscale (Il codice fisc. deve contenere solo numeri e lettere):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il codice fiscale non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) != 16);
    stoupper(str);
    strcpy(fiscalCode, str);
}

void getLocalManager(localManager *manager) {
    printf("\n- Registrazione del manager locale -\n-Inserisci:");
    getName(manager->name);
    getSurname(manager->surname);
    getFiscalCode(manager->fiscalCode);
}

unsigned int getIdArtwork() {
    FILE *file = NULL;
    size_t id = 0;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {
        // Dato che gli identificativi di ogni opera corrispondono con il numero di righe del file, basterà contare
        // il numero di righe per ottenere il nuovo idetificativo
        id = lineOfFile(file, MAX_LEN_ARTWORK);
        fclose(file);
    }

    return id;
}

void getArtworkName(char *artworkName) {
    char str[100];
    int i = 0;
    printf("\n\t>Nome opera d'arte (Il nome dell'opera deve contenere esclusivamente\n\tlettere e non puo' superare i 100 caratteri):\n\t-");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il nome dell'opera non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 100);

    strcpy(artworkName, str);
}

enum operaType getOperaType() {
    enum operaType opType;
    bool run = true;
    unsigned int choice;

    do {
        printf("\n-Premi:\n\t\t-1] Dipinto;\n\t\t-2] Scultura;\n\t\t-3] Disegno;\n\t-");
        choice = getUInt(10);

        switch (choice) {
            case 1:
                opType = painting;
                run = false;
                break;
            case 2:
                opType = sculpture;
                run = false;
                break;
            case 3:
                opType = drawing;
                run = false;
                break;
            default:
                break;
        }
    } while (run);

    return opType;
}

void getKind(char *kind) {
    char str[30];
    int i = 0;
    printf("\n\t>Genere opera (Il genere dell'opera deve contenere solo lette e non puo' superare i 30 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il genere dell'opera non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    strcpy(kind, str);
}

void getHistorPeriod(char *historPeriod) {
    char str[30];
    int i = 0;
    printf("\n\t>Periodo storico (Il periodo storico deve contenere solo lettere e deve essere al massimo di 30 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il perido storico non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    strcpy(historPeriod, str);
}

bool isBC() {
    bool proposition = false;
    printf("\n\t>Si tratta di un opera avanti cristo? (s/n):\n\t-");

    if (toupper(getch()) == 'S') {
        proposition = true;
    }
    getch();
    return proposition;
}

unsigned int getProdYear(bool BC) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    unsigned int currentY = tm.tm_year + 1900;
    unsigned int year, i = 0;

    printf("\n\t>Anno di prosuzione (L'anno non deve essere superiore a quello corrente, se l'opera e D.C.\n\t "
           "Altrimenti se e' A.C. non puo superare l'anno 40.000):\n\t-");

    do {

        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il perido storico non e' conforme con le specifiche richieste, riprova:");
        }

        year = getUInt(10);
        i++;

        // Se l'anno di porduzione non è A.C., verifica se l'anno inserito è maggiore di quello corrente
        // oppure se l'opera è A.C. verifica se è maggiore della prima opera scoperta
    } while ((!BC && year > currentY) || (BC && year > 40000));
    return year;
}

void getArtwork(artwork *artw) {

    printf("\n# Registrazione di un opera d'arte #");

    artw->IDArtwork = getIdArtwork();

    getArtworkName(artw->name);

    getName(artw->authorName);

    getSurname(artw->authorSurname);

    artw->operaType = getOperaType();

    getKind(artw->kind);

    getHistorPeriod(artw->historPeriod);

    artw->BC = isBC();

    artw->prodYear = getProdYear(artw->BC);

}

void chooseArtwork(unsigned int *IDs, const unsigned int dim) {

    FILE *file = NULL;
    char str[MAX_LEN_ARTWORK];
    unsigned int temp, choice;

    do {
        printf("\n>Inserire \"1\" per avviare una ricerca dettgliata delle opere disponibili\n>Inserire \"2\" "
               "per visualizzare in modo compatto tutte le opere nel sistema\n");
        choice = getUInt(10);
        switch (choice) {
            case 1:
                research();
                break;
            case 2:
                if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt",
                                  "r")) == NULL) {
                    printf("\n-ATTENZIONE: Non e' stato possibile aprire il file!");
                } else {
                    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL) {
                        printf("\n\t\t>ID: %s;", strtok(str, "#"));
                        printf("\tNome opera: %s;", strtok(NULL, "-"));
                        printf("\tAutore:%s %s;", strtok(NULL, "-"), strtok(NULL, "-"));
                    }
                    fclose(file);
                }
                break;
            default:
                printf("\nInserire un valore tra quelli disponibili");
                break;
        }
    } while (choice < 1 || choice > 2);

    printf("\n\n\t\t-Digita l'ID delle opere, per aggiungerle alla mostra:");

    // l'utente manager dovrà inserire gli identificativi delle opere d'arte che la mostra dovrà
    // contenere.
    for (int i = 0; i < dim; ++i) {
        printf("\n\t-");
        temp = getUInt(10);

        // Prima che il valore temp venga inserito nel vettore di identificatori delle
        // opere d'arte, si verifica se tale valore è effettivamente esistente nel file Artworks.txt
        if (IDExists(temp, file)) {
            IDs[i] = temp;
        } else {
            printf("\n-ATTENZIONE: L'ID specificato e' inesistente riprova:");
        }
    }
}

void printArtwork(int num, artwork *artwork) {
    printf("\n\t-Questo e' il risultato numero %d:\n", num);
    printf("\n\t\t-Nome dell'opera d'arte: %s", artwork->name);
    printf("\n\t\t-Nome dell'autore dell'opera d'arte: %s", artwork->authorName);
    printf("\n\t\t-Cognome dell'autore dell'opera d'arte: %s", artwork->authorSurname);
    printf("\n\t\t-Tipo dell'opera d'arte: ");

    switch (artwork->operaType) {
        case 0:
            printf("Dipinto");
            break;
        case 1:
            printf("Scultura");
            break;
        case 2:
            printf("Disegno");
            break;
        default:
            printf("Errore nel tipo");
            break;
    }

    printf("\n\t\t-Genere dell'opera d'arte: %s", artwork->kind);
    printf("\n\t\t-Periodo storico dell'opera d'arte: %s", artwork->historPeriod);
    printf("\n\t\t-Anno di produzione dell'opera d'arte: %d", artwork->prodYear);

    if (artwork->BC == true) {
        printf(" BC\n");
    } else {
        printf(" AD\n");
    }

    assArtshow(artwork->IDArtwork);
}

void printArtworksInShow(unsigned int idArtshow) {
    FILE *file = NULL;
    unsigned int id, i = 0, idsArtworks[MAX_ARTWORKS], dim;
    char temp[MAX_LEN_ARTWORK], *ptr = NULL, *fNameArt = NULL, *fNameAut = NULL, *fSurname = NULL;
    bool run = true;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stato possibile aprire il file per la verifica.");
    } else {

        dim = fgetIdsArtwork(idArtshow, idsArtworks);

        while (fgets(temp, MAX_LEN_ARTWORK, file) != NULL && run) {
            id = strtoul(strtok(temp, "#"), &ptr, 10);

            fNameArt = strtok(NULL, "-");
            fNameAut = strtok(NULL, "-");
            fSurname = strtok(NULL, "-");

            if (id == idsArtworks[i]) {
                printf("\n\tNome opera:%s\tNome autore:%s %s;", fNameArt, fSurname, fNameAut);
                i++;
            }
            if (i == dim) {
                run = false;
            }
        }
        fclose(file);
    }
}

void loadArtwork(char str[], artwork *artwork) {

    char *fArtID = NULL, *fArtName = NULL, *fArtAuthorName = NULL, *fArtAuthorSurname = NULL, *fArtKind = NULL, *fhistorPeriod = NULL;
    char *fArtType = NULL;
    char *fArtProdYear = NULL;
    char *fArtBC = NULL;
    char *ptr = NULL;

    fArtID = strtok(str, "#");
    fArtName = strtok(NULL, "-");
    fArtAuthorName = strtok(NULL, "-");
    fArtAuthorSurname = strtok(NULL, "-");
    fArtType = strtok(NULL, "-");
    fArtKind = strtok(NULL, "-");
    fhistorPeriod = strtok(NULL, "-");
    fArtProdYear = strtok(NULL, "-");
    fArtBC = strtok(NULL, "-");

    artwork->IDArtwork = strtol(fArtID, &ptr, 10);
    strcpy(artwork->name, fArtName);
    strcpy(artwork->authorName, fArtAuthorName);
    strcpy(artwork->authorSurname, fArtAuthorSurname);
    artwork->operaType = strtol(fArtType, &ptr, 10);
    strcpy(artwork->kind, fArtKind);
    strcpy(artwork->historPeriod, fhistorPeriod);
    artwork->prodYear = strtol(fArtProdYear, &ptr, 10);
    artwork->BC = strtol(fArtBC, &ptr, 10);
}

bool IDExists(unsigned int ID, FILE *file)
{
    char str[MAX_LEN_ARTWORK], *ptr = NULL;
    bool run = true, idExists = false;
    // finché ci sono righe nel file e non ho ancora trovato l'identificativo cercato
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL && run){
        if ((strtol(strtok(str, "#"), &ptr, 10)) == ID){
            run = false;
            idExists = true;
        }
    }

    return idExists;
}


unsigned int getIDShow() {
    unsigned int id = 0;
    FILE *file = NULL;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {
        // Dato che gli identificativi di ogni show corrispondono con il numero di righe del file, basterà contare
        // il numero di righe per ottenere il nuovo idetificativo
        id = lineOfFile(file, MAX_LEN_SHOW);
        fclose(file);
    }

    return id;
}

char *getShow(date *timeStart, date *timeEnd, localManager *manager) {
    unsigned int dimShow;
    unsigned int *artworks = NULL, i = 0;
    char *idArtwork = NULL;
    printf("\n# Registra mostra #");

    getLocalManager(manager);

    getExpositionTime(timeStart, timeEnd);

    printf("\n\t-Inserisci il numero di opere che la mostra puo' contenere (Max 60 opere):\n\t\t-");
    do {
        if (i > 0) {
            printf("\n\t-ATTENZIONE: il numero di opere supera il massimo valore inseribile, riprova:");
        }
        dimShow = getUInt(10);
        i++;
    } while (dimShow > MAX_ARTWORKS);

    artworks = (unsigned int *) malloc(sizeof(unsigned int) * dimShow);

    // vengono visualizzate le opere disponibili dopodiché l'utente sceglie quali dovranno essere
    // prese in considerazione
    chooseArtwork(artworks, dimShow);

    // Ogni elemento del vettore artworks viene diviso da una virgola
    idArtwork = separateWithComma(artworks, dimShow);
    free(artworks);

    return idArtwork;
}

void delateArtshow(const unsigned int idArtshow) {
    FILE *fileArtshow = NULL, *fileArtshowCopy = NULL, *fileRes = NULL, *fileResCopy = NULL;
    char tempArtshow[MAX_LEN_SHOW], tempRes[MAX_LEN_RES], *ptr = NULL, *ptrArtshow = NULL, *ptrRes = NULL;
    unsigned int idArt, idRes;
    bool itWasCanc = false;

    if ((fileArtshow = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");
    } else {

        if ((fileArtshowCopy = fopen(
                "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyArtshow.txt", "w")) == NULL) {
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");

        } else {

            if ((fileRes = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt",
                                 "r")) == NULL) {
                printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");
            } else {

                if ((fileResCopy = fopen(
                        "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
                        "w")) == NULL) {
                    printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file.");

                } else {

                    // prendi la riga da Artshow.txt
                    while (fgets(tempArtshow, MAX_LEN_SHOW, fileArtshow) != NULL) {

                        // prendi la riga da Reservation.txt
                        fgets(tempRes, MAX_LEN_RES, fileRes);

                        ptrRes = reversStrtok(tempRes, '#');
                        ptrArtshow = reversStrtok(tempArtshow, '#');
                        idArt = strtol(strtok(tempArtshow, "#"), &ptr, 10);
                        idRes = strtol(strtok(tempRes, "#"), &ptr, 10);

                        // se l'id recuperato da file (idArt) e diverso da quello che passato alla procedura
                        if (idArt != idArtshow) {
                            // se la mostra è stata cancellata
                            if (itWasCanc) {
                                // allora gli identificativi delle mostre successive vengono decrementati,
                                // in modo tale da non avere valori che vengono saltati
                                idArt--;
                                idRes--;
                                fprintf(fileArtshowCopy, "%u#%s", idArt, ptrArtshow);
                                fprintf(fileResCopy, "%u#%s", idRes, ptrRes);

                            } else {
                                fprintf(fileArtshowCopy, "%u#%s", idArt, ptrArtshow);
                                fprintf(fileResCopy, "%u#%s", idRes, ptrRes);

                            }
                        } else {
                            itWasCanc = true;
                        }
                    }
                    fclose(fileResCopy);
                }
                fclose(fileRes);
            }
            fclose(fileArtshowCopy);
        }
        fclose(fileArtshow);
    }
    remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt");
    remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");

    rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyArtshow.txt",
           "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt");
    rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
           "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
}

bool isShowOver(const unsigned int id) {
    bool proposition;
    date current, fdate;

    // carica le due date
    getCurrentDate(&current);
    fgetDateEnd(&fdate, id);

    // cofronta le date
    proposition = isPrevious(&fdate, &current);

    return proposition;
}

void assArtshow(unsigned int id) {
    FILE *file = NULL;
    char str[MAX_LEN_SHOW], *name = NULL, *dates = NULL, *datee = NULL, *ptr = NULL, *ids = NULL, pos[5];
    unsigned int idShow;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    } else {
        while (fgets(str, MAX_LEN_SHOW, file) != NULL) {
            ids = reversStrtok(reversStrtok(reversStrtok(reversStrtok(str, '/'), '#'), '/'), '#');
            ids[strlen(ids) - 1] = '\0';

            idShow = strtol(strtok(str, "#"), &ptr, 10);

            name = strtok(NULL, "#");

            strtok(NULL, "#");

            dates = strtok(NULL, "#");
            datee = strtok(NULL, "#");

            sprintf(pos, "%u", id);

            if (strstr(ids, pos) != NULL) {
                printf("\n\t>Quest'opera verra' esposta nella mostra con queste caratteristiche:");
                printf("\n\t\t-ID: %u", idShow);
                printf("\n\t\t-Nome: %s", name);
                printf("\n\t\t-Data inizio: %s", dates);
                printf("\n\t\t-Data fine: %s", datee);
            }
        }
        fclose(file);
    }
}

void selectArtshow(char *username) {
    unsigned int choice;

    printf("\n\t-Digita il ID della mostra a cui vuoi registrarti:\n\t-");
    choice = getUInt(10);
    bookClient(choice, username);
}

void editRes(char *oldUsername, char *newUsername) {
    FILE *oldRes = NULL, *newRes = NULL;
    char str[MAX_LEN_RES], *leftSubs = NULL, *subToReplace = NULL, *rigthSubs = NULL;

    if ((oldRes = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt", "r")) ==
        NULL) {
        printf("-ATTENZIONE: Non e' stato possibile aprire il file!\n");
    } else {
        if ((newRes = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
                            "w")) == NULL) {
            printf("-ATTENZIONE: Non e' stato possibile aprire il file!\n");
        } else {
            // finche non ci sono più righe nel file
            while (fgets(str, MAX_LEN_RES, oldRes) != NULL) {

                // allora se nella stringa appena presa, esiste l'username dell'utente che deve essere modificato
                if ((subToReplace = strstr(str, oldUsername)) != NULL) {

                    // se è il primo all'interno del file
                    if (*(subToReplace - 1) != '#') {

                        // allora rimpiazza il carattere precedente con il carattere '.' in modo tale da recuperare
                        // tutta la sottostringa che precede l'username da rimpiazzare
                        *(subToReplace - 1) = '.';

                        // recupera la sottostringa successiva a l'username che deve essere rimpiazzato
                        rigthSubs = reversStrtok(subToReplace, ',');

                        // recupera la sottostringa che precede l'username da rimpiazzare
                        leftSubs = strtok(str, ".");

                        // memoriazza nel nuovo file la sottostringa sinistra, il nuovo username di rimpiazzo e la
                        // sottostringa sinistra
                        fprintf(newRes, "%s,%s,%s", leftSubs, newUsername, rigthSubs);
                    } else {

                        // fai le stesse cose
                        *(subToReplace - 1) = '.';
                        rigthSubs = reversStrtok(subToReplace, ',');
                        leftSubs = strtok(str, ".");

                        // ma memorizzale in un modo differente
                        fprintf(newRes, "%s#%s,%s", leftSubs, newUsername, rigthSubs);
                    }
                } else {
                    fprintf(newRes, "%s", str);
                }
            }
            fclose(newRes);
        }
        fclose(oldRes);
    }
    remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
    rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
           "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
}

void printShow()
{
    FILE *file = NULL;
    char str[MAX_LEN_SHOW], *name = NULL, *dates = NULL, *datee = NULL, *ptr = NULL;
    unsigned int idShow, num = 1;
    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: non e' stata possibile effettuare l'operazione!");
    }
    else
    {
        while (fgets(str, MAX_LEN_SHOW, file) != NULL)
        {
            idShow = strtol(strtok(str, "#"), &ptr, 10);
            name = strtok(NULL, "#");
            strtok(NULL, "#");
            dates = strtok(NULL, "#");
            datee = strtok(NULL, "#");

            printf("\n\t>Mostra numero: %u", num);
            printf("\n\t\t-ID mostra: %u", idShow);
            printf("\n\t\t-Nome mostra: %s", name);
            printf("\n\t\t-Data inizio mostra: %s", dates);
            printf("\n\t\t-Data fine mostra: %s", datee);
            num++;
        }
    fclose(file);
    }
}
