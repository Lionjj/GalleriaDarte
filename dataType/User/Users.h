#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

#include <stdbool.h>

typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
}Users;

void registerUser();
void getUser(Users* user);
bool saveUser(Users* user);
bool isAlredyReg(Users* user);
#endif //GALLERIADARTE_USERS_H
