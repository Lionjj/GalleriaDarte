#include <stddef.h>
#include <stdio.h>

#include <stdlib.h>
#include "Artshow.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "../User/Users.h"
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define MAX_LEN_USERS 415
#define MAX_LEN_ARTWORK 230
#define MAX_LEN_SHOW 300

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

/**
 * Per fare in modo che, tale procedura funzioni in maniera corretta, è necessario che il parametro str[], sia una
 * stringa recupreata dal file ArtGalleryManager.txt, in caso contrario il corretto funzionamento del modulo,
 * non è garantito.
 *
 */
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

/**
 * \pre Tale funzione recupera dal file ArtGalleryManager.txt tre sottostringhe: fGalCity, fGalStreet, fGalHouseN;
 * \pre che verranno confrontate con i parametri formali della funzione, rispettivamente nell'ordine: nome della città,
 * \pre via/piazza e numero civico. La realizzazione di questo controllo viene effettuata con tre if annidati questo poiché
 * \pre solo nel caso in cui, due sedi della galleria, si trovino nella stessa città bisonga verificare se si trovino nella
 * \pre stessa via è in tale caso verificare anche se il numero civico è lo stesso. Se queste condizoni risultanto vere,
 * \pre ossia esistono due sedi della galleria registrate allo stesso indirizzo, allora la funzione
 * \pre avverte l'utente manager di ciò.
 *
 * Questo ciclo di controlli, continua fintato che, non è terminato il file, oppure termina se e solo se la
 * variabile proposition, che rappresenta il risultato finale del triplice controllo, è posta a false, ossia non
 * esiste una galleria già registrata nel file ArtGalleryManager.txt con il medesimo indirizzo della galleria i cui
 * valori sono stati passati alla funzione.
 */
bool isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN) {
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_USERS], *fGalCity, *fGalStreet, *fGalHouseN;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\ArtGalleryManager.txt",
                      "r")) == NULL) {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        while (fgets(str, MAX_LEN_USERS, file) != NULL && proposition == false) {

            fGalCity = strtok(str, "<");
            fGalStreet = strtok(NULL, "<");
            fGalHouseN = strtok(NULL, "<");

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

void getCurrentDate(date* d){
    time_t t  = time(NULL);
    struct tm tm = *localtime(&t);
    d->day = tm.tm_mday;
    d->month = tm.tm_mon + 1;
    d->year = tm.tm_year + 1900;
}

void getYear(date* time,const unsigned int current){
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
            if(current->month > t && current->year == time->year){
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12 e "
                       "\n\tdeve essere maggiore o guale a %u, riprova:", current->month);
            } else{
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12, riprova:");
            }
        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > 12) || (current->month > t && current->year == time->year));
    time->month = t;
}

/**
 * In tale procedura viene verificato innanzituto il lim che corrisponde al numero massimo, rappresentante il giorno,
 * rispetto al mese specificato dal puntatore time->month. Nel caso in cui il mese è di 30 giorni allora la variabile
 * lim connterrà il valore 30 e così via per gli altri mesi.
 *
 * Nel caso il mese corrisponde a febbraio, si verifica se l'anno, specificato dal puntatore time->year sia
 * bisestile attraverso la funzione isLeapYear(unsigned int year) che data un'annata verifica se essa è bisestile.
 * Nel caso l'anno sia bisestile allora lim conterrà il valore 29, altrimenti il valore 28.
 *
 * \sa Artshow.c::isLeapYear(unsigned int year).
 */
void getDay(date* time, date* current){
    unsigned int t, lim;
    int i = 0;

    if(time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11){
        lim = 30;
    } else if(time->month == 2){
        if(isLeapYear(time->year)){
            lim = 29;
        } else{
            lim = 28;
        }
    } else{
        lim = 31;
    }

    printf("\n\t>Giorno (il giorno deve essere maggiore o uguale a quello corrente):");
    do {
        if (i != 0) {
            if(t < current->day && current->month == time->month){
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d e"
                       "\n\tdeve essere maggiore o guale a %u, riprova:", lim, current->day);
            } else{
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d, riprova:", lim);
            }

        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > lim) || (t < current->day && current->month == time->month));

    time->day = t;
}

void getDate(date* time){
    date current;
    getCurrentDate(&current);

    printf("\n-Inserisci:");
    getYear(time, current.year);
    getMonth(time, &current);
    getDay(time, &current);
}

/**
 * Una volta che la data timeStart, rappresentante la data di inizio di una mostra, viene caricata, allora la
 * data timeEnd non deve precedere la data di partenza della mostra.
 *
 * \sa Artshow.h::getDate(date* time)
 */
void getExpositionTime(date* timeStart, date* timeEnd){
    int i = 0;
    printf("\n- Inizio data esposizione -");
    getDate(timeStart);

    printf("\n- Fine data esposizione -");
    do{
        if(i > 0){
            printf("\n\t-ATTENZIONE: La data di conclusione della mostra non deve essere precedente "
                   "alla data di inzio, riprova.");
        }
        getDate(timeEnd);
        i++;
    } while (!isPrevious(timeStart, timeEnd));
}

bool isLeapYear(unsigned int year){
    bool proposition = false;

    if(year%400 == 0) {
        proposition = true;
    } else {
        if((year%4 == 0) && !(year%100 == 0)){
            proposition = true;
        }
    }

    return proposition;
}

bool isPrevious(date* timeStart, date* timeEnd){
    bool proposition = false;

    if(timeStart->year < timeEnd->year){
        proposition = true;
    } else if(timeStart->year == timeEnd->year){
        if(timeStart->month < timeEnd->month){
            proposition = true;
        } else if(timeStart->month == timeEnd->month){
            if(timeStart->day <= timeEnd->day){
                proposition = true;
            }
        }
    }

    return proposition;
}

void getFiscalCode(char* fiscalCode){
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

void getLocalManager(localManager* manager){
    printf("\n- Registrazione del manager locale -\n-Inserisci:");
    getName(manager->name);
    getSurname(manager->surname);
    getFiscalCode(manager->fiscalCode);
}

unsigned int getIdArtwork(){
    FILE* file = NULL;
    char str [MAX_LEN_ARTWORK];
    size_t id = 0;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) == NULL){
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else{
        while (fgets(str, MAX_LEN_ARTWORK, file) != NULL) id++;
        fclose(file);
    }

    return id;
}

void getArtworkName(char* artworkName){
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

enum operaType getOperaType(){
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

void getKind(char* kind){
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

void getHistorPeriod(char* historPeriod){
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

    if(toupper(getch()) == 'S'){
        proposition = true;
    }
    getch();
    return proposition;
}

/**
 * Tale funzione verifica se l'anno di produzione di un'opera d'arte, nel caso essa fosse A.C., non sià superiore
 * all'anno 40.000 A.C. (anno a cui risale la prima opera d'arte scoperta)
 */
unsigned int getProdYear(bool BC){
    time_t t  = time(NULL);
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

void getArtwork(artwork* artw){

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

/**
 *
 *
 * Nel ciclo for, l'utente manager dovrà inserire gli identificativi delle opere d'arte che la mostra dovrà
 * contenere. Prima che il valore temp, digitato dall'utente, venga inserito nel vettore di identificatori delle
 * opere d'arte, si verifica se tale valore è effettivamente esistente nel file Artworks
 */
void chooseArtwork(unsigned int* IDs, const unsigned int dim){

    FILE *file = NULL;
    char str[MAX_LEN_ARTWORK];
    unsigned int temp, choice;

    do
    {
        printf(">Inserire \"1\" per avviare una ricerca dettgliata delle opere disponibili\n>Inserire \"2\" per visualizzare in modo compatto tutte le opere nel sistema\n");
        choice = getUInt(10);
        switch (choice)
        {
        case 1:
            research();
            break;
        case 2:
            if ((file = fopen("Data/Artworks.txt", "r")) == NULL)
            {
                printf("\n-ATTENZIONE: Non e' stato possibile aprire il file!");
            }
            else
            {
                while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
                {
                    printf("\n\t\t>ID: %s;", strtok(str, "#"));
                    printf("\tNome opera: %s;", strtok(NULL, "-"));
                    printf("\tAutore:%s %s;", strtok(NULL, "-"), strtok(NULL, "-"));
                }
                fclose(file);
            }
            break;
        default:
            printf("Inserire un valore tra quelli disponibili");
            break;
        }
    } while (choice < 1 || choice > 2);

    printf("\n\n\t\t-Digita l'ID delle opere, per aggiungerle alla mostra:");

    for (int i = 0; i < dim; ++i) {
        printf("\n\t-");
        temp = getUInt(10);
        if(IDExists(temp)){
            IDs[i] = temp;
        } else{
            printf("\n-ATTENZIONE: L'ID specificato e' inesistente riprova:");
        }
    }
}

/**
 * Tale funzion verifica, all'interno del file Artworks.txt, l'esistenza dell'identificativo passato come
 * parametro reale alla funzione. Se l'identificativo esiste allora restitusice true.
 */
bool IDExists(unsigned int ID){
    FILE* file = NULL;
    char str[MAX_LEN_ARTWORK], *ptr;
    bool run = true, idExists = false;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) == NULL){
        printf("\n-ATTENZIONE: Non e' stato possibile aprire il file!");
    } else{
        while (fgets(str, MAX_LEN_ARTWORK, file) != NULL && run){
            if((strtol(strtok(str, "#"), &ptr, 10)) == ID){
                run = false;
                idExists = true;
            }
        }
        fclose(file);
        free(ptr);
    }
    return idExists;
}

unsigned int getIDShow(){
    unsigned int id = 0;
    FILE* file = NULL;
    char str [MAX_LEN_SHOW];

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) == NULL){
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else{
        /** \ Conta le righe del file*/
        while (fgets(str, MAX_LEN_ARTWORK, file) != NULL) id++;
        fclose(file);
    }

    return id;
}

char* getShow(date *timeStart, date* timeEnd, localManager* manager){
    unsigned int dimShow;
    unsigned int *artworks = NULL;
    char *idArtwork = NULL;
    printf("\n# Registra mostra #");
    getExpositionTime(timeStart, timeEnd);

    getLocalManager(manager);
    /**
     * \bug risolvere timeEnd->day rimane uogale a zero
     */
    printf("\n\t-Inserisci il numero di opere che la mostra puo' contenere:\n\t\t-");
    dimShow = getUInt(10);
    artworks = (unsigned int*) malloc(sizeof (unsigned int)* dimShow);

    chooseArtwork(artworks, dimShow);
    idArtwork = separateWithComma(artworks, dimShow);

    free(artworks);

    return idArtwork;
}

//Non completo
/*void printArtshow(FILE *file, unsigned int ido)
{
    char *nome, str[MAX_LEN_SHOW], *id = NULL;

    while (fgets(str, MAX_LEN_SHOW, file) != NULL)
    {
        id = atoi(strtok(str, "#"));
        printf("%d", id);
        nome = strtok(NULL, "#");
        strtok(NULL, "#");
        if (strstr(ido,id) != 0)
        {
            printf("\n\t>Quest'opera verra' mostrata nella mostra con queste caratteristiche:");
            printf("\n\t\t-ID: %s", id);
            printf("\n\t\t-Nome: %s", nome);
        }
    }
}
*/