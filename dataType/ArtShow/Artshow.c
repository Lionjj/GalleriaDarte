#include <stddef.h>
#include <stdio.h>

#include <stdlib.h>
#include "Artshow.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "../Users/Users.h"
#include "../../lib/search.h"
#include "../Users/Client.h"
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define MAX_LEN_MANAGER 415

void getStreet(char *streetName)
{
    char str[90], *str2 = NULL;
    int i = 0;

    printf("\n\t>Via/piazza (Il nome della via/piazza non deve contenere numeri\n\t e deve essere compreso tra i 5 e i 90 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: La via/piazza inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalphaandspace(str) || strlen(str) > 90 || strlen(str) < 5);

    str2 = trimwhitespace(str);
    strcpy(streetName, str2);
}

void getHouseNum(char *houseNum)
{
    char str[5], *str2 = NULL;
    int i = 0;
    printf("\n\t>Numero civico (Il numero civico deve contenere esclusivamente numeri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il numero inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalnum(str));

    str2 = deletespaces(str);
    strcpy(houseNum, str2);
}

void getCity(char *city)
{
    char str[30], *str2 = NULL;
    int i = 0;
    printf("\n\t>Citta' (Il nome della citta non deve contenere numeri\n\te deve essere compreso tra 4 e 30 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il nome della citta inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30 || strlen(str) < 4);

    str2 = trimwhitespace(str);
    strcpy(city, str2);
}

void getNameStructure(char *structure)
{
    char str[50], *str2 = NULL;
    int i = 0;
    printf("\n\t>Nome della struttura (Il nome della struttura non deve contenere numeri\n\te deve essere compreso tra 5 e 50 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il nome della struttura inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 50 || strlen(str) < 5);

    str2 = trimwhitespace(str);
    strcpy(structure, str2);
}

void getExhiPlace(exhiPlace *place)
{
    printf("\n# Registra sede galleria #\n\t-Inserisci:");

    getStreet(place->streetName);

    getHouseNum(place->houseNum);

    getCity(place->city);

    getNameStructure(place->structure);
}

void loadGallery(char str[], exhiPlace *place)
{
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

bool isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN)
{
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_MANAGER], *fGalCity, *fGalStreet, *fGalHouseN;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) == NULL)
    {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    }
    else
    {

        /*
        * Questo ciclo di controlli, continua fintato che, non è terminato il file, oppure termina se e solo se la
        * variabile proposition, che rappresenta il risultato finale del triplice controllo, è posta a true, ossia
        * esiste una galleria già registrata nel file ArtGalleryManager.txt con il medesimo indirizzo della galleria,
        * i cui valori sono stati passati alla funzione.
        */
        while (fgets(str, MAX_LEN_MANAGER, file) != NULL && proposition == false)
        {

            // recupera dal file ArtGalleryManager.txt tre sottostringhe: fGalCity, fGalStreet, fGalHouseN
            fGalCity = strtok(str, "<");
            fGalStreet = strtok(NULL, "<");
            fGalHouseN = strtok(NULL, "<");

            /* solo nel caso in cui, due sedi della galleria, si trovino nella stessa città bisonga verificare se si
             * trovino nella stessa via è in tale caso verificare anche se il numero civico è lo stesso.
             */

            //se le due sedi si trovano nella stessa citta
            if (strcmp(fGalCity, galCity) == 0)
            {
                // se si trovano nella stessa via
                if (strcmp(fGalStreet, galStreet) == 0)
                {
                    // se si trovano allo stesso numero
                    if (strcmp(fGalHouseN, galHouseN) == 0)
                    {
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

void getCurrentDate(date *d)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    d->day = tm.tm_mday;
    d->month = tm.tm_mon + 1;
    d->year = tm.tm_year + 1900;
}

void getYear(date *time, const unsigned int current)
{
    unsigned int t;
    int i = 0;

    printf("\n\t>Anno (L'anno deve essere maggiore o uguale a quello corrente):\n\t-");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: L'anno inserito non e' conforme con le specifiche richieste, riprova:\n\t-");
        }
        t = getUInt(10);
        i++;
    } while (t < current);

    time->year = t;
}

void getMonth(date *time, date *current)
{
    unsigned int t;
    int i = 0;

    printf("\n\t>Mese (Il mese deve essere maggiore o uguale a quello corrente):\n\t-");
    do
    {
        if (i != 0)
        {
            if (current->month > t && current->year == time->year)
            {
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12 e "
                       "\n\tdeve essere maggiore o uguale a %u, riprova:\n\t-",
                       current->month);
            }
            else
            {
                printf("\n\t-ATTENZIONE: Il mese inserito deve essere compreso fra 1 e 12, riprova:\n\t-");
            }
        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > 12) || (current->month > t && current->year == time->year));
    time->month = t;
}

void getDay(date *time, date *current)
{
    unsigned int t, lim;
    int i = 0;

    /*
     * verifica innanzituto il lim che corrisponde al numero massimo, rappresentante il giorno,
     * rispetto al mese specificato dal puntatore time->month. Nel caso in cui il mese è di 30 giorni allora la
     * variabile lim connterrà il valore 30 e così via per gli altri mesi.
     */
    if (time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11)
    {
        lim = 30;

        /*
         * Nel caso il mese corrisponde a febbraio, si verifica se l'anno, specificato dal puntatore time->year sia
         * bisestile attraverso la funzione isLeapYear(unsigned int year) che data un'annata verifica se essa è bisestile.
         * Nel caso l'anno sia bisestile allora lim conterrà il valore 29, altrimenti il valore 28.
         */
    }
    else if (time->month == 2)
    {
        if (isLeapYear(time->year))
        {
            lim = 29;
        }
        else
        {
            lim = 28;
        }
    }
    else
    {
        lim = 31;
    }

    printf("\n\t>Giorno (il giorno deve essere maggiore o uguale a quello corrente):\n\t-");
    do
    {
        if (i != 0)
        {
            if (t < current->day && current->month == time->month && current->year == time->year)
            {
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d e"
                       "\n\tdeve essere maggiore o uguale a %u, riprova:\n\t-",
                       lim, current->day);
            }
            else
            {
                printf("\n\t-ATTENZIONE: Il giorno inserito deve essere compreso fra 1 e %d, riprova:\n\t-", lim);
            }
        }
        t = getUInt(10);
        i++;
    } while ((t < 1 || t > lim) || (t < current->day && current->month == time->month && current->year == time->year));

    time->day = t;
}

void getDate(date *time)
{
    date current;
    getCurrentDate(&current);

    printf("\n\t-Inserisci:");
    getYear(time, current.year);
    getMonth(time, &current);
    getDay(time, &current);
}

void getExpositionTime(date *timeStart, date *timeEnd)
{
    int i = 0;
    bool isTemp = false;
    date current;

    printf("\n\t>E' una mostra temporanea?(s/n)\n\t-");
    if (toupper(getchar()) == 'S')
    {
        isTemp = true;
    }
    fflush(stdin);
    getCurrentDate(&current);
    do
    {
        printf("\n\t- Inizio data esposizione -");
        getDate(timeStart);
        if ((timeStart->year - current.year) > 5)
        {
            printf("\n\t-ATTENZIONE: L'anno della data di inizio della mostra non puo' essere distante piu' di 5 anni rispetto l'anno corrente");
        }
    } while ((timeStart->year - current.year) > 5);
    if (isTemp)
    {
        printf("\n\t- Fine data esposizione -");
        do
        {
            if (i > 0)
            {
                printf("\n\t-ATTENZIONE: La data di conclusione della mostra non deve essere precedente "
                       "alla data di inzio, inoltre non puo' essere distante piu' di 5\n\t\tanni dall'anno di inizio della mostra.");
            }
            getDate(timeEnd);
            i++;
        } while ((!isPrevious(timeStart, timeEnd)) || ((timeEnd->year - timeStart->year) > 5));
    }
    else
    {
        timeEnd->day = 0;
        timeEnd->month = 0;
        timeEnd->year = 0;
    }
}

void fgetDateEnd(date *timeEnd, const unsigned int id)
{
    FILE *file = NULL;
    char artShow[MAX_LEN_SHOW], *date = NULL, *ptr = NULL;
    unsigned int fid;
    bool run = true;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {

        while (fgets(artShow, MAX_LEN_SHOW, file) != NULL && run)
        {
            fid = strtol(strtok(artShow, "#"), &ptr, 10);

            if (id == fid)
            {
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

void listenerTimeExpired()
{
    FILE *file = NULL;
    unsigned int len = 0;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {
        len = lineOfFile(file, MAX_LEN_SHOW);

        fclose(file);
    }
    for (int i = 0; i < len; ++i)
    {
        // se l'i-esima mostra è terminata
        if (isShowOver(i))
        {
            // eliminala
            delateArtshow(i);
        }
    }
}

bool isLeapYear(unsigned int year)
{
    bool proposition = false;

    if (year % 400 == 0)
    {
        proposition = true;
    }
    else
    {
        if ((year % 4 == 0) && !(year % 100 == 0))
        {
            proposition = true;
        }
    }

    return proposition;
}

bool isPrevious(date *timeStart, date *timeEnd)
{
    bool proposition = false;

    // Nel caso sia una mostra temporanea procedi
    if (timeStart->day != 0)
    {
        if (timeStart->year < timeEnd->year)
        {
            proposition = true;
        }
        else if (timeStart->year == timeEnd->year)
        {
            if (timeStart->month < timeEnd->month)
            {
                proposition = true;
            }
            else if (timeStart->month == timeEnd->month)
            {
                if (timeStart->day <= timeEnd->day)
                {
                    proposition = true;
                }
            }
        }
    }

    return proposition;
}

void getFiscalCode(char *fiscalCode)
{
    char str[17];
    int i = 0;
    printf("\n\t>Codice fiscale (Il codice fiscale deve contenere solo numeri e lettere):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il codice fiscale non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) != 16);
    stoupper(str);
    strcpy(fiscalCode, str);
}

void getLocalManager(localManager *manager)
{
    printf("\n\t- Registrazione del manager locale -\n\t-Inserisci:");
    getName(manager->name);
    getSurname(manager->surname);
    getFiscalCode(manager->fiscalCode);
}

unsigned int getIdArtwork()
{
    FILE *file = NULL;
    size_t id = 0;

    if ((file = fopen("Data/Artworks.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    }
    else
    {
        // Dato che gli identificativi di ogni opera corrispondono con il numero di righe del file, basterà contare
        // il numero di righe per ottenere il nuovo idetificativo
        id = lineOfFile(file, MAX_LEN_ARTWORK);
        fclose(file);
    }

    return id;
}

void getArtworkName(char *artworkName)
{
    char str[100], *str2 = NULL;
    int i = 0;
    printf("\n\t>Nome opera d'arte (Il nome dell'opera deve contenere esclusivamente\n\tlettere e deve essere compreso tra 5 e 100 caratteri):\n\t-");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il nome dell'opera non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalphaandspace(str) || strlen(str) > 100 || strlen(str) < 5);

    str2 = trimwhitespace(str);
    strcpy(artworkName, str2);
}

enum operaType getOperaType()
{
    enum operaType opType;
    bool run = true;
    unsigned int choice;

    do
    {
        printf("\n\t-Premi:\n\t\t-1] Dipinto;\n\t\t-2] Scultura;\n\t\t-3] Disegno;\n\t-");
        choice = getUInt(10);

        switch (choice)
        {
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

void getKind(char *kind)
{
    char str[30], *str2 = NULL;
    int i = 0;
    printf("\n\t>Genere opera (Il genere dell'opera deve contenere solo lettere\n\te deve essere compreso tra 5 e 30 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il genere dell'opera non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalphaandspace(str) || strlen(str) > 30 || strlen(str) < 5);

    str2 = trimwhitespace(str);
    strcpy(kind, str2);
}

void getHistorPeriod(char *historPeriod)
{
    char str[30], *str2 = NULL;
    int i = 0;
    printf("\n\t>Periodo storico (Il periodo storico deve contenere solo lettere\n\te deve essere compreso tra 4 e 30 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il perido storico non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalphaandspace(str) || strlen(str) > 30 || strlen(str) < 4);

    str2 = trimwhitespace(str);
    strcpy(historPeriod, str2);
}

bool isBC()
{
    bool proposition = false;
    printf("\n\t>Si tratta di un opera avanti cristo? (S/N):\n\t-");

    if (toupper(getchar()) == 'S')
    {
        proposition = true;
    }
    fflush(stdin);
    return proposition;
}

unsigned int getProdYear(bool BC)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    unsigned int currentY = tm.tm_year + 1900;
    unsigned int year, i = 0;

    printf("\n\t>Anno di produzione (L'anno non deve essere superiore a quello corrente, se l'opera e D.C.\n\t "
           "Altrimenti se e' A.C. non puo superare l'anno 40.000):\n\t-");

    do
    {

        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il perido storico non e' conforme con le specifiche richieste, riprova:\n\t-");
        }

        year = getUInt(10);
        i++;

        // Se l'anno di porduzione non è A.C., verifica se l'anno inserito è maggiore di quello corrente
        // oppure se l'opera è A.C. verifica se è maggiore della prima opera scoperta
    } while ((!BC && year > currentY) || (BC && year > 40000));
    return year;
}

void getArtwork(artwork *artw)
{

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

void chooseArtwork(unsigned int *IDs, const unsigned int dim)
{

    FILE *file = NULL;
    char str[MAX_LEN_ARTWORK];
    unsigned int choice, j;
    bool doesExists = true;
    bool isAlreadySelected = false;
    bool isFileArtshow = false;

    if ((file = fopen("Data/Artworks.txt",
                      "r")) == NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle opere!");
    }
    else
    {
        do
        {
            printf("\n\t>Inserire \"1\" per avviare una ricerca dettgliata delle opere disponibili\n\t>Inserire \"2\" per visualizzare in modo compatto tutte le opere nel sistema\n\t-");
            choice = getUInt(10);
            switch (choice)
            {
            case 1:
                research();
                break;
            case 2:
                while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
                {
                    printf("\n\t\t>ID: %s;", strtok(str, "#"));
                    printf("\n\tNome opera: %s;", strtok(NULL, "-"));
                    printf("\n\tAutore:%s %s;\n", strtok(NULL, "-"), strtok(NULL, "-"));
                }
                break;
            default:
                printf("\n\tInserire un valore tra quelli disponibili.");
                break;
            }
            // Prima che il valore temp venga inserito nel vettore di identificatori delle
            // opere d'arte, si verifica se tale valore è effettivamente esistente nel file Artworks.txt

        } while (choice < 1 || choice > 2);

        printf("\n\t-Digita l'ID delle opere, per aggiungerle alla mostra:");

        // l'utente manager dovrà inserire gli identificativi delle opere d'arte che la mostra dovrà
        // contenere.
        for (int i = 0; i < dim; ++i)
        {
            printf("\n\t-");
            // Il valore temp venga inserito nel vettore di identificatori delle
            // opere d'arte, poi si verifica se tale valore è effettivamente esistente nel file Artworks.txt e che non sia stato
            // già inserito precedentemente nel vettore stesso. Se una di queste due condizioni non è rispettata il valore viene riscritto.
            do
            {
                IDs[i] = getUInt(10);
                doesExists = IDExists(IDs[i], isFileArtshow);
                if (!doesExists)
                {
                    printf("\n\t-ATTENZIONE: L'ID specificato e' inesistente riprova:");
                }
                else
                {
                    isAlreadySelected = false;
                    for (j = 0; j < i; j++)
                    {
                        if (IDs[j] == IDs[i])
                        {
                            printf("\n\t-ATTENZIONE: Hai gia' inserito questo ID, riprova:");
                            isAlreadySelected = true;
                            break;
                        }
                    }
                }
            } while (!doesExists || isAlreadySelected);
        }
    }
    fclose(file);
}

void printArtwork(int num, artwork *artwork)
{
    printf("\n\t-Questo e' il risultato numero %d:\n", num);
    printf("\n\t\t-Nome dell'opera d'arte: %s", artwork->name);
    printf("\n\t\t-Nome dell'autore dell'opera d'arte: %s", artwork->authorName);
    printf("\n\t\t-Cognome dell'autore dell'opera d'arte: %s", artwork->authorSurname);
    printf("\n\t\t-Tipo dell'opera d'arte: ");

    switch (artwork->operaType)
    {
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
        printf("-ATTENZIONE: Errore nel tipo di opera!");
        break;
    }

    printf("\n\t\t-Genere dell'opera d'arte: %s", artwork->kind);
    printf("\n\t\t-Periodo storico dell'opera d'arte: %s", artwork->historPeriod);
    printf("\n\t\t-Anno di produzione dell'opera d'arte: %d", artwork->prodYear);

    if (artwork->BC == true)
    {
        printf(" A.C.\n");
    }
    else
    {
        printf(" D.C.\n");
    }

    assArtshow(artwork->IDArtwork);
}

void printArtworksInShow(unsigned int idArtshow)
{
    FILE *file = NULL;
    unsigned int id, i = 0, idsArtworks[MAX_ARTWORKS], dim;
    char temp[MAX_LEN_ARTWORK], *ptr = NULL, *fNameArt = NULL, *fNameAut = NULL, *fSurname = NULL;
    bool run = true;

    if ((file = fopen("Data/Artworks.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: non è stato possibile aprire il file delle opere.");
    }
    else
    {

        dim = fgetIdsArtwork(idArtshow, idsArtworks);

        while (fgets(temp, MAX_LEN_ARTWORK, file) != NULL && run)
        {
            id = strtoul(strtok(temp, "#"), &ptr, 10);

            fNameArt = strtok(NULL, "-");
            fNameAut = strtok(NULL, "-");
            fSurname = strtok(NULL, "-");

            if (id == idsArtworks[i])
            {
                printf("\n\tNome opera:%s\n\tNome autore:%s %s\n", fNameArt, fSurname, fNameAut);
                i++;
            }
            if (i == dim)
            {
                run = false;
            }
        }
        fclose(file);
    }
}

void loadArtwork(char str[], artwork *artwork)
{

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

bool IDExists(unsigned int ID, bool isFileArtshow)
{
    FILE *file = NULL;
    char str[MAX_LEN_ARTWORK], *ptr = NULL;
    bool run = true, idExists = false;
    if (isFileArtshow)
    {
        if ((file = fopen("Data/Artshow.txt", "r")) == NULL)
        {
            printf("\n\t-ATTENZIONE: non e' stato possibile aprire il file delle mostre!");
        }
        else
        {
            // finché ci sono righe nel file e non ho ancora trovato l'identificativo cercato
            while (fgets(str, MAX_LEN_ARTWORK, file) != NULL && run)
            {
                if ((strtol(strtok(str, "#"), &ptr, 10)) == ID)
                {
                    run = false;
                    idExists = true;
                }
            }
        }
    }
    else
    {
        if ((file = fopen("Data/Artworks.txt", "r")) == NULL)
        {
            printf("\n\t-ATTENZIONE: non e' stato possibile aprire il file delle opere!");
        }
        else
        {
            // finché ci sono righe nel file e non ho ancora trovato l'identificativo cercato
            while (fgets(str, MAX_LEN_ARTWORK, file) != NULL && run)
            {
                if ((strtol(strtok(str, "#"), &ptr, 10)) == ID)
                {
                    run = false;
                    idExists = true;
                }
            }
        }
    }
    fclose(file);
    return idExists;
}

bool isArtworkAlredyReg(char *artName)
{
    FILE *file = NULL;
    char str[MAX_LEN_ARTWORK], *name = NULL;
    bool proposition = false, run = true;
    if ((file = fopen("Data/Artworks.txt", "r")) == NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle opere.");
    }
    else
    {
        while (fgets(str, MAX_LEN_ARTWORK, file) != NULL && run)
        {
            strtok(str, "#");
            name = strtok(NULL, "-");

            if (strcmp(name, artName) == 0)
            {
                proposition = true;
                run = false;
            }
        }
        fclose(file);
    }
    return proposition;
}

unsigned int getIDShow()
{
    unsigned int id = 0;
    FILE *file = NULL;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {
        // Dato che gli identificativi di ogni show corrispondono con il numero di righe del file, basterà contare
        // il numero di righe per ottenere il nuovo idetificativo
        id = lineOfFile(file, MAX_LEN_SHOW);
        fclose(file);
    }

    return id;
}

char *getShow(date *timeStart, date *timeEnd, localManager *manager)
{
    unsigned int dimShow;
    unsigned int *artworks = NULL, i = 0;
    char *idArtwork = NULL;
    printf("\n# Registra mostra #");

    getLocalManager(manager);

    getExpositionTime(timeStart, timeEnd);

    printf("\n\t-Inserisci il numero di opere che la mostra puo' contenere (Max 60 opere):\n\t-");
    do
    {
        if (i > 0)
        {
            printf("\n\t-ATTENZIONE: il numero di opere supera il massimo valore inseribile, riprova:\n\t-");
        }
        dimShow = getUInt(10);
        i++;
    } while (dimShow > MAX_ARTWORKS);

    artworks = (unsigned int *)malloc(sizeof(unsigned int) * dimShow);

    // vengono visualizzate le opere disponibili dopodiché l'utente sceglie quali dovranno essere
    // prese in considerazione
    chooseArtwork(artworks, dimShow);

    // Ogni elemento del vettore artworks viene diviso da una virgola
    idArtwork = separateWithComma(artworks, dimShow);
    free(artworks);

    return idArtwork;
}

void delateArtshow(const unsigned int idArtshow)
{
    FILE *fileArtshow = NULL, *fileArtshowCopy = NULL, *fileRes = NULL, *fileResCopy = NULL;
    char tempArtshow[MAX_LEN_SHOW], tempRes[MAX_LEN_RES], *ptr = NULL, *ptrArtshow = NULL, *ptrRes = NULL;
    unsigned int idArt, idRes;
    bool itWasCanc = false;

    if ((fileArtshow = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {

        if ((fileArtshowCopy = fopen(
                 "Data/CopyArtshow.txt", "w")) == NULL)
        {
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file copia delle mostre.");
        }
        else
        {

            if ((fileRes = fopen("Data/Reservations.txt",
                                 "r")) == NULL)
            {
                printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle prenotazioni.");
            }
            else
            {

                if ((fileResCopy = fopen(
                         "Data/CopyReservations.txt",
                         "w")) == NULL)
                {
                    printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file copia delle prenotazioni.");
                }
                else
                {

                    // prendi la riga da Artshow.txt
                    while (fgets(tempArtshow, MAX_LEN_SHOW, fileArtshow) != NULL)
                    {

                        // prendi la riga da Reservation.txt
                        fgets(tempRes, MAX_LEN_RES, fileRes);

                        ptrRes = reversStrtok(tempRes, '#');
                        ptrArtshow = reversStrtok(tempArtshow, '#');
                        idArt = strtol(strtok(tempArtshow, "#"), &ptr, 10);
                        idRes = strtol(strtok(tempRes, "#"), &ptr, 10);

                        // se l'id recuperato da file (idArt) e diverso da quello che passato alla procedura
                        if (idArt != idArtshow)
                        {
                            // se la mostra è stata cancellata
                            if (itWasCanc)
                            {
                                // allora gli identificativi delle mostre successive vengono decrementati,
                                // in modo tale da non avere valori che vengono saltati
                                idArt--;
                                idRes--;
                                fprintf(fileArtshowCopy, "%u#%s", idArt, ptrArtshow);
                                fprintf(fileResCopy, "%u#%s", idRes, ptrRes);
                            }
                            else
                            {
                                fprintf(fileArtshowCopy, "%u#%s", idArt, ptrArtshow);
                                fprintf(fileResCopy, "%u#%s", idRes, ptrRes);
                            }
                        }
                        else
                        {
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
    remove("Data/Artshow.txt");
    remove("Data/Reservations.txt");

    rename("Data/CopyArtshow.txt",
           "Data/Artshow.txt");
    rename("Data/CopyReservations.txt",
           "Data/Reservations.txt");
}

bool isShowOver(const unsigned int id)
{
    bool proposition;
    date current, fdate;

    // carica le due date
    getCurrentDate(&current);
    fgetDateEnd(&fdate, id);

    // cofronta le date
    proposition = isPrevious(&fdate, &current);

    return proposition;
}

void assArtshow(unsigned int id)
{
    FILE *file = NULL;
    char str[MAX_LEN_SHOW], *name = NULL, *dates = NULL, *datee = NULL, *ptr = NULL, *ids = NULL, pos[5];
    unsigned int idShow;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {
        while (fgets(str, MAX_LEN_SHOW, file) != NULL)
        {
            ids = reversStrtok(reversStrtok(reversStrtok(reversStrtok(str, '/'), '#'), '/'), '#');
            ids[strlen(ids) - 1] = '\0';

            idShow = strtol(strtok(str, "#"), &ptr, 10);

            name = strtok(NULL, "#");

            strtok(NULL, "#");

            dates = strtok(NULL, "#");
            datee = strtok(NULL, "#");

            sprintf(pos, "%u", id);

            if (strstr(ids, pos) != NULL)
            {
                printf("\n\t>Quest'opera verra' esposta nella mostra con queste caratteristiche:");
                printf("\n\t\t-ID: %u", idShow);
                printf("\n\t\t-Nome: %s", name);
                printf("\n\t\t-Data inizio: %s", dates);
                printf("\n\t\t-Data fine: %s\n", datee);
            }
        }
        fclose(file);
    }
}

void selectArtshow(char *username)
{
    unsigned int choice;

    printf("\n\t-Digita l'identificativo della mostra a cui vuoi registrarti:\n\t-");
    choice = getUInt(10);
    bookClient(choice, username);
}

void editRes(char *oldUsername, char *newUsername)
{
    FILE *oldRes = NULL, *newRes = NULL;
    char str[MAX_LEN_RES], *leftSubs = NULL, *subToReplace = NULL, *rigthSubs = NULL;

    if ((oldRes = fopen("Data/Reservations.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle prenotazioni.");
    }
    else
    {
        if ((newRes = fopen("Data/CopyReservations.txt",
                            "w")) == NULL)
        {
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file copia delle prenotazioni.");
        }
        else
        {
            // finche non ci sono più righe nel file
            while (fgets(str, MAX_LEN_RES, oldRes) != NULL)
            {

                // allora se nella stringa appena presa, esiste l'username dell'utente che deve essere modificato
                if ((subToReplace = strstr(str, oldUsername)) != NULL)
                {

                    // se non è il primo all'interno della riga file
                    if (*(subToReplace - 1) != '#')
                    {

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
                    }
                    else
                    {

                        // fai le stesse cose
                        *(subToReplace - 1) = '.';
                        rigthSubs = reversStrtok(subToReplace, ',');
                        leftSubs = strtok(str, ".");

                        // ma memorizzale in un modo differente
                        fprintf(newRes, "%s#%s,%s", leftSubs, newUsername, rigthSubs);
                    }
                }
                else
                {
                    fprintf(newRes, "%s", str);
                }
            }
            fclose(newRes);
        }
        fclose(oldRes);
    }
    remove("Data/Reservations.txt");
    rename("Data/CopyReservations.txt",
           "Data/Reservations.txt");
}

void printShow()
{
    FILE *file = NULL;
    char str[MAX_LEN_SHOW], *name = NULL, *dates = NULL, *datee = NULL, *ptr = NULL;
    unsigned int idShow, num = 1;
    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t--ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
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
            printf("\n\t\t-Data fine mostra: %s\n", datee);
            num++;
        }
        fclose(file);
    }
}

bool deleteReservationCheck(int idShow)
{
    FILE *file = NULL;
    char str[MAX_LEN_SHOW], *idString = NULL, *ptr = NULL;
    unsigned int id;
    date current, fDateStart;
    bool proposition = true;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle mostre.");
    }
    else
    {
        getCurrentDate(&current);
        while (fgets(str, MAX_LEN_SHOW, file) != NULL && proposition)
        {
            idString = strtok(str, "#");
            id = strtol(idString, &ptr, 10);
            if (id == idShow)
            {
                strtok(NULL, "#");
                strtok(NULL, "#");
                fDateStart.day = strtol(strtok(NULL, "/"), &ptr, 10);
                fDateStart.month = strtol(strtok(NULL, "/"), &ptr, 10);
                fDateStart.year = strtol(strtok(NULL, "/"), &ptr, 10);
                if (isPrevious(&current, &fDateStart))
                {
                    if (fDateStart.year == current.year && fDateStart.month == current.month && ((fDateStart.day - current.day) < 1))
                    {
                        proposition = false;
                    }
                }
            }
        }
    }
    return proposition;
}

bool printIdReservations(char *username)
{
    FILE *file = NULL;
    char str[MAX_LEN_RES], *idRes = NULL;
    bool ctrl = false;
    unsigned int num = 1;
    if ((file = fopen("Data/Reservations.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle prenotazioni.");
    }
    else
    {
        while (fgets(str, MAX_LEN_RES, file) != NULL)
        {
            if (strstr(str, username) != NULL)
            {
                idRes = strtok(str, "#");
                printf("\n\t>Prenotazione numero: %u", num);
                printf("\n\t\t-ID mostra prenotata: %s", idRes);
                num++;
                ctrl = true;
            }
        }
        if (!ctrl)
        {
            printf("\n\t-ATTENZIONE: Nessuna prenotazione trovata con questo account!");
        }
        fclose(file);
    }
    return ctrl;
}

bool deleteClientFromRes(char *username, unsigned int idshow)
{
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_RES], strCop[MAX_LEN_RES], *ptr = NULL, *subToReplace = NULL, *rigthSubs = NULL, *leftSubs = NULL;
    unsigned int id, max;
    bool ctrl = false;

    if ((file = fopen("Data/Reservations.txt",
                      "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle prenotazioni.");
    }
    else
    {

        if ((fileCopy = fopen(
                 "Data/CopyReservations.txt",
                 "w")) ==
            NULL)
        {
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file copia delle prenotazioni.");
        }
        else
        {
            // finche non ci sono più righe nel file
            while (fgets(str, MAX_LEN_RES, file) != NULL)
            {

                strcpy(strCop, str);

                // prendi l'id della prenotazione
                id = strtoul(strtok(strCop, "#"), &ptr, 10);

                // prendi il numero di posti disposnibili per la mostra
                max = strtoul(strtok(NULL, "#"), &ptr, 10);

                // se è la mostra da cui si vuole cancellare l'username
                if (id == idshow)
                {

                    // allora se nella stringa appena presa, esiste l'username dell'utente che deve essere cancellato
                    if ((subToReplace = strstr(str, username)) != NULL)
                    {
                        max++;
                        // se non è il primo all'interno della riga file
                        if (*(subToReplace - 1) != '#')
                        {

                            // allora rimpiazza il carattere precedente con il carattere '.' in modo tale da recuperare
                            // tutta la sottostringa che precede l'username da rimpiazzare
                            *(subToReplace - 1) = '.';
                            // recupera la sottostringa successiva a l'username che deve essere rimpiazzato
                            rigthSubs = reversStrtok(subToReplace, ',');

                            // recupera la sottostringa che precede l'username da rimpiazzare (tranne l'ID e il valore
                            // di posti diposnibili)
                            leftSubs = reversStrtok(str, '#');
                            leftSubs = reversStrtok(leftSubs, '#');
                            leftSubs = strtok(leftSubs, ".");

                            // elimina l'username dell'utente
                            fprintf(fileCopy, "%u#%u#%s,%s", id, max, leftSubs, rigthSubs);
                        }
                        else
                        {
                            // fai le stesse cose
                            rigthSubs = reversStrtok(subToReplace, ',');

                            // ma memorizzale in un modo differente
                            fprintf(fileCopy, "%u#%u#%s", id, max, rigthSubs);
                        }
                        ctrl = true;
                    }
                    else
                    {
                        fprintf(fileCopy, "%s", str);
                    }
                }
                else
                {
                    fprintf(fileCopy, "%s", str);
                }
            }

            fclose(file);
            fclose(fileCopy);

            if (ctrl)
            {
                remove("Data/Reservations.txt");
                rename("Data/CopyReservations.txt",
                       "Data/Reservations.txt");
            }
            else
            {
                remove("Data/CopyReservations.txt");
            }
        }
    }
    return ctrl;
}