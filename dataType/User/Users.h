#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

#include <stdbool.h>

typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
}Users;

void registerUser();
void getUser(Users* user);
bool saveUser(Users* user);
bool isAlredyReg(char userName[],char userEmail[] , char mode);

// restitutisce vero se l'utente è riuscito ad entrare nel sistema
bool getLog();
bool logIn(Users* user);

// data la stringa presa da file, vengono caricate le informazioni dell'utente
void loadUser(char str[], Users* user);

// Procedura per modificare le credenziali di un utente
void editFile(Users* user, unsigned int choice);
void editUser(bool access, Users* user);

// Procedura per eliminare un utente
void delateUser(bool access, Users* users);

#endif //GALLERIADARTE_USERS_H
