#include <stdbool.h>
#include <stdio.h>
#include "../dataType/User/Users.h"
#include "datainput.h"
#include "../dataType/User/Artgalleymanagers.h"
#include "../lib/init.h"
#include "search.h"

void init() {
    bool access = false, run = true;
    User user;
    exhiPlace place;

    listenerTimeExpired();

    printf("Benvenuto in *nome del sistema*");
    do {
        if (!access) {
            run = home(&user, &place, &access);

        } else {
            if (!user.artGalleryManager) {
                run = userOperation(&user, &access);

            } else {
                run = managerOperation(&user, &place, &access);

            }
        }
    } while (run);
}

bool userOperation(User *user, bool *access) {
    unsigned int choice;
    bool run = true;

    printf("\n# Utente: %s #\n\tPremi:\n\t\t-1] Per prenotare una mostra;\n\t\t-2] Per"
           " modificare il tuo account;\n\t\t-3] Per eliminare l'account;\n\t\t-4] Per ricercare un'opera;\n\t\t-5] Per disdire una prenotazione\n\t\t-6] Per "
           "chiudere il programma;\n\t-", user->username);

    choice = getUInt(10);

    switch (choice) {
        case 1:
            bookShow(user->username);
            break;
        case 2:
            editUser(user, NULL);
            break;
        case 3:
            delateUser(user);
            *access = false;
            break;
        case 4:
            research();
            break;
        case 5:
            deleteReservation(user->username);
            break;
        default:
            run = false;
            break;
    }
    return run;
}

bool managerOperation(User *user, exhiPlace *place, bool *access) {
    unsigned int choice;
    bool run = true;

    printf("\n# Gestore galleria: %s #\n\tPremi:\n\t\t-1] Per registrare una mostra;\n\t\t-2] Per"
           " modificare il tuo account;\n\t\t-3] Per eliminare l'account;\n\t\t-4] Per ricercrare un'opera;\n\t\t-5] Per aggiungere una nuova opera d'arte;"
           "\n\t\t-6] Per chiudere il programma;\n\t-", user->username);

    choice = getUInt(10);

    switch (choice) {
        case 1:
            recordShow(place->structure);
            break;
        case 2:
            editUser(user, place);
            break;
        case 3:
            delateUser(user);
            *access = false;
            break;
        case 4:
            research();
            break;
        case 5:
            registerArtwork();
            break;
        default:
            access = false;
            run = false;
            break;
    }
    return run;
}

bool home(User *user, exhiPlace *place, bool *access) {
    unsigned int choice;
    bool run = true;

    printf("\n# Home #\n\tPremi:\n\t\t-1] Per registrarti;\n\t\t-2] Per "
           "effettuare il login;\n\t\t-3] Oppure un qualsiasi bottone per uscire dal programma;\n\t-");
    choice = getUInt(10);


    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            printf("\n\tPremi:\n\t\t-1] Per effettuare l'accesso come utente;"
                   "\n\t\t-2] Oppure un qualsiasi bottone per effettuare l'accesso come gestore della galleria;\n\t\t-");

            choice = getUInt(10);
            if (choice == 1) {
                user->artGalleryManager = false;
                *access = logIn(user, NULL);
            } else {
                user->artGalleryManager = true;
                *access = logIn(user, place);
            }
            break;
        default:
            run = false;
            break;
    }
    return run;
}