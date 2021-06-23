#ifndef GALLERIADARTE_STRINGCONTROL_H
#define GALLERIADARTE_STRINGCONTROL_H

// Funzione booleana utilizzata per verificare se una stringa contiene solo caratteri alfabetici
#include <stdio.h>

bool sisalpha(char *str);

// Funzione booleana utilizzata per verificare se una stringa contiene solo caratteri alfanumerici
bool sisalnum(char str[]);

bool sisdigit(char* str);

// Funzione booleana utilizzata per verificare se una stringa contiene alemno un carattere numerico
bool shaveanumber(char str[]);

bool verifyemail(char str[]);

bool sisspace(char str[]);

void deletespaces(char str[]);

void stoupper(char str[]);

char* separateWithComma(unsigned int* arr, unsigned int dim);
char* reversStrtok(char *str, char symbol);
bool isSubStringExist(char *str, const char *subStr);
unsigned int lineOfFile(FILE *file, int MAX_LENG);

unsigned int fgetIdsArtwork(unsigned int idArtshow, unsigned int idsArtwork[]);

#endif //GALLERIADARTE_STRINGCONTROL_H
