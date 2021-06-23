#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include "Users.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "Artgalleymanagers.h"

void registerUser() {
    User user = {"", "", "", "", ""};
    unsigned int choice;

    printf("\n\t-Premi:\n\t\t-1] Per registrarti come utente;\n\t\t"
           "-2] oppure un qualsiasi altro tasto per registrarti come gestore della galleria;\n\t\t-");
    choice = getUInt(10);

    if (choice == 1) {
        user.artGalleryManager = false;
    } else {
        user.artGalleryManager = true;
    }

    getUser(&user);
    if (!isUserAlredyReg(user.username, user.email, 'b', user.artGalleryManager)) {
        saveUser(&user);
    }
}

void getUser(User *user) {
    // Indice utilizzato per emettere eventuali messaggi di errore
    printf("\n# Registrazione utente #\n-Inserisci:");

    getName(user->name);

    getSurname(user->surname);

    getUsername(user->username);

    getEmail(user->email);

    getPw(user->pw);
}

bool saveUser(User *user) {
    bool proposition = true;
    FILE *file = NULL;

    if (!user->artGalleryManager) {
        if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt", "a")) ==
            NULL) {
            proposition = false;
            printf("-ATTENZIONE: Non e' stato possibile registrare l'utente!\n");
        } else {

            fprintf(file, "%s#%s#%s-%s-%s-\n", user->username, user->email, user->pw, user->name, user->surname);
            printf("-Benvenuto nel sistema %s!\n", user->name);
            fclose(file);
            free(file);
        }
    } else {
        proposition = saveArtGalleyManager(user);
    }
    return proposition;
}

bool isUserAlredyReg(char *userName, char *userEmail, char mode, bool userType) {
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_USERS], *fUserName = NULL, *fUserEmail = NULL;

    if (!userType) {
        if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt", "r")) ==
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
            free(fUserName);
            free(fUserEmail);
        }
    } else {
        proposition = isGalleryManagAlredyReg(userName, userEmail, mode);
    }
    return proposition;
}

bool getLog(User *user, exhiPlace *place) {
    bool proposition = true, pw = false, userEmail = false, run = true;
    char uNameORuEmail[80], uPw[50], str[MAX_LEN_USERS];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    int i = 0;
    FILE *file = NULL;

    printf("# Login #\n\t>Email/Username:");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: l'username/email non deve superare gli 80 caratteri, riprova:");
        }
        gets(uNameORuEmail);
        i++;
    } while (strlen(uNameORuEmail) > 80);

    i = 0;

    printf("\n\t>password:");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(uPw);
        i++;
    } while (strlen(uPw) > 50 || strlen(uPw) < 8);
    if (!user->artGalleryManager) {

        if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt", "r")) ==
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

                strcpy(user->name, fUserUserName);
                strcpy(user->surname, fUserSurname);
                strcpy(user->username, fUserUserName);
                strcpy(user->email, fUserEmail);
                strcpy(user->pw, fUserPw);

                free(file);
                free(fUserPw);
                free(fUserEmail);
                free(fUserUserName);
                free(fUserName);
                free(fUserSurname);
                free(verif);
            }
        }
    } else {
        proposition = getManagerLog(user, place, uNameORuEmail, uPw);
    }

    printf("\n");
    return proposition;
}

bool logIn(User *user, exhiPlace *place) {
    bool proposition = false;
    if (!user->artGalleryManager) {
        if ((proposition = getLog(user, NULL))) {
            printf("\n\t-Benevenuto nel sistema!");
        } else {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    } else {
        if ((proposition = getLog(user, place))) {
            printf("\n\t-Benevenuto nel sistema!");
        } else {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    }
    return proposition;
}

void editUser(User *user, exhiPlace *place) {
    unsigned int choice;
    if (!user->artGalleryManager) {
        printf("# Modifica utente #\n\tPremi:\n\t\t-1] Per modificare l'username;\n\t\t-2] Per modifcare l'email;"
               "\n\t\t-3] Per modificare la password;\n\t\t-4] oppure un qualsiasi bottone interrompere la modifica;\n\t-");

        choice = getUInt(10);

        editFile(user, NULL, choice);
    } else {
        printf("# Modifica utente/galleria #\n\tPremi:\n\t\t-1] Per modificare l'username;\n\t\t-2] Per modifcare l'email;"
               "\n\t\t-3] Per modificare la password;\n\t\t-4] Per modificare il posto in cui e' sitauata la galleria;"
               "\n\t\t-5] oppure un qualsiasi bottone interrompere la modifica;\n\t-");

        choice = getUInt(10);

        editFile(user, place, choice);
    }
}

void editFile(User *user, exhiPlace *place, unsigned int choice) {
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    User temp;

    if (!user->artGalleryManager) {
        if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt", "r")) ==
            NULL) {
            printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
        } else {

            if ((fileCopy = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyClient.txt",
                                  "w")) == NULL) {
                printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
            } else {
                // continua fintato che non ci sono più linee nel file
                while (fgets(str, MAX_LEN_USERS, file) != NULL) {

                    loadUser(str, &temp);

                    if (strcmp(temp.username, user->username) == 0) {

                        // a seconda della scelta cambia nell'ordine: username, email, password
                        switch (choice) {
                            case 1:

                                getUsername(temp.username);
                                // deve uscire un messaggio di errore nel momento in cui il valore inserito e già esistente

                                if (!isUserAlredyReg(temp.username, "", 'u', user->artGalleryManager)) {
                                    editRes(user->username, temp.username);
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

                            default:
                                printf("\n\t-Azione per modificare i dati dell'utente interrotta!\n");
                                break;
                        }
                    }

                    fprintf(fileCopy, "%s#%s#%s-%s-%s-\n", temp.username, temp.email, temp.pw, temp.name, temp.surname);
                }

                fclose(file);
                fclose(fileCopy);

                remove("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt");
                rename("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyClient.txt",
                       "C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt");

                free(fileCopy);
                free(file);
            }
        }
    } else {
        editManagerFile(user, place, choice);
    }
}

void delateUser(User *users) {
    char choice;
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    User temp;

    printf("\n\t-ATTENZIONE: stai per eliminare questo account, sei sicuro di procedere?(s/n):\n\t-");
    choice = (char) getch();

    if (toupper(choice) == 'S') {
        if (!users->artGalleryManager) {
            if ((file = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt",
                              "r")) ==
                NULL) {
                printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
            } else {

                if ((fileCopy = fopen(
                        "C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyClient.txt",
                        "w")) ==
                    NULL) {
                    printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
                } else {

                    while (fgets(str, MAX_LEN_USERS, file) != NULL) {
                        loadUser(str, &temp);
                        if (strcmp(temp.username, users->username) != 0) {
                            fprintf(fileCopy, "%s#%s#%s-%s-%s-\n", temp.username, temp.email, temp.pw, temp.name,
                                    temp.surname);
                        }
                    }
                    printf("\n\t-Account cancellato, grazie per aver utilizzato la nostra APP!");

                    fclose(file);
                    fclose(fileCopy);

                    remove("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt");
                    rename("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyClient.txt",
                           "C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Client.txt");

                    free(fileCopy);
                    free(file);
                }
            }
        } else {
            delateManager(users);
        }
    } else {
        printf("\n\t-Cancellazione dell'account annullata.");
    }
}

void getName(char *name) {
    char str[30];
    int i = 0;

    printf("\n\t>Nome (Il nome non deve contenere numeri o spazi, e non deve superare i 30 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il nome inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(name, str);
}

void getSurname(char *surname) {
    char str[30];
    int i = 0;

    printf("\n\t>Cognome (Il cognome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: Il cognome inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(surname, str);
}

void getUsername(char *username) {
    char str[50];
    int i = 0;

    printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) > 50);

    deletespaces(str);
    strcpy(username, str);
}

void getEmail(char *email) {
    char str[80];
    int i = 0;

    printf("\n\t>Email (L'Email non deve superare gli 80 caratteri):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!verifyemail(str) || strlen(str) > 80);

    deletespaces(str);
    strcpy(email, str);
}

void getPw(char *pw) {
    char str[50];
    int i = 0;
    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve almeno\n\tcontenere un numero):");
    do {
        if (i != 0) {
            printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!shaveanumber(str) || (strlen(str) > 50 || strlen(str) < 8));

    deletespaces(str);
    strcpy(pw, str);
}

void bookShow(char *username) {
    printArtworksInShow(6);
    selectArtshow(username);
}

void deleteReservation(char *username) {
    FILE *file = NULL, *fileCopy = NULL;
    char temp[MAX_LEN_SHOW], *ptr = NULL, *usernames = NULL;
    unsigned int id, max, idshow;
    bool ctrl = false;

    if ((file = fopen("Data/Reservations.txt",
                      "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    } else {

        if ((fileCopy = fopen(
                "Data/CopyReservations.txt",
                "w")) ==
            NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {
            printf("\tInserire ID della mostra prenotata da disdire\n\t-");
            idshow = getUInt(10);
            while (fgets(temp, MAX_LEN_SHOW, file)) {

                temp[strlen(temp) - 1] = '\0';

                id = strtol(strtok(temp, "#"), &ptr, 10);
                max = strtol(strtok(NULL, "#"), &ptr, 10);

                if (id == idshow) {
                    if (max < 30) {
                        max++;
                        fprintf(fileCopy, "%u#%u#", id, max);
                        while ((usernames = strtok(NULL, ",")) != NULL) {
                            if (strstr(usernames, "<") == NULL) {
                                if (strstr(username, usernames) == NULL) {
                                    fprintf(fileCopy, "%s,", usernames);
                                    ctrl = true;
                                }
                            }
                        }
                        fprintf(fileCopy, "<\n");
                    } else {
                        printf("\n\t-ATTENZIONE:Errore! Questa mostra non possiede prenotazioni\n");
                        usernames = strtok(NULL, "<");
                        if (usernames != NULL) {
                            fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                        } else {
                            fprintf(fileCopy, "%u#%u#<\n", id, max);
                        }
                    }
                } else {
                    usernames = strtok(NULL, "<");
                    if (usernames != NULL) {
                        fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                    } else {
                        fprintf(fileCopy, "%u#%u#<\n", id, max);
                    }
                }
            }
            fclose(file);
            fclose(fileCopy);
            if (ctrl == true) {
                remove("Data/Reservations.txt");
                rename("Data/CopyReservations.txt",
                       "Data/Reservations.txt");
            } else {
                remove("Data/CopyReservations.txt");
                printf("\nATTENZIONE: Nessuna prenotazione trovata per la mostra selezionata, modifica annullata.\n");
            }
        }
    }
}

void editRes(char *oldUsername, char *newUsername) {
    FILE *oldRes = NULL, *newRes = NULL;
    char str[MAX_LEN_RES], *leftSubs = NULL, *subToReplace = NULL, *rigthSubs = NULL;
    if ((oldRes = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt", "r")) ==
        NULL) {
        printf("-ATTENZIONE: Non e' stato possibile aprire il file!\n");
    } else {
        if ((newRes = fopen("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
                            "w")) == NULL) {
            printf("-ATTENZIONE: Non e' stato possibile aprire il file!\n");
        } else {
            while (fgets(str, MAX_LEN_RES, oldRes) != NULL) {
                if ((subToReplace = strstr(str, oldUsername)) != NULL) {
                    if (*(subToReplace - 1) != '#') {
                        *(subToReplace - 1) = '.';
                        rigthSubs = reversStrtok(subToReplace, ',');
                        leftSubs = strtok(str, ".");
                        fprintf(newRes, "%s,%s,%s", leftSubs, newUsername, rigthSubs);
                    } else {
                        *(subToReplace - 1) = '.';
                        rigthSubs = reversStrtok(subToReplace, ',');
                        leftSubs = strtok(str, ".");
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
    remove("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
    rename("C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
           "C:\\User\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
}