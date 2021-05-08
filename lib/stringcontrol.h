#ifndef GALLERIADARTE_STRINGCONTROL_H
#define GALLERIADARTE_STRINGCONTROL_H

// Funzione booleana utilizzata per verificare se una stringa contiene solo caratteri alfabetici
bool sisaspha(char str[]);

// Funzione booleana utilizzata per verificare se una stringa contiene solo caratteri alfanumerici
bool sisalnum(char str[]);

// Funzione booleana utilizzata per verificare se una stringa contiene alemno un carattere numerico
bool shaveanumber(char str[]);

// Funzione booleana utilizzata per verificare se una stringa contiene alemno un carattere speciale ($, %, &, ...)
bool shaveaspecial(char str[]);

bool verifyemail(char str[]);

bool sisspace(char str[]);

void deletespaces(char str[]);
#endif //GALLERIADARTE_STRINGCONTROL_H
