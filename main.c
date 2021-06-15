#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/datainput.h"
#include "dataType/User/Users.h"
#include "dataType/User/Artgalleymanagers.h"


int main()
{
    bool access = false, run = true;
    Users user;
    exhiPlace place;
    unsigned int choice;

    printf("Benvenuto in *nome del sistema*");
    do {

        if(!access)
        {
            printf("\n# Home #\n\tPremi:\n\t\t-1] Per registrarti;\n\t\t-2] Per "
                   "effettuare il login;\n\t\t-3] Oppure un qualsiasi bottone per uscire dal programma;\n\t-");
            choice = getUInt(10);


            switch (choice)
            {
                case 1:
                    registerUser();
                    break;
                case 2:
                    printf("\n\tPremi:\n\t\t-1] Per effettuare l'accesso come utente;"
                           "\n\t\t-2] Oppure un qualsiasi bottone per effettuare l'accesso come gestore della galleria;\n\t\t-");

                    choice = getUInt(10);
                    if(choice == 1)
                    {
                        user.artGalleryManager = false;
                        access = logIn(&user, NULL);
                    }else {
                        user.artGalleryManager = true;
                        access = logIn(&user, &place);
                    }
                    break;
                default:
                    run = false;
                    break;
            }
        } else{
            if(!user.artGalleryManager) {
                printf("\n# Utente: %s #\n\tPremi:\n\t\t-1] Per prenotare una mostra;\n\t\t-2] Per"
                       " modificare il tuo account;\n\t\t-3] Per eliminare l'account;\n\t\t-4] Per "
                       "chiudere il programma;\n\t-", user.username);

                choice = getUInt(10);

                switch (choice) {
                    case 1:
                        //prenotaMostra();
                        break;
                    case 2:
                        editUser(&user, NULL);
                        break;
                    case 3:
                        delateUser(&user);
                        access = false;
                        break;
                    default:
                        run = false;
                        break;
                }
            } else{

                printf("\n# Gestore galleria: %s #\n\tPremi:\n\t\t-1] Per registrare una mostra;\n\t\t-2] Per"
                       " modificare il tuo account;\n\t\t-3] Per eliminare l'account;\n\t\t-4] Per aggiungere una nuova opera d'arte;"
                       "\n\t\t-5] Per chiudere il programma;\n\t-", user.username);

                choice = getUInt(10);

                switch (choice) {
                    case 1:
                        recordShow(place.structure);
                        break;
                    case 2:
                        editUser(&user, &place);
                        break;
                    case 3:
                        delateUser(&user);
                        access = false;
                        break;
                    case 4:
                        registerArtwork();
                        break;
                    default:
                        access = false;
                        run = false;
                        break;
                }
            }
        }

    } while (run);

    system("PAUSE");
    return 0;
}