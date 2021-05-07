#include "Users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../lib/stringcontrol.h"

void registerUser()
{
    Users user = {"","", "", "", ""};
    getUser(&user);
    puts(user.name);
    puts(user.surname);
    puts(user.email);
    puts(user.pw);
    puts(user.username);
    if(!isAlredyReg(&user)) saveUser(&user);

}

void getUser(Users* user)
{
    char* ptr = NULL, str[80];
    int i = 0; // Indice utilizzato per emettere eventuali messaggi di errore
    printf("# Registrazione utente #\n");

    printf("-Inserisci\n\t>Nome (Il nome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: Il nome inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisaspha(str) || strlen(str) > 30);

    strcpy(user->name, str);
    i = 0;

    printf("\n\t>Cognome (Il cognome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: Il cognome inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisaspha(str) || strlen(str) > 30);

    strcpy(user->surname, str);
    i = 0;

    printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) > 50);

    strcpy(user->username, str);
    i = 0;

    printf("\n\t>Email (L'Email non deve superare gli 80 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!verifyemail(str) || strlen(str) > 80);

    strcpy(user->email, str);
    i = 0;

    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve alemo\n\tcontenere un carattere speciale e un numero):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!shaveanumber(str) || strlen(str) > 50);

    strcpy(user->pw, str);

    free(ptr);
}

bool saveUser(Users* user)
{
    bool proposition = true;
    FILE *file = NULL;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "a")) == NULL)
    {
        proposition = false;
        printf("-ATTENZIONE: Non è stato possibile registrare l'utente!\n");
    } else{

        fprintf(file, "%s#%s#%s-%s-%s-\n", user->username, user->email, user->pw, user->name, user->surname);
        printf("-Benvenuto nel sistema %s!\n", user->name);
        fclose(file);
        free(file);
    }
    return proposition;
}

bool isAlredyReg(Users* user)
{
    bool proposition = false;
    FILE *file = NULL;
    char str[240], *fUserName = NULL, *fUserEmail= NULL;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) == NULL)
    {
        proposition = NULL;
        printf("-ATTENZIONE: Non è stato possibile aprire il file per la verifica.\n");
    } else{

        while (fgets(str, 240, file) != NULL && proposition == false)
        {
            fUserName = strtok(str, "#");
            fUserEmail = strtok(NULL, "#");

            if(strcmp(fUserName, user->username) == 0)
            {
                proposition = true;
                printf("-ATTENZIONE: il nome utente scelto e' gia' esistente!\n");
            }

            if(strcmp(fUserEmail, user->email) == 0)
            {
                proposition = true;
                printf("-ATTENZIONE: l'email utilizzata e' gia' esistente!\n");
            }
        }

        fclose(file);
        free(file);
    }

    return proposition;
}
