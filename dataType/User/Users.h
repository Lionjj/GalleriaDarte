#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
}Users;

void registerUser();
#endif //GALLERIADARTE_USERS_H
