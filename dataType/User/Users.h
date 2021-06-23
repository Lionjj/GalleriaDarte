#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

#include <stdbool.h>
#include "../ArtShow/Artshow.h"
#include <stdio.h>

#define MAX_LEN 240
#define MAX_LEN_USERS 415
#define MAX_LEN_RES 1540

typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
    bool artGalleryManager;
}User;

void registerUser();
void getUser(User* user);

void getName(char* user);
void getSurname(char *surname);
void getUsername(char *username);
void getEmail(char *email);
void getPw(char *pw);

bool saveUser(User* user);
bool isUserAlredyReg(char userName[],char userEmail[] , char mode, bool userType);

// restitutisce vero se l'utente è riuscito ad entrare nel sistema
bool getLog(User* user, exhiPlace* place);
bool logIn(User* user, exhiPlace* place);

// data la stringa presa da file, vengono caricate le informazioni dell'utente
void loadUser(char str[], User* user);

// Procedura per modificare le credenziali di un utente
void editFile(User* user, exhiPlace* place, unsigned int choice);
void editUser(User* user, exhiPlace* place);

// Procedura per eliminare un utente
void delateUser(User* users);

// EffettuaPrenotazione()

// CancellaPrenotazione()
void deleteReservation(char *username);
// RicercaMostra()

// RicercaOpera()
//Procedure di ricerca



void bookShow(char *username);
void editRes(char *oldUsername, char *newUsername);
#endif //GALLERIADARTE_USERS_H
