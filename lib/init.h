#ifndef GALLERIADARTE_INIT_H
#define GALLERIADARTE_INIT_H

#include <stdbool.h>
#include "../dataType/Users/Users.h"
/**
 * Procedura utilizzata per inizializare le funzionalità di base del programma
 *
 * \sa home(User *user, exhiPlace *place, bool *access)
 *
 * \sa managerOperation(User *user, exhiPlace *place, bool *access)
 *
 * \sa clientOperation(User *user, bool *access)
 *
 */
void init();

/**
 * Funzione coordinatrice utilizzata per permettere ad un'utente client di operare nel sistema.
 *
 * \sa bookShow(char *username)
 *
 * \sa editUser(User *user, exhiPlace *place)
 *
 * \sa delateUser(User *user)
 *
 * \sa research()
 *
 * \sa deleteReservation(char *username)
 *
 * @param *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente client
 * @param *access valore booleano rappresentante l'accesso di un utente al sistema
 * @return true se l'utente vuol continuare ad operare nel sistema, false altrimeti
 */
bool clientOperation(User *user, bool *access);

/**
 * Funzione coordinatrice utilizzata per permettere ad un'utente manager di operare nel sistema.
 *
 * \sa recordShow(char *nameStructure
 *
 * \sa editUser(User *user, exhiPlace *place)
 *
 * \sa delateUser(User *user)
 *
 * \sa research()
 *
 * \sa registerArtwork()
 *
 * @param *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente manager
 * @param *place puntatore ad una struttura di tipo exhiPlace, contenette le informazioni della struttura gestita dal
 * manager
 * @param *access valore booleano rappresentante l'accesso di un utente al sistema
 * @return true se l'utente vuol continuare ad operare nel sistema, false altrimeti
 */
bool managerOperation(User *user, exhiPlace *place, bool *access);

/**
 * Funzione utilizzata per permettere ad un utente di effettuare operazione nel sistema prima dell'accesso:
 *
 * - registrarsi
 * - effettuare il login
 * - terminare il programma
 *
 * \sa logIn(User *user, exhiPlace *place)
 *
 * \sa registerUser()
 *
 * @param *user puntatore ad una struttura di tipo User, utilizzata per contenere le informazioni di un generico utente
 * @param *place puntatore ad una stringa che conterrà il nome della città in cui è situata la struttura
 * @param *access valore booleano rappresentante l'accesso di un utente al sistema
 * @return true se l'utente vuol continuare ad operare nel sistema, false altrimeti
 */
bool home(User *user, exhiPlace *place, bool *access);
#endif //GALLERIADARTE_INIT_H
