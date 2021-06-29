#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include "Users.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "Artgallerymanagers.h"
#include "Client.h"
#include "../../lib/search.h"
#include "../../dataType/ArtShow/Artshow.h"

void registerUser()
{
    User user = {"", "", "", "", ""};
    unsigned int choice;

    printf("# Registrazione utente #\n\t-Premi:\n\t\t-1] Per registrarti come utente;\n\t\t"
           "-2] oppure un qualsiasi altro tasto per registrarti come gestore della galleria;\n\t-");
    choice = getUInt(10);

    if (choice == 1)
    {
        user.artGalleryManager = false;
    }
    else
    {
        user.artGalleryManager = true;
    }

    // prendi le informazioni dell'utente
    getUser(&user);

    // se le informazioni dell'utente non esistno nel sistema
    if (!isUserAlredyReg(user.username, user.email, 'b', user.artGalleryManager))
    {
        // salva il nuovo utente nel sistema
        saveUser(&user);
    }
}

void editUser(User *user, exhiPlace *place)
{
    unsigned int choice;

    // se non è un account, gestore della galleria
    if (!user->artGalleryManager)
    {
        printf("# Modifica utente #\n\tPremi:\n\t\t-1] Per modificare l'username;\n\t\t-2] Per modifcare l'email;"
               "\n\t\t-3] Per modificare la password;\n\t\t-4] oppure un qualsiasi bottone interrompere la modifica;\n\t-");

        choice = getUInt(10);

        editFile(user, NULL, choice);
    }
    else
    {
        printf("# Modifica utente/galleria #\n\tPremi:\n\t\t-1] Per modificare l'username;\n\t\t-2] Per modifcare l'email;"
               "\n\t\t-3] Per modificare la password;\n\t\t-4] Per modificare il posto in cui e' sitauata la galleria;"
               "\n\t\t-5] oppure un qualsiasi bottone interrompere la modifica;\n\t-");

        choice = getUInt(10);

        editFile(user, place, choice);
    }
}

void delateUser(User *user)
{
    char choice;

    printf("\n\t-ATTENZIONE: stai per eliminare questo account, sei sicuro di procedere?(S/N):\n\t-");
    choice = (char)getchar();
    fflush(stdin);
    // se legge "S" in input procede con l'eliminazione dell'account
    if (toupper(choice) == 'S')
    {
        if (!user->artGalleryManager)
        {
            delateClient(user);
        }
        else
        {
            delateManager(user);
        }
    }
    else
    {
        printf("\n\t-Cancellazione dell'account annullata.");
    }
}

bool logIn(User *user, exhiPlace *place)
{
    bool proposition = false;

    // se non è un account, gestore della galleria
    if (!user->artGalleryManager)
    {

        // se le credenziali per il login sono corrette
        if ((proposition = getLog(user, NULL)))
        {
            // accedi come utente client
            printf("\n\t-Benevenuto nel sistema!");
        }
        else
        {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    }
    else
    {
        // se le credenziali per il login sono corrette
        if ((proposition = getLog(user, place)))
        {
            // accedi come utente manager
            printf("\n\t-Benevenuto nel sistema!");
        }
        else
        {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    }
    return proposition;
}

void getUser(User *user)
{
    // Indice utilizzato per emettere eventuali messaggi di errore
    printf("\n# Registrazione utente #\n\t-Inserisci:");

    getName(user->name);

    getSurname(user->surname);

    getUsername(user->username);

    getEmail(user->email);

    getPw(user->pw);
}

void getName(char *name)
{
    char str[30], *str2 = NULL;
    int i = 0;

    printf("\n\t>Nome (Il nome non deve contenere numeri o spazi e deve essere compreso tra 4 caratteri e 30 caratteri): ");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il nome inserito non e' conforme con le specifiche richieste, riprova: ");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30 || strlen(str) < 4);

    str2 = deletespaces(str);
    strcpy(name, str2);
}

void getSurname(char *surname)
{
    char str[30], *str2 = NULL;
    int i = 0;

    printf("\n\t>Cognome (Il cognome non deve contenere numeri e deve essere compreso tra 4 caratteri e 30 caratteri): ");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il cognome inserito non e' conforme con le specifiche richieste, riprova: ");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30 || strlen(str) < 4);

    str2 = deletespaces(str);
    strcpy(surname, str2);
}

void getUsername(char *username)
{
    char str[50], *str2 = NULL;
    int i = 0;

    printf("\n\t>Username (L'Username deve essere compreso tra 8 caratteri e 50 caratteri.): ");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova: ");
        }
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) > 50 || strlen(str) < 8);

    str2 = deletespaces(str);
    strcpy(username, str2);
}

void getEmail(char *email)
{
    char str[80], *str2 = NULL;
    int i = 0;

    printf("\n\t>Email (L'Email non deve superare gli 80 caratteri, avere 1 \"@\", i valori dopo la \"@\" devono essere\n\t\tdi tipo alfabetico e deve essere presente almeno un \".\" ): ");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!verifyemail(str) || strlen(str) > 80);

    str2 = deletespaces(str);
    strcpy(email, str2);
}

void getPw(char *pw)
{
    char str[50], *str2 = NULL;
    int i = 0;
    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve almeno\n\tcontenere un numero):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!shaveanumber(str) || (strlen(str) > 50 || strlen(str) < 8));

    str2 = deletespaces(str);
    strcpy(pw, str2);
}

void loadUser(char str[], User *user)
{
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
}

void editFile(User *user, exhiPlace *place, unsigned int choice)
{
    // se non è un account, gestore della galleria
    if (!user->artGalleryManager)
    {
        editClientFile(user, choice);
    }
    else
    {
        editManagerFile(user, place, choice);
    }
}

bool saveUser(User *user)
{
    bool proposition = true;

    // se non è un account, gestore della galleria
    if (!user->artGalleryManager)
    {
        proposition = saveClient(user);
    }
    else
    {
        proposition = saveArtGalleyManager(user);
    }
    return proposition;
}

bool isUserAlredyReg(char *userName, char *userEmail, char mode, bool userType)
{
    bool proposition = false;

    // se non è un account, gestore della galleria
    if (!userType)
    {
        proposition = isClientAlredyReg(userName, userEmail, mode);
    }
    else
    {
        proposition = isGalleryManagAlredyReg(userName, userEmail, mode);
    }
    return proposition;
}

bool getLog(User *user, exhiPlace *place)
{
    bool proposition = true;
    char uNameORuEmail[80], uPw[50];
    int i = 0;
    printf("# Login #\n\t>Email/Username:");

    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: l'username/email non deve superare gli 80 caratteri, riprova:");
        }
        gets(uNameORuEmail);
        i++;
    } while (strlen(uNameORuEmail) > 80);

    i = 0;

    printf("\n\t>password:");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(uPw);
        i++;
    } while (strlen(uPw) > 50 || strlen(uPw) < 8);

    // se non è un account, gestore della galleria
    if (!user->artGalleryManager)
    {
        proposition = getClientLog(user, uNameORuEmail, uPw);
    }
    else
    {
        proposition = getManagerLog(user, place, uNameORuEmail, uPw);
    }

    printf("\n");
    return proposition;
}