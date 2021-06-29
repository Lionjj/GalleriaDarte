#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ArtShow/Artshow.h"
#include "Users.h"
#include "../../lib/datainput.h"
#include "Artgallerymanagers.h"

void editManagerFile(User *user, exhiPlace *place, unsigned int choice)
{
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_MANAGER];
    User temp;
    exhiPlace tempP;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    }
    else
    {
        if ((fileCopy = fopen(
                 "Data/CopyArtGallety.txt",
                 "w")) == NULL)
        {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        }
        else
        {
            // continua fintato che non ci sono più linee nel file
            while (fgets(str, MAX_LEN_MANAGER, file) != NULL)
            {

                loadUser(str, &temp);
                loadGallery(NULL, &tempP);

                if (strcmp(temp.username, user->username) == 0)
                {

                    // a seconda della scelta, nell'ordine, è possibile modificare: username, email, password oppure
                    // informazioni riguardanti la galleria: Città, via e numero civico
                    switch (choice)
                    {
                    case 1:

                        getUsername(temp.username);

                        // Se l'username non è presente nel file ArtGalleryManager.txt
                        if (!isUserAlredyReg(temp.username, "", 'u', user->artGalleryManager))
                        {
                            // Cambia l'attuale username dell'utente con quello nuovo
                            strcpy(user->username, temp.username);
                        }
                        else
                        {
                            // altrimenti reimposta il precedente
                            strcpy(temp.username, user->username);
                        }
                        break;

                    case 2:

                        getEmail(temp.email);

                        // Se l'e-mail non è presente nel file ArtGalleryManager.txt
                        if (!isUserAlredyReg("", temp.email, 'e', user->artGalleryManager))
                        {
                            // Cambia l'attuale e-mail dell'utente con quello nuovo
                            strcpy(user->email, temp.email);
                        }
                        else
                        {
                            // altrimenti reimposta il precedente
                            strcpy(temp.email, user->email);
                        }
                        break;

                    case 3:

                        getPw(temp.pw);
                        strcpy(user->pw, temp.pw);

                        break;

                    case 4:
                        printf("\n\tPremi:\n\t\t-1] Per modificare la citta';\n\t\t-2] Per modificare la via;"
                               "\n\t\t-3] Per modificare il numero civico;\n\t\t-4] oppure un qualsiasi bottone "
                               "interrompere la modifica;\n\t-");

                        choice = getUInt(10);

                        switch (choice)
                        {
                        case 1:

                            // nel caso l'utente manager debba cambiare la città in cui si trova la sede della
                            // galleria dovrà necessariamente cambiare anche la via e il numero civico
                            getCity(tempP.city);

                            getStreet(tempP.streetName);

                            getHouseNum(tempP.houseNum);

                            // Se la nuova sede non è già registrata
                            if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum))
                            {

                                // Rimpiazza i valori precedenti con quelli nuvoi
                                strcpy(place->city, tempP.city);
                                strcpy(place->streetName, tempP.streetName);
                                strcpy(place->houseNum, tempP.houseNum);
                            }
                            else
                            {

                                // Altrimenti reimposta i valori precedenti
                                strcpy(tempP.city, place->city);
                                strcpy(tempP.streetName, place->streetName);
                                strcpy(tempP.houseNum, place->houseNum);
                            }
                            break;
                        case 2:

                            // nel caso l'utente debba cambiare la via in cui a sede è situata dovrà cambiare
                            // anche il numero civico

                            getStreet(tempP.streetName);

                            getHouseNum(tempP.houseNum);

                            if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum))
                            {
                                strcpy(place->streetName, tempP.streetName);
                                strcpy(place->houseNum, tempP.houseNum);
                            }
                            else
                            {
                                strcpy(tempP.streetName, place->streetName);
                                strcpy(tempP.houseNum, place->houseNum);
                            }
                            break;
                        case 3:
                            getHouseNum(tempP.houseNum);

                            if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum))
                            {
                                strcpy(place->houseNum, tempP.houseNum);
                            }
                            else
                            {
                                strcpy(tempP.houseNum, place->houseNum);
                            }
                            break;
                        default:
                            printf("\n\t-Azione per modificare i dati dell'utente interrotta!");
                            break;
                        }
                        break;
                    default:
                        printf("\n\t-Azione per modificare i dati dell'utente interrotta!");
                        break;
                    }
                }

                fprintf(fileCopy, "%s#%s#%s-%s-%s-%s<%s<%s<%s-\n", temp.username, temp.email, temp.pw, temp.name,
                        temp.surname, tempP.city, tempP.streetName, tempP.houseNum, tempP.structure);
            }

            fclose(file);
            fclose(fileCopy);

            remove("Data/ArtGalleryManager.txt");
            rename("Data/CopyArtGallety.txt",
                   "Data/ArtGalleryManager.txt");
        }
    }
}

void delateManager(User *user)
{
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_MANAGER];
    User temp;
    exhiPlace tempP;

    if ((file = fopen(
             "Data/ArtGalleryManager.txt",
             "r")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    }
    else
    {

        if ((fileCopy = fopen(
                 "Data/CopyArtGallety.txt",
                 "w")) ==
            NULL)
        {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        }
        else
        {

            while (fgets(str, MAX_LEN_MANAGER, file) != NULL)
            {
                loadUser(str, &temp);
                loadGallery(NULL, &tempP);

                // Fintanto che l'username preso da file è diverso, dall'utente che vuole cancellare il suo account,
                // allora ricopiami i valori degli altri utenti
                if (strcmp(temp.username, user->username) != 0)
                {
                    fprintf(fileCopy, "%s#%s#%s-%s-%s-%s<%s<%s<%s-\n", temp.username, temp.email, temp.pw,
                            temp.name, temp.surname, tempP.city, tempP.streetName, tempP.houseNum,
                            tempP.structure);
                }
            }
            printf("\n\t-Account cancellato!");

            fclose(file);
            fclose(fileCopy);

            remove("Data/ArtGalleryManager.txt");
            rename("Data/CopyArtGallety.txt",
                   "Data/ArtGalleryManager.txt");

            free(fileCopy);
            free(file);
        }
    }
}

void registerArtwork()
{
    artwork artw;
    FILE *file = NULL;

    getArtwork(&artw);

    // verifica se l'opera è già esistente nel file
    if (!isArtworkAlredyReg(artw.name))
    {
        if ((file = fopen("Data/Artworks.txt", "a")) ==
            NULL)
        {
            printf("\n\t-ATTENZIONE: Non e' stato possibile registrare nel sistema l'opera!");
        }
        else
        {
            fprintf(file, "%u#%s-%s-%s-%u-%s-%s-%u-%u\n", artw.IDArtwork, artw.name, artw.authorName, artw.authorSurname,
                    artw.operaType, artw.kind, artw.historPeriod, artw.prodYear, artw.BC);
            fclose(file);
        }
    }
    else
    {
        printf("\n\t-ATTENZIONE: L'opera e' gia' stata registrata");
    }
}

void recordShow(char *nameStructure)
{
    date timeStart, timeEnd;
    localManager manager;
    unsigned int id;
    char *idArtwork = NULL;
    FILE *file = NULL;

    if ((file = fopen("Data/Artshow.txt", "a")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile registrare la mostra!");
    }
    else
    {
        idArtwork = getShow(&timeStart, &timeEnd, &manager);

        id = getIDShow();
        fprintf(file, "%u#%s#%s#%u/%u/%u#%u/%u/%u#%s\n", id, nameStructure, manager.fiscalCode, timeStart.day,
                timeStart.month,
                timeStart.year, timeEnd.day, timeEnd.month, timeEnd.year, idArtwork);

        free(idArtwork);
        fclose(file);
    }

    if ((file = fopen("Data/Reservations.txt", "a")) ==
        NULL)
    {
        printf("\n\t-ATTENZIONE: Non e' stato possibile registrare la mostra!");
    }
    else
    {

        fprintf(file, "%u#%u#<\n", id, 30);
        fclose(file);
    }
}

bool saveArtGalleyManager(User *user)
{
    bool proposition = true;
    FILE *file = NULL;
    exhiPlace place = {"", "", "", ""};

    getExhiPlace(&place);

    // se la galleria non esiste nel file, allora procedi nel memorizzarla
    if (!isGalleryAlredyReg(place.city, place.streetName, place.houseNum))
    {
        if ((file = fopen(
                 "Data/ArtGalleryManager.txt",
                 "a")) ==
            NULL)
        {
            proposition = false;
            printf("\n\t-ATTENZIONE: Non e' stato possibile registrare l'utente!");
        }
        else
        {

            fprintf(file, "%s#%s#%s-%s-%s-%s<%s<%s<%s-\n", user->username, user->email, user->pw, user->name,
                    user->surname,
                    place.city, place.streetName, place.houseNum, place.structure);
            printf("\n\t-Benvenuto nel sistema %s!", user->name);
            fclose(file);
        }
    }
    else
    {
        printf("\n\t-ATTENZIONE: Esiste gia' una sede della galleria nel luogo specificato!");
    }
    return proposition;
}

bool isGalleryManagAlredyReg(char *userName, char *userEmail, char mode)
{
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_MANAGER], *fUserName = NULL, *fUserEmail = NULL;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL)
    {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    }
    else
    {

        while (fgets(str, MAX_LEN_MANAGER, file) != NULL && proposition == false)
        {
            switch (mode)
            {
            case 'b':
                fUserName = strtok(str, "#");
                fUserEmail = strtok(NULL, "#");

                if (strcmp(fUserName, userName) == 0)
                {
                    proposition = true;
                    printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                }

                if (strcmp(fUserEmail, userEmail) == 0)
                {
                    proposition = true;
                    printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                }
                break;

            case 'u':
                fUserName = strtok(str, "#");

                if (strcmp(fUserName, userName) == 0)
                {
                    proposition = true;
                    printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                }
                break;

            case 'e':
                strtok(str, "#");
                fUserEmail = strtok(NULL, "#");

                if (strcmp(fUserEmail, userEmail) == 0)
                {
                    proposition = true;
                    printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                }
                break;

            default:
                break;
            }
        }
        fclose(file);
    }
    return proposition;
}

bool getManagerLog(User *user, exhiPlace *place, char *uNameORuEmail, char *uPw)
{
    bool proposition = true, pw = false, uNameOrEmail = false, run = true;
    char str[MAX_LEN_MANAGER];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    FILE *file = NULL;
    char *fStreetName = NULL, *fHouseNum = NULL, *fCity = NULL, *fStructure = NULL;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL)
    {
        proposition = NULL;
        printf("\n-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    }
    else
    {

        verif = fgets(str, MAX_LEN_MANAGER, file);

        while (verif != NULL && run)
        {

            fUserUserName = strtok(str, "#");
            fUserEmail = strtok(NULL, "#");
            fUserPw = strtok(NULL, "-");

            // verifica le credenziali inserite
            if (strcmp(fUserUserName, uNameORuEmail) == 0)
            {
                uNameOrEmail = true;
            }

            if (strcmp(fUserEmail, uNameORuEmail) == 0)
            {
                uNameOrEmail = true;
            }

            if (strcmp(fUserPw, uPw) == 0)
            {
                pw = true;
            }

            // se la passoword e l'email/username, vengono ritrovate nel file
            proposition = uNameOrEmail && pw;
            // allora ferma il ciclo
            run = !proposition;

            if (run)
            {
                verif = fgets(str, MAX_LEN_MANAGER, file);
            }
        }

        fclose(file);

        // Se l'utente è stato ritrovato
        if (proposition)
        {
            // carica le informazioni dell'account

            fUserName = strtok(NULL, "-");
            fUserSurname = strtok(NULL, "-");

            fCity = strtok(NULL, "<");
            fStreetName = strtok(NULL, "<");
            fHouseNum = strtok(NULL, "<");
            fStructure = strtok(NULL, "-");

            strcpy(user->name, fUserName);
            strcpy(user->surname, fUserSurname);
            strcpy(user->username, fUserUserName);
            strcpy(user->email, fUserEmail);
            strcpy(user->pw, fUserPw);

            strcpy(place->city, fCity);
            strcpy(place->streetName, fStreetName);
            strcpy(place->houseNum, fHouseNum);
            strcpy(place->structure, fStructure);
        }
    }
    return proposition;
}