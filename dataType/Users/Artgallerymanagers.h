#ifndef GALLERIADARTE_ARTGALLERYMANAGERS_H
#define GALLERIADARTE_ARTGALLERYMANAGERS_H

/**
 * Numero massimo di caratteri che una stringa può contenere nel file ArtGalleryManager.txt
 */
#define MAX_LEN_MANAGER  415

/**
 * \file GalleriaDarte.dataType.Users.Artgallerymanagers.h
 * \defgroup managerOperations Operazioni dell'utente manager
 * \addtogroup managerOperations
 *@{*/

/**
 * Tale procedura permette ad un utente manager di modificare i prorpi dati e quelli della struttura che egli gestisce.
 * Sulla base della scelta effettuata, rappresentata da choice, l'utente portà modificare:
 *
 * - il suo username
 * - la sua e-mail
 * - la sua password
 * - la citta della struttura
 * - la via della struttura
 * - il numero civico della struttura
 *
 * \pre I parametri user e place, devono essere caricati estrapolando le informazioni memorizzate su
 * \pre ArtGalleyManager.txt altrimenti il corretto funziomaneto della procedura non è garantito.
 *
 * @param[in,out] *user: punatore ad una struttura di tipo User, contente le informaizoni di un utente manager
 * @param[in,out] *place: puntatore ad una struttura di tipo exhiPlace, contenette le informazioni della struttura
 * gestita dal manager
 * @param[in] choice: intero senza segno rappresentante la decisione dell'utente
 */
void editManagerFile(User *user, exhiPlace *place, unsigned int choice);

/**
 * Tale procedura permette ad un utente mangaer di eliminare il propio account ArtGalleyManager.txt.
 *
 * \pre Il parametro user deve essere essere caricati estrapolando le informazioni memorizzate su ArtGalleyManager.txt
 * \pre altrimenti il corretto funziomaneto della procedura non è garantito.
 *
 * @param[in] *user: punatore ad una struttura di tipo User, contente le informaizoni di un utente manager
 */
void delateManager(User *user);

/**
 * Procedura che permette all'utente managere di registrare una nuova opera d'arte e memorizzando le su informazioni in
 * Artworks.txt
 */
void registerArtwork();

/**
 * Tale procedura permette ad un utente manager di creare una nuova mostra, salvando le informazioni che inserirà
 * in Artshow.txt
 *
 * @param[in] *nameStructure: stringa rappresentante il nome della struttura in cui si terrà la mostra
 */
void recordShow(char* nameStructure);
/**@}*/

/**
 * \defgroup implictManagerOperations Operazioni implicite per l'utente manager
 * \addtogroup implictManagerOperations
 *@{*/

/**
 * Tale funzione permette di memorizzare le informazioni contenute nel parametro user, in ArtGalleryManger.txt
 *
 * @param[in] *user: punatore ad una struttura di tipo User, contente le informaizoni di un utente manager
 * @return True se è stato possibile registrare un nuovo utente manager in ArtGalleryManger.txt, falso altrimenti
 */
bool saveArtGalleyManager(User *user);

/**
 * Tale Funzione ha il compito di verificare se, dato l'username, l'email o entrambi i valori, essi esistno nel file
 * ArtGalleryManager.txt.
 *
 * \note Il parametro mode può assumere tre simboli, 'b' nel caso il controllo debba essere fatto sia sull'e-mail sia
 * \note su l'username; 'u' nel caso il controllo venga fatto sull'usename, e in questo caso il parametro userEmail può
 * \note essere NULL; 'e' nel caso il controllo venga fatto sull'e-mail, e in questo caso il parametro userName può
 * \note essere NULL. In tutti i casi in cui mode non assume uno di questi caratteri, la funzione effettuer alcuna
 * \note operazione.
 *
 * @param[in] *userName: stringa rappresentante l'username del manager
 * @param[in] *userEmail: stringa rappresentante l'e-mail del manager
 * @param[in] mode: tipo di controllo da effettuare
 * @return True se l'usenrmae, l'e-mail o entrambi, a seconda del mode, esistono in ArtGalleyManager.txt, false
 * altrimenti
 */
bool isGalleryManagAlredyReg(char *userName, char *userEmail, char mode);

/**
 * Tale funzione permette di verificare se le credenziali uNameORuEmail e uPw, rispettivamente username/e-mail e
 * passowrd corrispodnono con quelle estrapolate da ArtGalleryManager.txt, se si, allora la struttura user, e place
 * vengono caricate con i valori estrapolati dal file.
 *
 * @param[out] *user: punatore ad una struttura di tipo User, contente le informaizoni di un utente manager
 * @param[out] *place: puntatore ad una struttura di tipo exhiPlace, contenette le informazioni della struttura gestita
 * dal manager
 * @param[in] *uNameORuEmail: stringa rappresentante l'username o l'e-mail dell'utente manager
 * @param[in] *uPw: stringa rappresentante la password del utente manager
 * @return True se l'utente esiste nel sistema, falso altrimenti
 */
bool getManagerLog(User *user, exhiPlace *place, char *uNameORuEmail, char * uPw);
/**@}*/
#endif //GALLERIADARTE_ARTGALLERYMANAGERS_H
