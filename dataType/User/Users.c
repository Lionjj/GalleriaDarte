#include "Users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../lib/stringcontrol.h"
#include "../../lib/dataimput.h"

#define MAX_LEN 240

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

    printf("-Inserisci\n\t>Nome (Il nome non deve contenere numeri o spazi, e non deve superare i 30 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: Il nome inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisaspha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(user->name, str);
    i = 0;

    printf("\n\t>Cognome (Il cognome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: Il cognome inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisaspha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(user->surname, str);
    i = 0;

    printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) > 50);

    deletespaces(str);
    strcpy(user->username, str);
    i = 0;

    printf("\n\t>Email (L'Email non deve superare gli 80 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!verifyemail(str) || strlen(str) > 80);

    deletespaces(str);
    strcpy(user->email, str);
    i = 0;

    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve alemo\n\tcontenere un carattere speciale e un numero):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        gets(str);
        i++;
    } while (!shaveanumber(str) || (strlen(str) > 50 || strlen(str) < 8));

    deletespaces(str);
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
        printf("-ATTENZIONE: Non e' stato possibile registrare l'utente!\n");
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
    char str[MAX_LEN], *fUserName = NULL, *fUserEmail= NULL;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) == NULL)
    {
        proposition = NULL;
        printf("-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.\n");
    } else{

        while (fgets(str, MAX_LEN, file) != NULL && proposition == false)
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
        free(fUserName);
        free(fUserEmail);
    }

    return proposition;
}

bool getLog(Users* user)
{
    bool proposition = true, pw = false, userEmail = false, run = true;
    char uNameORuEmail[80], uPw[50], str[MAX_LEN];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    int i = 0;
    FILE* file = NULL;

    printf("# Login #\n\t>Email/Username:");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: l'username/email non deve superare gli 80 caratteri, riprova:");
        gets(uNameORuEmail);
        i++;
    } while (strlen(uNameORuEmail) > 80);

    i = 0;

    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri):");
    do {
        if(i != 0) printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        gets(uPw);
        i++;
    } while (strlen(uPw) > 50 || strlen(uPw) < 8);


    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) == NULL)
    {
        proposition = NULL;
        printf("-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.\n");
    } else{

        verif = fgets(str, MAX_LEN, file);

        while ( verif != NULL && run){

            fUserUserName = strtok(str, "#");
            fUserEmail = strtok(NULL, "#");
            fUserPw = strtok(NULL, "-");


            if (strcmp(fUserUserName, uNameORuEmail) == 0)
            {
                userEmail = true;
            }

            if (strcmp(fUserEmail, uNameORuEmail) == 0)
            {
                userEmail = true;
            }

            if(strcmp(fUserPw, uPw) == 0)
            {
                pw = true;
            }

            proposition = userEmail && pw;
            run = !proposition;

            if(run)
            {
                verif = fgets(str, MAX_LEN, file);
            }
        }

        fclose(file);

        if(proposition)
        {
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

    printf("\n");
    return proposition;
}

bool logIn(Users* user)
{
    bool proposition;
    if((proposition = getLog(user))){
        printf("\t-Benevenuto nel sistema!\n");
    } else{
        printf("\t-ATTENZIONE: Credenziali errate!\n");
    }

    return proposition;
}

void editUser(bool access, Users* user)
{
    unsigned int choice;

    // se si è fatto il login nel sistema allora si potrà procedere
    if(access == false)
    {
        printf("\t-ATTENZIONE: per potere cambiare i dati devi prima effettuare il login.\n");
    } else{

        printf("# Modifica utente #\n\tPremi:\n\t\t-1] Per modificare l'username;\n\t\t-2] Per modifcare l'email;"
               "\n\t\t-3] Per modificare la password;\n\t\t-4] oppure un qualsiasi bottone per uscire dal programma;\n\t-");

        choice = getUInt(10);

        editFile(user, choice);
    }
}

void editFile(Users* user, unsigned int choice)
{
    FILE* file = NULL, *fileCopy = NULL;
    char str[MAX_LEN], newValue[80];
    Users temp;
    int i = 0;


    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) == NULL)
    {
        printf("\t-ATTENZIONE: non è stata possibile effettuare l'operazione!\n");
    } else{

        if((fileCopy = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt", "w")) == NULL)
        {
            printf("\t-ATTENZIONE: non è stato possibile effettuare la copia del file!\n");
        } else{
            // continua fintato che non ci sono più linee nel file
            while (fgets(str, MAX_LEN, file) != NULL)
            {

                loadUser(str, &temp);

                if(strcmp(temp.username, user->username) == 0)
                {

                    // a seconda della scelta cambia nell'ordine: username, email, password
                    switch (choice)
                    {
                        case 1:

                            printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
                            do {
                                if(i != 0) printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova:");
                                gets(newValue);
                                i++;
                            } while (!sisalnum(newValue) || strlen(newValue) > 50);


                            strcpy(temp.username, newValue);
                            break;

                        case 2:

                            printf("\n\t>Email (L'Email non deve superare gli 80 caratteri):");
                            do {
                                if(i != 0) printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
                                gets(newValue);
                                i++;
                            } while (!verifyemail(newValue) || strlen(newValue) > 80);

                            strcpy(temp.email, newValue);
                            break;

                        case 3:

                            printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve alemo\n\tcontenere un carattere speciale e un numero):");
                            do {
                                if(i != 0) printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
                                gets(newValue);
                                i++;
                            } while (!shaveanumber(newValue) || (strlen(newValue) > 50 || strlen(newValue) < 8));

                            strcpy(temp.pw, newValue);
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

            remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");
            rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt", "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");

            free(fileCopy);
            free(file);
        }
    }
}

void loadUser(char str[], Users* user)
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

    free(fUserPw);
    free(fUserEmail);
    free(fUserUserName);
    free(fUserName);
    free(fUserSurname);
}