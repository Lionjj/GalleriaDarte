#ifndef GALLERIADARTE_CLIENT_H
#define GALLERIADARTE_CLIENT_H

/**
 * Numero massimo di caratteri che una stringa può contenere nel file Client.txt
 */
#define MAX_LEN_CLIENT 240

/**
 * \file GalleriaDarte.dataType.Users.Client.h
 * \defgroup clientOperation Operazioni di un utente client
 *
 * \addtogroup clientOperation
 * @{
 */

#include <stdbool.h>
#include "Users.h"

/**
 * Tale procedura permette ad un utente client di modificare i prorpi dati.
 * Sulla base della scelta effettuata, rappresentata da choice, l'utente portà modificare:
 *
 * -il suo username
 * -la sua e-mail
 * -la sua password
 *
 * \sa editRes(char *oldUsername, char *newUsername)
 *
 * @param[in,out] *user	puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente client
 * @param[in] choice intero senza segno rappresentante la scelta dell'utente
 */
void editClientFile(User *user, unsigned int choice);

/**
 * Tale procedura permette ad un utente client di effettuare l'operazione di eliminazione dell'account.
 *
 * \pre Il parametro user deve essere essere caricati estrapolando le informazioni memorizzate su ArtGalleyManager.txt
 * \pre altrimenti il corretto funziomaneto della procedura non è garantito.
 *
 * @param[in] *User puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente client
 */
void delateClient(User *User);

/**
 * Tale procedura viene utilizzata per permette ad un utente di registrarsi ad una mostra.
 *
 * \pre Se il parametro username è NULL il corretto funzionamento della procedura non è garantito
 *
 * @param[in] *username	stringa rappresentante l'username di un utente client
 */
void bookShow(char *username);

/**
 * Tale procedura permette di disdire la prenotazione di un utente client ad una mostra.
 *
 * \pre Se il parametro username è NULL il corretto funzionamento della procedura non è garantito
 * @param[in] *username stringa rappresentante l'username di un utente client
 */
void deleteReservation(char *username);
/** @}*/

/**
 * \defgroup implicitClientOperation Operazioni di un utente client
 *
 * \addtogroup implicitClientOperation Operazioni implicite per l'utente client
 * @{
 */
/**
 * Tale procedura permette di memorizzare l'utente client, tramite il suo username alla mostra il cui identificativo è
 * rappresentanto da IDArtshow.
 *
 * @param[in] IDArtshow intero senza segno rappresentante l'identificarivo di una mostra
 * @param[in] *newUsername stringa rappresentante l'username di un utente client
 */
void bookClient(unsigned int IDArtshow, char *newUsername);

/**
 * Tale funzione permette di memorizzare le informazioni contenute in user nel file Client.txt.
 *
 * @param [in] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente client
 * @return true se l'operazione di memorizzazione dell'utente client è avvenuta con successo, falso altriementi.
 */
bool saveClient(User *user);

/**
 * Tale Funzione ha il compito di verificare se, dato l'username, l'email o entrambi i valori, essi esistno nel file
 * Client.txt.
 *
 * \note Il parametro mode può assumere tre simboli, 'b' nel caso il controllo debba essere fatto sia sull'e-mail sia
 * \note su l'username; 'u' nel caso il controllo venga fatto sull'usename, e in questo caso il parametro userEmail può
 * \note essere NULL; 'e' nel caso il controllo venga fatto sull'e-mail, e in questo caso il parametro userName può
 * \note essere NULL. In tutti i casi in cui mode non assume uno di questi caratteri, la funzione effettuer alcuna
 * \note operazione.
 *
 *
 * @param[in] *userName stringa rappresentante l'username di un utente client
 * @param[in] *userEmail stringa rappresentante l'e-mail di un utente client
 * @param[in]mode carattere, tipo di controllo che la funzione deve effettuare
 * @return true se l'utente client è già registrato nel file Client.txt falso altriemtni
 */
bool isClientAlredyReg(char *userName, char *userEmail, char mode);

/**
 * Tale funzione permette di verificare se le credenziali uNameORuEmail e uPw, rispettivamente username/e-mail e
 * passowrd corrispodnono con quelle estrapolate da Client.txt, se si, allora la struttura user viene caricata con i
 * valori estrapolati dal file.
 *
 * @param[out] *user punatore ad una struttura di tipo User, contente le informaizoni di un utente client
 * @param[in] *uNameORuEmail stringa rappresentante l'username o l'e-mail dell'utente client
 * @param[in] *uPw stringa rappresentante la password del utente client
 * @return true se l'utente esiste nel sistema, falso altrimenti
 */
bool getClientLog(User *user, char *uNameORuEmail, char *uPw);
/** @}*/
#endif //GALLERIADARTE_CLIENT_H
