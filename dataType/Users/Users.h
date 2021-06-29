#ifndef GALLERIADARTE_USERS_H
#define GALLERIADARTE_USERS_H

#include <stdbool.h>
#include "../ArtShow/Artshow.h"
#include <stdio.h>

/**
 * Lunghezza massima che una stringa estrapolata dal file Reservations.txt può avere.
 */
#define MAX_LEN_RES 1540
/**
 * \file GalleriaDarte.dataType.Users.Users.h
 * \struct Users "../GalleriaDarte/dataType/Users/User.h"
 */
typedef struct
{
    char name[30];
    char surname[30];
    char username[50];
    char email[80];
    char pw [50];
    bool artGalleryManager;
}User;
/**
 * \defgroup userOperations Operazioni di un utente generico
 * \addtogroup userOperations
 * @{
 */
/**
 * Tale procedura permette di registrarsi al sistema.
 * Permettendo al nuovo utente di registrarsi o come utente manager o come utente Client.
 *
 * \sa saveUser(User* user)
 *
 * \sa isUserAlredyReg(char userName[], char userEmail[], char mode, bool userType)
 */
void registerUser();

/**
 * Tale procedura viene utilizzata per modificare le informazioni dell'utente, sia nella struttre che nei file.
 *
 * \sa editFile(User* user, exhiPlace* place, unsigned int choice)
 *
 * \pre Nel caso di modifica di un utente manager, se parametri user e place siano NULL non è garantito il corretto
 * \pre funzionamento della procedura. Nel caso di modifica di un utente client allora è necessario che il parametro
 * \pre user non sia NULL, altrimenti non è garantito il corretto funzionamento della procedura.
 *
 * \note Se le modifiche vengono effettuate su un utente client, allora il parametro place può essere NULL.
 *
 * @param[in,out] *user	puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 * @param[in,out] *place puntatore ad una struttura di tipo exhiPlace rappresentante una sede della galleria
 */
void editUser(User* user, exhiPlace* place);

/**
 * Modulo coordinatoria permette di eliminare l'utente rappresentato dal parametro user dal sistema.
 *
 * \sa delateClient(User *user)
 *
 * \sa delateManager(User *user)
 *
 * @param[in] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 */
void delateUser(User* user);

/**
 * Tale funzione permette ad un utente di effettuare il log-in nel sistema utilizzando le sue credenziali, caricando le
 * informazioni dell'utente in user e nel caso sia un utente manager caricando le informazioni rigardanti il luogo
 * in place. Tali informazioni sono estrapolate dai file ArtGalleryManager.txt oppure da Client.txt.
 *
 * \sa getLog(User* user, exhiPlace* place)
 *
 * \note Nel caso in cui l'utente dovesse specificare che stia effettuando l'accesso come utente client allora il
 * \note parametro place può anche essere NULL.
 *
 * @param[out] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 * @param[out] *place puntatore ad una struttura di tipo exhiPlace rappresentante una sede della galleria
 * @return true l'utente è effettivamente riuscito ad accedere al sistema, falso altrimenti
 */
bool logIn(User* user, exhiPlace* place);
/** @}*/

/**
 * \defgroup implicitUserOperations Operazioni implicite di un utente generico
 * \addtogroup implicitUserOperations
 * @{
 */

/**
 * Modulo coordinatore utilizzato per caricare una struttura di tipo User con le informazioni iserite dall'utente.
 *
 * \pre Tutte le evenutali informazioni precedentemente contenute nel parametro user, andranno perse una volta che questa
 * \pre procedura verrà richiamata.
 *
 * \sa getName(char* user)
 * \sa getSurname(char *surname)
 * \sa getUsername(char *username)
 * \sa getEmail(char *email)
 * \sa getPw(char *pw)
 *
 * @param[out]	*user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 */
void getUser(User* user);

/**
 * Tale procedura viene utilizzata per permettere all'utente di inserire il proprio nome.
 *
 * \pre se il parametro name dovesse avere in precedenza un valore, esso verrà perso.
 *
 * @param[out] *name stringa a cui verrà assegnato il nome di un utente
 */
void getName(char* user);

/**
 * Tale procedura viene utilizzata per permettere all'utente di inserire il proprio cognome.
 *
 * \pre se il parametro surname dovesse avere in precedenza un valore, esso verrà perso.
 *
 * @param surname
 */
void getSurname(char *surname);

/**
 * Tale procedura viene utilizzata per permettere all'utente di inserire il proprio username.
 *
 * \pre se il parametro username dovesse avere in precedenza un valore, esso verrà perso.
 *
 * @param *username	stringa a cui verrà assegnato l'username di un utente
 */
void getUsername(char *username);

/**
 * Tale procedura viene utilizzata per permettere all'utente di inserire la propria e-mail.
 *
 * \pre se il parametro email dovesse avere in precedenza un valore, esso verrà perso.
 *
 * @param email
 */
void getEmail(char *email);

/**
 * Tale procedura viene utilizzata per permettere all'utente di inserire la propria password.
 *
 * \pre se il parametro pw dovesse avere in precedenza un valore, esso verrà perso.
 *
 * @param[out] *pw stringa a cui verrà assegnato la password di un utente
 */
void getPw(char *pw);

/**
 * Tale procedura permette di caricare le informazioni estrapolate dalla stringa str nella struttura user.
 *
 * \pre Tutte le evenutali informazioni precedenti contenute nel parametro user, andranno perse una volta che questa
 * \pre procedura verrà richiamata. Inoltre nel caso in cui la stringa str, non sia una righa del file Client.txt
 * \pre oppure di ArtGalleryManager.txt, il corretto funzionamento della procedura non è garantito.
 *
 * @param[in] str[]	stringa contenente le informazioni di un utente
 * @param[out] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 */
void loadUser(char str[], User* user);

/**
 * Modulo coordinatorio utilizzata per modificare le informazioni relative o ad un utente Client o ad un utente Manager
 * richiamando rispettivamente le procedure:
 *
 * \sa editClientFile(User *user, unsigned int choice)
 *
 * \sa editManagerFile(User *user, exhiPlace *place, unsigned int choice)
 *
 * \pre Nel caso in cui tale procedura dovesse essere utilizzata per modificare le informazioni di un cliente, allora
 * \pre il parametro place può essere NULL
 *
 * @param[in,out] *user	puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 * @param[in,out] *place puntatore ad una struttura di tipo exhiPlace rappresentante una sede della galleria
 * @param[in] choice intero senza segno rappresentante la scelta dell'utente
 */
void editFile(User* user, exhiPlace* place, unsigned int choice);

/**
 * Funzione coordinatoria utilizzata per memorizzare nel sistema un generico utente.
 *
 * \sa saveClient(User *user)
 *
 * \sa saveArtGalleyManager(User *user)
 *
 * @param[in] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 * @return True se l'operazione di scrittura delle informazioni di user sui file è avvenuta con successo, falso
 * altrimenti
 */
bool saveUser(User* user);

/**
 * Tale funzione coordinatoria viene utilizzata per verificare se nel sistema esista già un'utente con e-mail e username
 * coincidenti con i parametri userName e userEmail.
 *
 * @param userName[] stringa rappresentante l'username di un utente generico
 * @param userEmail[] stringa rappresentante l'e-mail di un utente generico
 * @param mode carattere, tipo di controllo che la funzione deve effettuare
 * @param userType valore boolean , esso specifica se l'utente è un utente client o manager
 * @return true se esiste nel sistema, false altrimenti
 */
bool isUserAlredyReg(char userName[],char userEmail[] , char mode, bool userType);

/**
 * Tale funzione coordinatoria permette ad un utente di inserire le proprie credenziali dell'account, dopo di chè verifica 
 * se tale account esiste nel sistema. A seconda che si tratti di un account manager o client.
 *
 * \sa getClientLog(User *user, char uNameORuEmail[], char uPw[])
 *
 * \sa getManagerLog(User *user, exhiPlace *place, char *uNameORuEmail, char *uPw)
 *
 * @param[in] *user puntatore ad una struttura di tipo User, rappresentante le informazioni di un utente generico
 * @param[in] *place puntatore ad una struttura di tipo exhiPlace rappresentante una sede della galleria
 * @return true se le credenziali che ll'utente ha inserito esistono nel sistema, falso altrimenti
 */
bool getLog(User* user, exhiPlace* place);
/** @}*/
#endif //GALLERIADARTE_USERS_H
