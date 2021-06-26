#include <string.h>
#include <stdlib.h>
#include "Users.h"
#include "../../lib/stringcontrol.h"

void loadUser(char str[], User *user) {
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL;

    fUserUserName = strtok(str, "#");
    fUserEmail = strtok(NULL, "#");
    fUserPw = strtok(NULL, "-");
    fUserName = strtok(NULL, "-");
    fUserSurname = strtok(NULL, "-");

    strcpy(user->name, fUserName);
    strcpy(user->surname, fUserSurname);
    strcpy(user->username, fUserUserName);
    strcpy(user->email, fUserEmail);
    strcpy(user->pw, fUserPw);

    free(fUserPw);
    free(fUserEmail);
    free(fUserUserName);
    free(fUserName);
    free(fUserSurname);
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
                    if (max > 0) {
                        if (usernames != NULL) {
                            if (!isSubStringExist(usernames, newUsername)) {
                                max--;
                                fprintf(fileCopy, "%u#%u#%s%s,<\n", id, max, usernames, newUsername);
                            } else {
                                fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                                printf("\n\t>Hai gia' una prenotazione per questa mostra.");
                            }
                        } else {
                            max--;
                            fprintf(fileCopy, "%u#%u#%s,<\n", id, max, newUsername);
                        }
                    } else {
                        printf("\n\t-ATTENZIONE: ci dispiace ma purtoppo il numero massimo di utenti \n\tpartecipanti a "
                               "questa mostra e' stato raggiunto.");
                        fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                    }
                } else {
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
