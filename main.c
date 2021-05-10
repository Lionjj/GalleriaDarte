#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/dataimput.h"
#include "dataType/User/Users.h"


int main()
{
    bool access = false, run = true;
    Users user;
    unsigned int choice;
    printf("# Home #\n\tBenvenuto in *nome del sistema*\n\tPremi:\n\t\t-1] Per registrarti;\n\t\t-2] Per "
           "effettuare il login;\n\t\t-3] Oppure un qualsiasi bottone per uscire dal programma;\n\t-");



    do {

        if(!access)
        {
            choice = getUInt(10);

            switch (choice)
            {
                case 1:
                    registerUser();
                    break;
                case 2:
                    access = logIn(&user);
                    break;
                default:
                    run = false;
                    break;
            }
        } else{
            printf("\n\tPremi:\n\t\t-1] Per prenotare una mostra;\n\t\t-2] Per"
                   " modificare il tuo account;\n\t\t-3] Per eliminare l'account;\n\t\t-4] Per "
                   "chiudere il programma;\n\t-");

            choice = getUInt(10);
            switch (choice)
            {
                case 1:
                    //prenotaMostra();
                    break;
                case 2:
                    editUser(access, &user);
                    break;
                case 3:
                    delateUser(access, &user);
                    access = false;
                    break;
                default:
                    run = false;
                    break;
            }
        }

    } while (run);

    system("PAUSE");
    return 0;
}