#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include "Users.h"
#include "../../lib/stringcontrol.h"
#include "../../lib/datainput.h"
#include "Artgalleymanagers.h"


void registerUser()
{
    Users user = {"", "", "", "", ""};
    unsigned int choice;

    printf("\n\t-Premi:\n\t\t-1] Per registrarti come utente;\n\t\t"
           "-2] oppure un qualsiasi altro tasto per registrarti come gestore della galleria;\n\t\t-");
    choice = getUInt(10);

    if (choice == 1)
    {
        user.artGalleryManager = false;
    }
    else
    {
        user.artGalleryManager = true;
    }

    getUser(&user);
    if (!isUserAlredyReg(user.username, user.email, 'b', user.artGalleryManager))
    {
        saveUser(&user);
    }
}

void getUser(Users *user)
{
    // Indice utilizzato per emettere eventuali messaggi di errore
    printf("\n# Registrazione utente #\n-Inserisci:");

    getName(user->name);

    getSurname(user->surname);

    getUsername(user->username);

    getEmail(user->email);

    getPw(user->pw);
}

bool saveUser(Users *user)
{
    bool proposition = true;
    FILE *file = NULL;

    if (!user->artGalleryManager)
    {
        if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "a")) ==
            NULL)
        {
            proposition = false;
            printf("-ATTENZIONE: Non e' stato possibile registrare l'utente!\n");
        }
        else
        {

            fprintf(file, "%s#%s#%s-%s-%s-\n", user->username, user->email, user->pw, user->name, user->surname);
            printf("-Benvenuto nel sistema %s!\n", user->name);
            fclose(file);
            free(file);
        }
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
    FILE *file = NULL;
    char str[MAX_LEN_USERS], *fUserName = NULL, *fUserEmail = NULL;

    if (!userType)
    {
        if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) ==
            NULL)
        {
            proposition = NULL;
            printf("\n\t-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
        }
        else
        {

            while (fgets(str, MAX_LEN_USERS, file) != NULL && proposition == false)
            {
                switch (mode)
                {
                case 'b':
                    fUserName = strtok(str, "#");
                    fUserEmail = strtok(NULL, "#");

                    if (strcmp(fUserName, userName) == 0)
                    {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                    }

                    if (strcmp(fUserEmail, userEmail) == 0)
                    {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                    }
                    break;

                case 'u':
                    fUserName = strtok(str, "#");

                    if (strcmp(fUserName, userName) == 0)
                    {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: il nome utente scelto e' gia' esistente!");
                    }
                    break;

                case 'e':
                    strtok(str, "#");
                    fUserEmail = strtok(NULL, "#");

                    if (strcmp(fUserEmail, userEmail) == 0)
                    {
                        proposition = true;
                        printf("\n\t-ATTENZIONE: l'email utilizzata e' gia' esistente!");
                    }
                    break;

                default:
                    break;
                }
            }

            fclose(file);

            free(file);
            free(fUserName);
            free(fUserEmail);
        }
    }
    else
    {
        proposition = isGalleryManagAlredyReg(userName, userEmail, mode);
    }
    return proposition;
}

bool getLog(Users *user, exhiPlace *place)
{
    bool proposition = true, pw = false, userEmail = false, run = true;
    char uNameORuEmail[80], uPw[50], str[MAX_LEN_USERS];
    char *fUserUserName = NULL, *fUserEmail = NULL, *fUserPw = NULL, *fUserName = NULL, *fUserSurname = NULL, *verif = NULL;
    int i = 0;
    FILE *file = NULL;

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
    if (!user->artGalleryManager)
    {

        if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) ==
            NULL)
        {
            proposition = NULL;
            printf("\n-ATTENZIONE: Non e' stato possibile aprire il file per la verifica.");
        }
        else
        {

            verif = fgets(str, MAX_LEN_USERS, file);

            while (verif != NULL && run)
            {

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

                if (strcmp(fUserPw, uPw) == 0)
                {
                    pw = true;
                }

                proposition = userEmail && pw;
                run = !proposition;

                if (run)
                {
                    verif = fgets(str, MAX_LEN_USERS, file);
                }
            }

            fclose(file);

            if (proposition)
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
    }
    else
    {
        printf("-%s", user->username);
        proposition = getManagerLog(user, place, uNameORuEmail, uPw);
    }

    printf("\n");
    return proposition;
}

bool logIn(Users *user, exhiPlace *place)
{
    bool proposition = false;
    if (!user->artGalleryManager)
    {
        if ((proposition = getLog(user, NULL)))
        {
            printf("\n\t-Benevenuto nel sistema!");
        }
        else
        {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    }
    else
    {
        if ((proposition = getLog(user, place)))
        {
            printf("\n\t-Benevenuto nel sistema!");
        }
        else
        {
            printf("\n\t-ATTENZIONE: Credenziali errate!");
        }
    }
    return proposition;
}

void editUser(Users *user, exhiPlace *place)
{
    unsigned int choice;
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

void editFile(Users *user, exhiPlace *place, unsigned int choice)
{
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    Users temp;

    if (!user->artGalleryManager)
    {
        if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt", "r")) ==
            NULL)
        {
            printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
        }
        else
        {

            if ((fileCopy = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt",
                                  "w")) == NULL)
            {
                printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
            }
            else
            {
                // continua fintato che non ci sono più linee nel file
                while (fgets(str, MAX_LEN_USERS, file) != NULL)
                {

                    loadUser(str, &temp);

                    if (strcmp(temp.username, user->username) == 0)
                    {

                        // a seconda della scelta cambia nell'ordine: username, email, password
                        switch (choice)
                        {
                        case 1:

                            getUsername(temp.username);

                            // deve uscire un messaggio di errore nel momento in cui il valore inserito e già esistente

                            if (!isUserAlredyReg(temp.username, "", 'u', user->artGalleryManager))
                            {
                                strcpy(user->username, temp.username);
                            }
                            else
                            {
                                strcpy(temp.username, user->username);
                            }
                            break;

                        case 2:

                            getEmail(temp.email);

                            if (!isUserAlredyReg("", temp.email, 'e', user->artGalleryManager))
                            {
                                strcpy(user->email, temp.email);
                            }
                            else
                            {
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

                remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");
                rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt",
                       "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");

                free(fileCopy);
                free(file);
            }
        }
    }
    else
    {
        editManagerFile(user, place, choice);
    }
}

void loadUser(char str[], Users *user)
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

void delateUser(Users *users)
{
    char choice;
    FILE *file = NULL, *fileCopy = NULL;
    char str[MAX_LEN_USERS];
    Users temp;

    printf("\n\t-ATTENZIONE: stai per eliminare questo account, sei sicuro di procedere?(s/n):\n\t-");
    choice = (char)getch();

    if (toupper(choice) == 'S')
    {
        if (!users->artGalleryManager)
        {
            if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt",
                              "r")) ==
                NULL)
            {
                printf("\n\t-ATTENZIONE: non è stata possibile effettuare l'operazione!");
            }
            else
            {

                if ((fileCopy = fopen(
                         "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt",
                         "w")) ==
                    NULL)
                {
                    printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
                }
                else
                {

                    while (fgets(str, MAX_LEN_USERS, file) != NULL)
                    {
                        loadUser(str, &temp);
                        if (strcmp(temp.username, users->username) != 0)
                        {
                            fprintf(fileCopy, "%s#%s#%s-%s-%s-\n", temp.username, temp.email, temp.pw, temp.name,
                                    temp.surname);
                        }
                    }
                    printf("\n\t-Account cancellato, grazie per aver utilizzato la nostra APP!");

                    fclose(file);
                    fclose(fileCopy);

                    remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");
                    rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyUsers.txt",
                           "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Users.txt");

                    free(fileCopy);
                    free(file);
                }
            }
        }
        else
        {
            delateManager(users);
        }
    }
    else
    {
        printf("\n\t-Cancellazione dell'account annullata.");
    }
}

void getName(char *name)
{
    char str[30];
    int i = 0;

    printf("\n\t>Nome (Il nome non deve contenere numeri o spazi, e non deve superare i 30 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il nome inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(name, str);
}

void getSurname(char *surname)
{
    char str[30];
    int i = 0;

    printf("\n\t>Cognome (Il cognome non deve contenere numeri, e non deve superare i 30 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: Il cognome inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalpha(str) || strlen(str) > 30);

    deletespaces(str);
    strcpy(surname, str);
}

void getUsername(char *username)
{
    char str[50];
    int i = 0;

    printf("\n\t>Username (L'Username non deve superare i 50 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: L'username inserito non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!sisalnum(str) || strlen(str) > 50);

    deletespaces(str);
    strcpy(username, str);
}

void getEmail(char *email)
{
    char str[80];
    int i = 0;

    printf("\n\t>Email (L'Email non deve superare gli 80 caratteri):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: L'email inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!verifyemail(str) || strlen(str) > 80);

    deletespaces(str);
    strcpy(email, str);
}

void getPw(char *pw)
{
    char str[50];
    int i = 0;
    printf("\n\t>password (la password non deve superare i 50 caratteri e deve essere di almeno 8 caratteri, inoltre deve alemo\n\tcontenere un carattere speciale e un numero):");
    do
    {
        if (i != 0)
        {
            printf("\n\t-ATTENZIONE: La password inserita non e' conforme con le specifiche richieste, riprova:");
        }
        gets(str);
        i++;
    } while (!shaveanumber(str) || (strlen(str) > 50 || strlen(str) < 8));

    deletespaces(str);
    strcpy(pw, str);
}

void research()
{
    FILE *file = NULL;
    unsigned int choice;
    printf("\n\t>Scegliere criterio di ricerca:\n\t\t-1] Nome opera;\n\t\t-2] Autore opera;"
           "\n\t\t-3] Tipo opera;\n\t\t-4] Genere opera;\n\t\t-5] Periodo storico opera;"
           "\n\t\t-6] Anno produzione opera\n\t-");
    choice = getUInt(10);
    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) == NULL)
    {
        printf("\n\t-ATTENZIONE: non e' stata possibile effettuare l'operazione!");
    }
    else
    {
        switch (choice)
        {
        case 1:

            printf("\n\t-Ricerca tramite nome\n");
            searchName(file);
            break;

        case 2:

            printf("\n\t-Ricerca tramite autore\n");
            searchArtAuthor(file);
            break;

        case 3:

            printf("\n\t-Ricerca tramite tipo di opera\n");
            searchArtType(file);
            break;

        case 4:

            printf("\n\t-Ricerca tramite genere di opera\n");
            searchArtKind(file);
            break;

        case 5:

            printf("\n\t-Ricerca tramite periodo storico\n");
            searchArtHistorPeriod(file);
            break;

        case 6:

            printf("\n\t-Ricerca tramite anno di produzione\n");
            searchArtProdYear(file);
            break;

        default:
            printf("\n\t-Azione di ricerca interrotta!\n");
            break;
        }
        fclose(file);
    }
}

void searchName(FILE *file)
{
    char name[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire nome da ricercare\n\t-");
    gets(name);
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.name, name) != 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtAuthor(FILE *file)
{
    char authorName[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire il nome, il cognome o nome e cognome dell'autore\n\t-");
    gets(authorName);
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strcmp(artwork.authorName, authorName) == 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
        else
        {
            if (strcmp(artwork.authorSurname, authorName) == 0)
            {
                num++;
                printArtwork(num, &artwork);
            }
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtType(FILE *file)
{
    char str[MAX_LEN];
    unsigned int artType;
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire un tipo tra i disponibili:\n\t\t-0] Dipinto;\n\t\t-1] Scultura;\n\t\t-2] Disegno;\n\t-");
    artType = getUInt(10);
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (artwork.operaType == artType)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtKind(FILE *file)
{
    char artKind[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire genere\n\t-");
    gets(artKind);
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.kind, artKind) != 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtHistorPeriod(FILE *file)
{
    char artHistorPeriod[MAX_LEN], str[MAX_LEN];
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo storico (a lettere)\n\t-");
    gets(artHistorPeriod);
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (strstr(artwork.historPeriod, artHistorPeriod) != 0)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void searchArtProdYear(FILE *file)
{
    char str[MAX_LEN];
    int min, max, c;
    artwork artwork;
    int num = 0;
    printf("\n\t>Inserire periodo di produzione");
    printf("\n\t>Primo anno:\n\t-");
    min = getInt(10);
    printf("\n\t>Secondo anno:\n\t-");
    max = getInt(10);
    if (min > max)
    {
        c = min;
        min = max;
        max = c;
    }
    while (fgets(str, MAX_LEN, file) != NULL)
    {
        loadArtwork(str, &artwork);
        if (artwork.prodYear >= min && artwork.prodYear <= max)
        {
            num++;
            printArtwork(num, &artwork);
        }
    }
    printf("\n\t-Numero risultati: %d", num);
}

void loadArtwork(char str[], artwork *artwork)
{

    char *fArtID = NULL, *fArtName = NULL, *fArtAuthorName = NULL, *fArtAuthorSurname = NULL, *fArtKind = NULL, *fhistorPeriod = NULL;
    char *fArtType = NULL;
    char *fArtProdYear = NULL;
    char *fArtBC = NULL;
    char *ptr = NULL;

    fArtID = strtok(str, "#");
    fArtName = strtok(NULL, "-");
    fArtAuthorName = strtok(NULL, "-");
    fArtAuthorSurname = strtok(NULL, "-");
    fArtType = strtok(NULL, "-");
    fArtKind = strtok(NULL, "-");
    fhistorPeriod = strtok(NULL, "-");
    fArtProdYear = strtok(NULL, "-");
    fArtBC = strtok(NULL, "-");

    artwork->IDArtwork = strtol(fArtID, &ptr, 10);
    strcpy(artwork->name, fArtName);
    strcpy(artwork->authorName, fArtAuthorName);
    strcpy(artwork->authorSurname, fArtAuthorSurname);
    artwork->operaType = strtol(fArtType, &ptr, 10);
    strcpy(artwork->kind, fArtKind);
    strcpy(artwork->historPeriod, fhistorPeriod);
    artwork->prodYear = strtol(fArtProdYear, &ptr, 10);
    artwork->BC = strtol(fArtBC, &ptr, 10);

    free(fArtID);
    free(fArtName);
    free(fArtAuthorName);
    free(fArtAuthorSurname);
    free(fArtType);
    free(fArtKind);
    free(fhistorPeriod);
    free(fArtProdYear);
    free(fArtBC);
}

void printArtwork(int num, artwork* artwork)
{
    printf("\n\t-Questo e' il risultato numero %d:\n", num);
    printf("\n\t\t-ID dell'opera d'arte: %d", artwork->IDArtwork);
    printf("\n\t\t-Nome dell'opera d'arte: %s", artwork->name);
    printf("\n\t\t-Nome dell'autore dell'opera d'arte: %s", artwork->authorName);
    printf("\n\t\t-Cognome dell'autore dell'opera d'arte: %s", artwork->authorSurname);
    printf("\n\t\t-Tipo dell'opera d'arte: ");
    switch (artwork->operaType)
    {
    case 0:
        printf("Dipinto");
        break;
    case 1:
        printf("Scultura");
        break;
    case 2:
        printf("Disegno");
        break;
    default:
        printf("Errore nel tipo");
        break;
    }
    printf("\n\t\t-Genere dell'opera d'arte: %s", artwork->kind);
    printf("\n\t\t-Periodo storico dell'opera d'arte: %s", artwork->historPeriod);
    printf("\n\t\t-Anno di produzione dell'opera d'arte: %d", artwork->prodYear);
    if (artwork->BC == true)
    {
        printf(" BC\n");
    }
    else
    {
        printf(" AD\n");
    }
}


void bookShow(char *username)
{

    // printa le mostre disponibili e le opere associate
    selectArtshow(username);
}

unsigned int* fgetIdsArtwork(const unsigned int idArtshow, unsigned int *retDim){
    FILE *file = NULL;
    bool run = true;
    char str[MAX_LEN_SHOW], *ptr = NULL, *temp = NULL;
    unsigned int *idsArtwork = NULL;
    unsigned int id, i = 0, len = 1;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artshow.txt", "r")) == NULL){
        printf("\n\t-ATTENZIONE: non è stato possibile aprire il file per la verifica.");
    } else{
        while (run && fgets(str, MAX_LEN_SHOW, file) != NULL){
            id = strtol(strtok(str, "#"), &ptr, 10);
            if(id == idArtshow){
                run = false;
            }
        }

        strtok(NULL, "#");
        strtok(NULL, "#");
        strtok(NULL, "#");
        strtok(NULL, "#");


        idsArtwork = (unsigned int*) malloc(sizeof (unsigned int));

        while ((temp = strtok(NULL, ",")) != NULL){
            idsArtwork[i] = strtol(temp, &ptr, 10);
            idsArtwork = realloc(idsArtwork, len);

            i++;
            len++;
        }
        fclose(file);
    }
    *retDim = i - 1;

    return idsArtwork;
}

void printAssArtworks(unsigned int idArtshow){
    FILE* file = NULL;
    unsigned int *idsArtwork = NULL;
    unsigned int dim, id;
    char temp[MAX_LEN_SHOW], *ptr = NULL;
    bool run = true;

    if((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Artworks.txt", "r")) == NULL){
        printf("\n\t-ATTENZIONE: non è stato possibile aprire il file per la verifica.");
    } else{

        idsArtwork = fgetIdsArtwork(idArtshow, &dim);

        for (int i = 0; i < dim; ++i) {
            while (run && fgets(temp, MAX_LEN_SHOW, file) != NULL) {
                id = strtol(strtok(temp, "#"), &ptr, 10);
                if (id == idsArtwork[i]) {

                    printf("\n\tNome opera: %s;",strtok(NULL, "-"));
                    printf("\tAutore:%s %s;",strtok(NULL, "-"), strtok(NULL, "-"));

                    run = false;
                }
            }
            run = true;
        }
        free(idsArtwork);
        fclose(file);
    }
}

void selectArtshow(char *username){
    unsigned int choice;

    printf("\n\t-Digita il ID della mostra a cui vuoi registrarti:\n\t-");
    choice = getUInt(10);
    bookUser(choice, username);

}

void bookUser(const unsigned int IDArtshow, char *newUsername){
    FILE *file = NULL, *fileCopy = NULL;
    char temp[MAX_LEN_SHOW], *ptr = NULL, *usernames = NULL;
    unsigned int id, max;

    if ((file = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt", "r")) ==
        NULL){
        printf("-ATTENZIONE: Non e' stato possibile registrarti alla mostra!\n");
    }
    else{
        if ((fileCopy = fopen("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
                              "w")) == NULL){
            printf("\n\t-ATTENZIONE: non è stato possibile effettuare la copia del file!");
        }
        else{
            while (fgets(temp,MAX_LEN_SHOW,file)){

                temp[strlen(temp)-1] = '\0';

                id = strtol(strtok(temp, "#"), &ptr, 10);
                max = strtol(strtok(NULL, "#"), &ptr, 10);
                usernames = strtok(NULL, "<");


                if(id == IDArtshow){

                    if(max > 0){
                        max--;
                        if(usernames != NULL){
                            fprintf(fileCopy, "%u#%u#%s%s,<\n", id, max, usernames, newUsername);
                        } else{
                            fprintf(fileCopy, "%u#%u#%s,<\n", id, max, newUsername);
                        }

                    } else{
                        printf("\n\t-ATTENZIONE: ci dispiace ma purtoppo il numero massimo di utenti \n\tpartecipanti a "
                               "questa mostra e' stato raggiunto.");
                    }
                } else{
                    if(usernames != NULL){
                        fprintf(fileCopy, "%u#%u#%s<\n", id, max, usernames);
                    } else{
                        fprintf(fileCopy, "%u#%u#<\n", id, max);
                    }
                }
            }
            fclose(fileCopy);
        }
        fclose(file);

        remove("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
        rename("C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\CopyReservations.txt",
               "C:\\Users\\iMuSL\\CLionProjects\\GalleriaDarte\\GalleriaDarte\\Data\\Reservations.txt");
    }
}