#ifndef GALLERIADARTE_STRINGCONTROL_H
#define GALLERIADARTE_STRINGCONTROL_H
/**
 * \file GalleriaDarte.lib.stringcontrol.h
 * \defgroup serviceFunctionsStr Funzioni di servizio su stringhe
 * \addtogroup serviceFunctionsStr
 * @{
 */
#include <stdbool.h>
#include <stdio.h>
/**
 * Tale funzione è utilizzata per verificare se la stringa str contiente solo caratteri alfabetici.
 *
 * \sa isalpha(int c);
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è composta da soli caratteri alfabetici, false altrimenti
 */
bool sisalpha(char *str);

/**
 * Funzione utilizzata per verificare se una stringa contiene solo caratteri alfanumerici
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è composta da soli caratteri alfanumerici, false altrimenti
 */
bool sisalnum(char str[]);

/**
 * Funzione utilizzata per verificare se una stringa contiene solo caratteri numerici
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è composta da soli numeri, false altrimenti
 */
bool sisdigit(char* str);

/**
 * Funzione utilizzata per verificare se una stringa contiene almeno un carattere numerico
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è composta da almeno un numero, false altrimenti
 */
bool shaveanumber(char str[]);

/**
 * Tale funzione verifica se la stringa str, è strutturata in maniera tale da poter far riferimento ad una ipotetica
 * e-mail esistente.
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è strutturata in maniera tale che possa far riferimento ad un e-mail, false altrimenti
 */
bool verifyemail(char str[]);

/**
 * Procedura che elimina dalla stringa str eventuali spazi
 *
 * @param[in,out] str[]: stringa generica
 * @return un puntatore ad una stringa senza spazi
 */
char* deletespaces(char str[]);

/**
 * Procedura che converte tutti i caratteri minuscoli in caratteri maiuscoli
 *
 * @param[in,out] str[]: stringa generica
 */
void stoupper(char str[]);

/**
 * Tale funzione si occupa di separare ogni elemento del vettore arr con una virgola.
 *
 * @param[in] *arr: vettore di interi senza segno
 * @param[in] dim: dimensione del vettore
 * @return un vettore di caratteri dove ogni valore è separato da una virgola
 */
char* separateWithComma(unsigned int* arr, unsigned int dim);

/**
 * Tale funzione lavora in modo simile alla funzione strtock(), ma, invece che, restituire un puntatore alla stringa
 * precedente ad un determinato simbolo, restituisce un puntatore alla sottostringa successiva a quel simbolo.
 *
 * \sa strtok(char *str, const char *delim)
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @param[in] symbol: carattere utilizzato per dividere la stringa
 * @return un puntatore alla sottostringa che viene dopo il carattere symbol
 */
char* reversStrtok(char *str, char symbol);

/**
 * Tale funzione è utilizzata per verificare l'esistenza della sottostringa subStr, nella stringa str
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @param[in] *subStr: puntatore alla stringa da ricercare
 * @return True se la sottostringa esiste, false altrimenti
 */
bool isSubStringExist(char *str, const char *subStr);

/**
 * Tale funzione conta il numero di righe che il file possiede
 *
 * @param[in] *file: puntatore ad un file generico
 * @param[in] MAX_LENG: valore intero rappresentante il massimo numero di caratteri che una stringa del file può avere
 * @return il numero di righe presenti nel file
 */
unsigned int lineOfFile(FILE *file, int MAX_LENG);

/**
 * Tale funzione è utilizzata per verificare se la stringa str contiente solo caratteri alfabetici o spazi bianchi.
 *
 * \sa isalpha(int c);
 * \sa isspace(int c);
 *
 * @param[in] *str: puntatore ad una stringa generica
 * @return true se la stringa è composta da soli caratteri alfabetici o spazi bianchi, false altrimenti
 */
bool sisalphaandspace(char *str);

/**
 * Procedura che elimina dalla stringa str eventuali spazi iniziali e finali
 *
 * @param[in,out] str[]: stringa generica
 * @return un puntatore ad una stringa senza spazi iniziali e finali
 */
char *trimwhitespace(char *str);
/**@}*/
#endif //GALLERIADARTE_STRINGCONTROL_H
