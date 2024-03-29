#include <stdio.h>
#include <string.h>
#include "../dataType/ArtShow/Artshow.h"
#include "datainput.h"
#include "search.h"
#include <stdlib.h>

void research()
{
    FILE *file = NULL;
    unsigned int choice;
    do
    {
        printf("\n\t>Scegliere criterio di ricerca:\n\t\t-1] Nome opera;\n\t\t-2] Autore opera;"
               "\n\t\t-3] Tipo opera;\n\t\t-4] Genere opera;\n\t\t-5] Periodo storico opera;"
               "\n\t\t-6] Anno produzione opera\n\t-");
        choice = getUInt(10);
        if ((file = fopen("Data/Artworks.txt", "r")) ==
            NULL)
        {
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file delle opere.");
        }
        else
        {
            switch (choice)
            {
            case 1:

                printf("\n\t-Ricerca tramite nome");
                searchName(file);
                break;

            case 2:

                printf("\n\t-Ricerca tramite autore");
                searchArtAuthor(file);
                break;

            case 3:

                printf("\n\t-Ricerca tramite tipo di opera");
                searchArtType(file);
                break;

            case 4:

                printf("\n\t-Ricerca tramite genere di opera");
                searchArtKind(file);
                break;

            case 5:

                printf("\n\t-Ricerca tramite periodo storico");
                searchArtHistorPeriod(file);
                break;

            case 6:

                printf("\n\t-Ricerca tramite anno di produzione");
                searchArtProdYear(file);
                break;

            default:
                printf("\n\t-Azione di ricerca interrotta!");
                break;
            }
            fclose(file);
        }
    } while (choice < 1 || choice > 6);
}

void searchName(FILE *file)
{
    char name[MAX_LEN_ARTWORK], str[MAX_LEN_ARTWORK];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire nome da ricercare\n\t-");
    gets(name);
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.name, name) != NULL)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtAuthor(FILE *file)
{
    char authorName[MAX_LEN_ARTWORK], str[MAX_LEN_ARTWORK];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire il nome, il cognome o nome e cognome dell'autore\n\t-");
    gets(authorName);
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strcmp(artwork.authorName, authorName) == 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
        else
        {
            if (strcmp(artwork.authorSurname, authorName) == 0)
            {
                num++;
                printArtwork(num, &artwork);
            }
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtType(FILE *file)
{
    char str[MAX_LEN_ARTWORK];
    unsigned int artType;
    artwork artwork;
    int num = 0;
    do
    {
        printf("\n\t>Inserire un tipo tra i disponibili:\n\t\t-1] Dipinto;\n\t\t-2] Scultura;\n\t\t-3] Disegno;\n\t-");
        artType = getUInt(10);
    } while (artType < 1 || artType > 3);
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (artwork.operaType == (artType - 1))
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtKind(FILE *file)
{
    char artKind[MAX_LEN_ARTWORK], str[MAX_LEN_ARTWORK];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire genere\n\t-");
    gets(artKind);
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.kind, artKind) != 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtHistorPeriod(FILE *file)
{
    char artHistorPeriod[MAX_LEN_ARTWORK], str[MAX_LEN_ARTWORK];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo storico (a lettere)\n\t-");
    gets(artHistorPeriod);
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.historPeriod, artHistorPeriod) != 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtProdYear(FILE *file)
{
    char str[MAX_LEN_ARTWORK];
    int min, max, c;
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo di produzione");
    printf("\n\t>Primo anno:\n\t-");
    min = getInt(10);
    printf("\n\t>Secondo anno:\n\t-");
    max = getInt(10);
    if (min > max)
    {
        c = min;
        min = max;
        max = c;
    }
    while (fgets(str, MAX_LEN_ARTWORK, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (artwork.prodYear >= min && artwork.prodYear <= max)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchShowName()
{
    FILE *file = NULL;
    char name[50], str[MAX_LEN_SHOW], *showName = NULL, *dates = NULL, *datee = NULL, *ptr = NULL;
    unsigned int id;
    unsigned int num = 1;

    if ((file = fopen("Data/Artshow.txt", "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: non e' stata possibile aprire il file delle mostre!");
    }
    else
    {
        printf("\n\t>Inserire nome da ricercare\n\t-");
        gets(name);
        while (fgets(str, MAX_LEN_SHOW, file) != NULL)
        {
            id = strtol(strtok(str, "#"), &ptr, 10);
            showName = strtok(NULL, "#");
            strtok(NULL, "#");
            dates = strtok(NULL, "#");
            datee = strtok(NULL, "#");
            if (strcmp(name, showName) == 0)
            {
                printf("\n\t>Mostra numero: %u", num);
                printf("\n\t\t-ID mostra: %u", id);
                printf("\n\t\t-Nome mostra: %s", showName);
                printf("\n\t\t-Data inizio mostra: %s", dates);
                printf("\n\t\t-Data fine mostra: %s", datee);
                num++;
            }
        }
        fclose(file);
    }
}