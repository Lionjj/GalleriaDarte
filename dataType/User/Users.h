#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

#include <stdbool.h>
#include "../ArtShow/Artshow.h"

typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
    bool artGalleryManager;
}Users;

void registerUser();
void getUser(Users* user);

void getNameU(Users* user);
void getSurnameU(Users* user);
void getUsernameU(Users* user);
void getEmailU(Users* user);
void getPwU(Users* user);

bool saveUser(Users* user);
bool isUserAlredyReg(char userName[],char userEmail[] , char mode, bool userType);

// restitutisce vero se l'utente è riuscito ad entrare nel sistema
bool getLog(Users* user, exhiPlace* place);
bool logIn(Users* user, exhiPlace* place);

// data la stringa presa da file, vengono caricate le informazioni dell'utente
void loadUser(char str[], Users* user);

// Procedura per modificare le credenziali di un utente
void editFile(Users* user, exhiPlace* place, unsigned int choice);
void editUser(Users* user, exhiPlace* place);

// Procedura per eliminare un utente
void delateUser(Users* users);

// EffettuaPrenotazione()

// CancellaPrenotazione()

// RicercaMostra()

// RicercaOpera()

#endif //GALLERIADARTE_USERS_H
