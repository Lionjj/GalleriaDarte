#include "Users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../lib/stringcontrol.h"

void registerUser()
{
    Users user;
    char* ptr;
    printf("# Registrazione utente #\n");

    printf("-Inserisci\n\t>Nome (Il nome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        gets(user.name);
    } while (!sisaspha(user.name) && strlen(user.name) > 30);

    printf("\n\t>Cognome (Il cognome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        gets(user.surname);
    } while (!sisaspha(user.surname) && strlen(user.surname) > 30);

    printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
    do {
        gets(user.username);
    } while (!sisalnum(user.username) && strlen(user.username) > 50);

    printf("\n\t>Email (L'Email non deve superare i 80 caratteri):");
    do {
        gets(user.email);
        ptr = strtok(user.email, "@");
    } while (ptr == NULL && strlen(user.email) > 80);

    printf("\n\t>Email ( non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve contenere alemo un arattere speciale e un numero):");
    do {
        gets(user.pw);
    } while (!shaveanumber(user.pw));

    free(ptr);
}

