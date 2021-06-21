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
}Users;

void registerUser();
void getUser(Users* user);

void getName(char* user);
void getSurname(char *surname);
void getUsername(char *username);
void getEmail(char *email);
void getPw(char *pw);

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
//Procedure di ricerca
void research();
void searchName(FILE* file);
void searchArtAuthor(FILE* file);
void searchArtType(FILE* file);
void searchArtKind(FILE* file);
void searchArtHistorPeriod(FILE* file);
void searchArtProdYear(FILE* file);
void assArtshow(unsigned int id);


void printArtwork(int num, artwork* artwork);
unsigned int* fgetIdsArtwork(unsigned int idArtshow, unsigned int *retDim);
void printAssArtworks(unsigned int idArtshow);
void bookUser(unsigned int IDArtshow, char *newUsername);
void selectArtshow(char *username);
void bookShow(char *username);
#endif //GALLERIADARTE_USERS_H
