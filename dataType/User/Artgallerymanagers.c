#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ArtShow/Artshow.h"
#include "Users.h"
#include "../../lib/datainput.h"
#include "Artgalleymanagers.h"

#define MAX_LEN_USERS 415

bool saveArtGalleyManager(Users *user) {
    bool proposition = true;
    FILE *file = NULL;
    exhiPlace place = {"", "", "", ""};

    getExhiPlace(&place);

    if (!isGalleryAlredyReg(place.city, place.streetName, place.houseNum)) {
        if ((file = fopen(
                "Data/ArtGalleryManager.txt",
                "a")) ==
            NULL) {
            proposition = false;
            printf("\n\t-ATTENZIONE: Non e' stato possibile registrare l'utente!");
        } else {

            fprintf(file, "%s#%s#%s-%s-%s-%s<%s<%s<%s-\n", user->username, user->email, user->pw, user->name,
                    user->surname,
                    place.city, place.streetName, place.houseNum, place.structure);
            printf("\n-Benvenuto nel sistema %s!", user->name);
            fclose(file);
        }
    }else {
        printf("\n\t-ATTENZIONE: Non e' stato possibile registrare l'utente!\n");
    }
    return proposition;
}

bool isGalleryManagAlredyReg(char *userName, char *userEmail, char mode){
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_USERS], *fUserName = NULL, *fUserEmail = NULL;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL) {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        while (fgets(str, MAX_LEN_USERS, file) != NULL && proposition == false) {
            switch (mode) {
                case 'b':
                    fUserName = strtok(str, "#");
                    fUserEmail = strtok(NULL, "#");

                    if (strcmp(fUserName, userName) == 0) {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                    }

                    if (strcmp(fUserEmail, userEmail) == 0) {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                    }
                    break;

                case 'u':
                    fUserName = strtok(str, "#");

                    if (strcmp(fUserName, userName) == 0) {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                    }
                    break;

                case 'e':
                    strtok(str, "#");
                    fUserEmail = strtok(NULL, "#");

                    if (strcmp(fUserEmail, userEmail) == 0) {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                    }
                    break;

                default:
                    break;
            }
        }
        fclose(file);

        free(file);
    }
    return proposition;
}

bool getManagerLog(Users *user, exhiPlace *place, char *uNameORuEmail, char * uPw){
    bool proposition = true, pw = false, userEmail = false, run = true;
    char str[MAX_LEN_USERS];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    FILE *file = NULL;
    char *fStreetName = NULL, *fHouseNum = NULL, *fCity = NULL, *fStructure = NULL;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL) {
        proposition = NULL;
        printf("\n-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        verif = fgets(str, MAX_LEN_USERS, file);


        while (verif != NULL && run) {

            fUserUserName = strtok(str, "#");
            fUserEmail = strtok(NULL, "#");
            fUserPw = strtok(NULL, "-");

            if (strcmp(fUserUserName, uNameORuEmail) == 0) {
                userEmail = true;
            }

            if (strcmp(fUserEmail, uNameORuEmail) == 0) {
                userEmail = true;
            }

            if (strcmp(fUserPw, uPw) == 0) {
                pw = true;
            }

            proposition = userEmail && pw;
            run = !proposition;

            if (run) {
                verif = fgets(str, MAX_LEN_USERS, file);
            }
        }

        fclose(file);

        if (proposition) {
            fUserName = strtok(NULL, "-");
            fUserSurname = strtok(NULL, "-");

            fCity = strtok(NULL, "<");
            fStreetName = strtok(NULL, "<");
            fHouseNum = strtok(NULL, "<");
            fStructure = strtok(NULL, "-");

            strcpy(user->name, fUserUserName);
            strcpy(user->surname, fUserSurname);
            strcpy(user->username, fUserUserName);
            strcpy(user->email, fUserEmail);
            strcpy(user->pw, fUserPw);

            strcpy(place->city, fCity);
            strcpy(place->streetName, fStreetName);
            strcpy(place->houseNum, fHouseNum);
            strcpy(place->structure, fStructure);

            free(file);
            free(fUserPw);
            free(fUserEmail);
            free(fUserUserName);
            free(fUserName);
            free(fUserSurname);
            free(verif);
        }
    }
    return proposition;
}

void editManagerFile(Users *user, exhiPlace *place, unsigned int choice){
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    Users temp;
    exhiPlace tempP;

    if ((file = fopen("Data/ArtGalleryManager.txt",
                      "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    } else {
        if ((fileCopy = fopen(
                "Data/CopyArtGallety.txt",
                "w")) == NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {
            // continua fintato che non ci sono più linee nel file
            while (fgets(str, MAX_LEN_USERS, file) != NULL) {

                loadUser(str, &temp);
                loadGallery(NULL, &tempP);

                if (strcmp(temp.username, user->username) == 0) {

                    // a seconda della scelta cambia nell'ordine: username, email, password
                    switch (choice) {
                        case 1:

                            getUsername(temp.username);

                            if (!isUserAlredyReg(temp.username, "", 'u', user->artGalleryManager)) {
                                strcpy(user->username, temp.username);
                            } else {
                                strcpy(temp.username, user->username);
                            }
                            break;

                        case 2:

                            getEmail(temp.email);

                            if (!isUserAlredyReg("", temp.email, 'e', user->artGalleryManager)) {
                                strcpy(user->email, temp.email);
                            } else {
                                strcpy(temp.email, user->email);
                            }
                            break;

                        case 3:

                            getPw(temp.pw);

                            strcpy(user->pw, temp.pw);

                            break;

                        case 4:
                            printf("\n\tPremi:\n\t\t-1] Per modificare la citta';\n\t\t-2] Per modificare la via;"
                                   "\n\t\t-3] Per modificare il numero civico;\n\t\t-4] oppure un qualsiasi bottone interrompere la modifica;\n\t-");

                            choice = getUInt(10);

                            switch (choice) {
                                case 1:
                                    getCity(tempP.city);

                                    getStreet(tempP.streetName);

                                    getHouseNum(tempP.houseNum);

                                    if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum)) {
                                        strcpy(place->city, tempP.city);
                                        strcpy(place->streetName, tempP.streetName);
                                        strcpy(place->houseNum, tempP.houseNum);
                                    } else {
                                        strcpy(tempP.city, place->city);
                                        strcpy(tempP.streetName, place->streetName);
                                        strcpy(tempP.houseNum, place->houseNum);
                                    }
                                    break;
                                case 2:
                                    getStreet(tempP.streetName);

                                    getHouseNum(tempP.houseNum);

                                    if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum)) {
                                        strcpy(place->streetName, tempP.streetName);
                                        strcpy(place->houseNum, tempP.houseNum);
                                    } else {
                                        strcpy(tempP.streetName, place->streetName);
                                        strcpy(tempP.houseNum, place->houseNum);
                                    }
                                    break;
                                case 3:
                                    getHouseNum(tempP.houseNum);

                                    if (!isGalleryAlredyReg(tempP.city, tempP.streetName, tempP.houseNum)) {
                                        strcpy(place->houseNum, tempP.houseNum);
                                    } else {
                                        strcpy(tempP.houseNum, place->houseNum);
                                    }
                                    break;
                                default:
                                    printf("\n\t-Azione per modificare i dati dell'utente interrotta!\n");
                                    break;
                            }
                            break;
                        default:
                            printf("\n\t-Azione per modificare i dati dell'utente interrotta!\n");
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

            free(fileCopy);
            free(file);
        }
    }
}

void delateManager(Users *users){
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    Users temp;

    if ((file = fopen(
            "Data/ArtGalleryManager.txt",
            "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");

    } else {

        exhiPlace tempP;

        if ((fileCopy = fopen(
                "Data/CopyArtGallety.txt",
                "w")) ==
            NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {

            while (fgets(str, MAX_LEN_USERS, file) != NULL) {
                loadUser(str, &temp);
                loadGallery(NULL, &tempP);
                if (strcmp(temp.username, users->username) != 0) {
                    fprintf(fileCopy, "%s#%s#%s-%s-%s-%s<%s<%s<%s-\n", temp.username, temp.email, temp.pw,
                            temp.name, temp.surname, tempP.city, tempP.streetName, tempP.houseNum,
                            tempP.structure);
                }
            }
            printf("\n\t-Account cancellato, grazie per aver utilizzato la nostra APP!");

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

void recordShow(char* nameStructure){
    date timeStart, timeEnd;
    localManager manager;
    unsigned int id;
    char* idArtwork = NULL;
    FILE* file = NULL;

    if((file = fopen("Data/Artshow.txt", "a")) == NULL){
        printf("\n-ATTENZIONE: Non e' stato possibile registrare la mostra!");
    }else{
        idArtwork = getShow(&timeStart, &timeEnd, &manager);

        id = getIDShow();

        fprintf(file, "%u#%s#%s#%u/%u/%u#%u/%u/%u#%s\n",id, nameStructure, manager.fiscalCode, timeStart.day, timeStart.month,
                timeStart.year, timeEnd.day, timeEnd.month, timeEnd.year, idArtwork);

        free(idArtwork);
        fclose(file);
    }

    if((file = fopen("Data/Reservations.txt", "a")) == NULL){
        printf("\n-ATTENZIONE: Non e' stato possibile registrare la mostra!");
    }else{

        fprintf(file, "%u#\n",id);
        fclose(file);
    }
}

void registerArtwork(){
    artwork artw;
    FILE* file = NULL;

    getArtwork(&artw);

    // verifica se l'opera è già esistente nel file
    if((file = fopen("Data/Artworks.txt", "a")) == NULL){
        printf("-ATTENZIONE: Non e' stato possibile registrare nel sistema l'opera!\n");
    } else{
        fprintf(file, "%u#%s-%s-%s-%u-%s-%s-%u-%u\n", artw.IDArtwork, artw.name, artw.authorName, artw.authorSurname,
                artw.operaType, artw.kind, artw.historPeriod, artw.prodYear, artw.BC);
        fclose(file);
    }
}
