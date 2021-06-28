#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Users.h"
#include "Client.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "../../lib/search.h"
#include "../ArtShow/Artshow.h"

void editClientFile(User *user, unsigned int choice){
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_CLIENT];
    User temp;

    if ((file = fopen("Data/Client.txt", "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    } else {

        if ((fileCopy = fopen("Data/CopyClient.txt",
                              "w")) == NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {
            // continua fintato che non ci sono più linee nel file
            while (fgets(str, MAX_LEN_CLIENT, file) != NULL) {

                loadUser(str, &temp);

                if (strcmp(temp.username, user->username) == 0) {

                    // a seconda della scelta, nell'ordine, è possibile modificare: username, email, password
                    switch (choice) {
                        case 1:

                            getUsername(temp.username);

                            // se l'username dell'utente non esiste già fra quelli registrati
                            if (!isUserAlredyReg(temp.username, "", 'u', user->artGalleryManager)) {

                                // allora modifica le prenotazioni fatte a nome del vecchio username, combaindolo con
                                // quello nuovo
                                editRes(user->username, temp.username);

                                // cambia l'username precedente dell'utente che è connesso al sistema, con il nuovo
                                // username scelto
                                strcpy(user->username, temp.username);

                            } else {

                                // reimposta il precedente username
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

            remove("Data/Client.txt");
            rename("Data/CopyClient.txt",
                   "Data/Client.txt");
        }
    }
}

void delateClient(User *user){
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_CLIENT];
    User temp;

    if ((file = fopen("Data/Client.txt",
                      "r")) ==
        NULL) {
        printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
    } else {

        if ((fileCopy = fopen(
                "Data/CopyClient.txt",
                "w")) ==
            NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {

            // finche è possibile recuperare dal file una riga
            while (fgets(str, MAX_LEN_CLIENT, file) != NULL) {
                loadUser(str, &temp);

                // confronta l'username recuperato dal file, con l'username dell'utente che è attualmente connesso
                // nel caso non i valori non corrispondano
                if (strcmp(temp.username, user->username) != 0) {
                    // allora memorizza ricopia tutte le informazioni nel nuovo file
                    fprintf(fileCopy, "%s#%s#%s-%s-%s-\n", temp.username, temp.email, temp.pw, temp.name,
                            temp.surname);
                }
            }
            printf("\n\t-Account cancellato, grazie per aver utilizzato la nostra APP!");

            fclose(file);
            fclose(fileCopy);

            remove("Data/Client.txt");
            rename("Data/CopyClient.txt",
                   "Data/Client.txt");
        }
    }
}

 void bookShow(char *username) {
    unsigned int choice, i = 0;
    bool fileArtshow = true;
    do {
        printf("\n\t>Inserire \"1\" per avviare una ricerca tramite nome delle mostre disponibili\n\t>Inserire \"2\" per visualizzare in modo compatto tutte le mostre nel sistema\n");
        choice = getUInt(10);
        switch (choice)
        {
        case 1:
            searchShowName();
            break;
        case 2:
            printShow();
            break;
        default:
            printf("\n\t-ATTENZIONE: Inserire un valore tra quelli disponibili.");
            break;
        }
    } while(choice < 1 || choice > 2);

    do {
        if(i > 0)
        {
            printf("\n\t-ATTENZIONE: ID inserito non esistente!");
        }
        printf("\n\t>Inserire ID della mostra desiderata per vedere le opere associate:\n\t-");
        choice = getUInt(10);
        i=1;
        } while(!IDExists(choice, fileArtshow));
        printArtworksInShow(choice);
        printf("\n\t>Vuoi registrarti a questa mostra? (S/N):\n\t-");
        if(toupper(getchar()) == 'S') 
        {
            bookClient(choice, username);
        }
        fflush(stdin);
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

void bookClient(const unsigned int IDArtshow, char *newUsername) {
    FILE *file = NULL, *fileCopy = NULL;
    char temp[MAX_LEN_SHOW], *ptr = NULL, *usernames = NULL;
    unsigned int id, max;

    if ((file = fopen("Data/Reservations.txt", "r")) ==
        NULL) {
        printf("-ATTENZIONE: Non e' stato possibile registrarti alla mostra!\n");
    } else {
        if ((fileCopy = fopen(
                "Data/CopyReservations.txt",
                "w")) == NULL) {
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        } else {
            while (fgets(temp, MAX_LEN_SHOW, file)) {

                temp[strlen(temp) - 1] = '\0';

                id = strtoul(strtok(temp, "#"), &ptr, 10);
                max = strtoul(strtok(NULL, "#"), &ptr, 10);
                usernames = strtok(NULL, "<");

                if (id == IDArtshow) {

                    // se ci sono ancora posti per la mostra
                    if (max > 0) {

                        // se ci sono altri utenti che hanno effettuato la prenotazione
                        if (usernames != NULL) {

                            // verifica se l'utente che sta prenotando la mostra, non abbia già una prenotazione per la
                            // stessa
                            if (!isSubStringExist(usernames, newUsername)) {

                                // nel caso non abbia già una prenotazione, decrementa di 1 i posti disponibili per la
                                // mostra
                                max--;

                                // memorizza il nuovo utente
                                fprintf(fileCopy, "%u#%u#%s%s,<\n", id, max, usernames, newUsername);
                            } else {

                                // altrimenti ricopia nel nuovo file le restanti righe
                                fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                                printf("\n\t>Hai gia' una prenotazione per questa mostra.");
                            }
                        } else {

                            // Nel caso l'utente sia il primo a registrarsi alla mostra, decrementa di 1 il numero di
                            // posti disponibili e salva e memorizza l'utente
                            max--;
                            fprintf(fileCopy, "%u#%u#%s,<\n", id, max, newUsername);
                        }
                    } else {

                        // nel caso in cui i posti alla mostra siano finiti, allora l'utente non potra effettuare la prenotazione
                        printf("\n\t-ATTENZIONE: ci dispiace ma purtoppo il numero massimo di utenti \n\tpartecipanti a "
                               "questa mostra e' stato raggiunto.");
                        fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                    }
                } else {
                    // nel caso in cui la mostra non sia quella specificata dall'utente copia nel nuovo file le
                    // informazioni presenti nel vecchio file
                    if (usernames != NULL) {
                        fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                    } else {
                        fprintf(fileCopy, "%u#%u#<\n", id, max);
                    }
                }
            }
            fclose(fileCopy);
        }
        fclose(file);

        remove("Data/Reservations.txt");
        rename("Data/CopyReservations.txt",
               "Data/Reservations.txt");
    }
}

bool saveClient(User *user){
    bool proposition = true;
    FILE *file = NULL;

    if ((file = fopen("Data/Client.txt", "a")) ==
        NULL) {
        proposition = false;
        printf("-ATTENZIONE: Non e' stato possibile registrare l'utente!\n");
    } else {

        fprintf(file, "%s#%s#%s-%s-%s-\n", user->username, user->email, user->pw, user->name, user->surname);
        printf("-Benvenuto nel sistema %s!\n", user->name);
        fclose(file);
        free(file);
    }
    return proposition;
}

bool isClientAlredyReg(char *userName, char *userEmail, char mode){
    bool proposition = false;
    FILE *file = NULL;
    char str[MAX_LEN_CLIENT], *fUserName = NULL, *fUserEmail = NULL;


    if ((file = fopen("Data/Client.txt", "r")) ==
        NULL) {
        proposition = NULL;
        printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        while (fgets(str, MAX_LEN_CLIENT, file) != NULL && proposition == false) {
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
    }

    return proposition;
}

bool getClientLog(User *user, char uNameORuEmail[], char uPw[]){
    bool proposition = true, pw = false, userEmail = false, run = true;
    char str[MAX_LEN_CLIENT];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    FILE *file = NULL;

    if ((file = fopen("Data/Client.txt", "r")) ==
        NULL) {
        proposition = NULL;
        printf("\n-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
    } else {

        verif = fgets(str, MAX_LEN_CLIENT, file);

        while (verif != NULL && run) {

            fUserUserName = strtok(str, "#");
            fUserEmail = strtok(NULL, "#");
            fUserPw = strtok(NULL, "-");

            // verifica le credenziali inserite
            if (strcmp(fUserUserName, uNameORuEmail) == 0) {
                userEmail = true;
            }

            if (strcmp(fUserEmail, uNameORuEmail) == 0) {
                userEmail = true;
            }

            if (strcmp(fUserPw, uPw) == 0) {
                pw = true;
            }

            // se la passoword e l'email/username, vengono ritrovate nel file
            proposition = userEmail && pw;
            // allora ferma il ciclo
            run = !proposition;

            if (run) {
                verif = fgets(str, MAX_LEN_CLIENT, file);
            }
        }

        fclose(file);

        // Se l'utente è stato ritrovato
        if (proposition) {
            // carica le informazioni dell'account
            fUserName = strtok(NULL, "-");
            fUserSurname = strtok(NULL, "-");

            strcpy(user->name, fUserName);
            strcpy(user->surname, fUserSurname);
            strcpy(user->username, fUserUserName);
            strcpy(user->email, fUserEmail);
            strcpy(user->pw, fUserPw);
        }
    }
    return proposition;
}