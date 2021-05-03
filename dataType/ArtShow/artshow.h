#ifndef GALLERIADARTE_ARTSHOW_H
#define GALLERIADARTE_ARTSHOW_H

#include <stdbool.h>

typedef struct
{
    char streetName[90];
    char houseNum[5];
    char city[30];
    char structure[50];
    unsigned int paintingsNumb;
    unsigned int sculpturesNumb;
}exhiPlace;

typedef struct{
    unsigned int day;
    unsigned int month;
    unsigned int year;
}exposure;

typedef struct
{
    char name[30];
    char surname[30];
    char fiscalCode[16];
    char IDResponsible[6];
}loacaManager;


enum operaType {painting, sculpture, drawing };

typedef struct
{
    char name[100];
    char authorName[30];
    char authorSurname[30];
    enum operaType operaType;
    char kind [30];
    char historPeriod[30];
    unsigned int prodYear;
    bool BC;
}artwork;

bool tempExhibition;

unsigned int sizeShows;

unsigned int codeShows;

#endif //GALLERIADARTE_ARTSHOW_H
