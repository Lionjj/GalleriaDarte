#include <stdio.h>
#include <stdlib.h>
#include "Reservations.h"
#include "../User/Users.h"

void reserve(Users* user)
{
    FILE* file = NULL;
    Reservation newRes;

    if((file = fopen("Data/Reservations.txt", "a")) == NULL)
    {
        printf("\n\t-ATTENZIONE: non è stato possibile effettuare la prenotazione!");
    } else{
        // newRes.IDExhibition =  getIdMostra();
        // mostraDate(&newRes); mostra le date disponibile per quella mostra, dopodiche carica la nuova prenotazione con la data desiderata dall'utente

       //  fprintf(file, "%d-%struct-%s",newRes.IDExhibition, newRes.giornoDesiderato, user->username);

        fclose(file);
        free(file);
    }
}