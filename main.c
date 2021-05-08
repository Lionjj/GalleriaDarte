#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/dataimput.h"
#include "dataType/User/Users.h"


int main()
{
    bool access = false;
    Users user;
    printf("# Home #\n\tBenvenuto in *nome del sistema*\n\tPremi:\n\t\t-1] Per registrarti;\n\t\t-2] Per "
           "effettuare il login;\n\t\t-3] oppure un qualsiasi bottone per uscire dal programma;\n\t-");

    unsigned int choice = getUInt(10);
    switch (choice)
    {
        case 1:
            registerUser();
            break;
        case 2:
            access = logIn(&user);
            break;
        default:
            exit(1);
    }
    editUser(access, &user);

    system("PAUSE");
    return 0;
}