#ifndef GALLERIADARTE_ARTSHOW_H
#define GALLERIADARTE_ARTSHOW_H

/**
 * Numero massimo di caratteri che una stringa può contenere nel file Artshow.txt
 */
#define MAX_LEN_SHOW 400

/**
 * Numero massimo di caratteri che una stringa può contenere nel file Artworks.txt
 */
#define MAX_LEN_ARTWORK 235

/**
 * Numero massimo di opere che una mostra può contenere
 */
#define MAX_ARTWORKS 60
#include <stdio.h>
#include <stdbool.h>
/**
 * \file GalleriaDarte.dataType.ArtShow.Artshow.h
 *
 * \defgroup exhibitionPlace Luogo della mostra
 * \struct exhiPlace "../GalleriaDarte/dataType/ArtShow/Artshow.h"
 */
typedef struct
{
    char streetName[90];
    char houseNum[5];
    char city[30];
    char structure[50];
} exhiPlace;

/**
 * \defgroup date Data
 * \struct date "../GalleriaDarte/dataType/ArtShow/Artshow.h"
 */
typedef struct
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
} date;

/**
 * \defgroup localManager Manager locale
 * \struct localManager "../GalleriaDarte/dataType/ArtShow/Artshow.h"
 */
typedef struct
{
    char name[30];
    char surname[30];
    char fiscalCode[17];
} localManager;

/**
 * \addtogroup artwork
 * \enum operaType "../GalleriaDarte/dataType/ArtShow/Artshow.h"
 */
enum operaType
{
    painting, sculpture, drawing
};

/**
 * \defgroup artwork Opera d'arte
 * \struct artwork "../GalleriaDarte/dataType/ArtShow/Artshow.h"
 */
typedef struct
{
    unsigned int IDArtwork;
    char name[100];
    char authorName[30];
    char authorSurname[30];
    enum operaType operaType;
    char kind[30];
    char historPeriod[30];
    unsigned int prodYear;
    bool BC;
} artwork;

/**
 * \addtogroup exhibitionPlace
 * @{*/

/**
 * Carica il valore: streetName[] di una struttura exhiPlace
 *
 * @param[out] *streetName: puntatore ad una stringa che contenerrà il nome della via in cui è situata una struttura
 */
void getStreet(char *streetName);

/**
 * Carica il valore: houseNum[] di una struttura exhiPlace
 *
 * @param[out] *houseNum: puntatore ad una stringa che contenerrà il numero civico di una struttura
 */
void getHouseNum(char *houseNum);

/**
 * Carica il valore: city[] di una struttura exhiPlace
 *
 * @param[out] *place: puntatore ad una stringa che conterrà il nome della città in cui è situata la struttura
 */
void getCity(char *city);

/**
 * Carica il valore: structure[] di una struttura exhiPlace
 *
 * @param[out] *structure: puntatore ad una stringa che conterrà il nome della struttura
 */
void getNameStructure(char *structure);

/**
 * \brief Carica l'intera struttura
 *
 * Modulo coordinatore, utilizzato per caricare una generica struttura, exhiPlace;
 *
 * \pre Tutte le evenutali informazioni precedentemente contenute nel parametro place, andranno perse una volta che questa
 * \pre procedura verrà richiamata.
 *
 * \sa getStreet(char *streetName)
 *
 * \sa getHouseNum(char *houseNum)
 *
 * \sa getCity(char *city)
 *
 * \sa getNameStructure(char *structure)
 *
 * @param[out] *place: puntatore ad una struttura di tipo: exhiPlace
 */
void getExhiPlace(exhiPlace *place);

/**
 * Tale procedura viene utilizzata per dividere in token la stringa str, recuperata da file,
 * per poi caricare i token nella struttura place.
 *
 * \pre la stringa str, dovrà essere recuperata dal file ArtGalleryManager.txt, altrimenti il corretto funzionamento
 * \pre della procedura non è garantito. Inoltre tutte le evenutali informazioni precedentemente contenute nel parametro
 * \pre place, andranno perse una volta che questa procedura verrà richiamata.
 *
 * @param[in] str[]: stringa da dividere in token
 * @param[out] *place: puntatore ad una struttura di tipo exhiPlace
 */
void loadGallery(char str[], exhiPlace *place);

/**
 * Funzione utilizzata per verificare se una sede della galleria d'arte è gia registrata
 *
 * \pre Se anche solo uno dei parametri galCity, galStreet e galHouseN è NULL, il corretto funzionamento della funzione
 * \pre non è garantito.
 *
 * \sa isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN)
 *
 * @param[in] *galCity: puntatore a una stringa rappresentante la città in cui è situata la sede
 * @param[in] *galStreet: puntatore a una stringa che rappresenta la via in cui è situata la sede
 * @param[in] *galHouseN: puntatore a una stringa che rappresenta il numero civico in cui è situata la sede
 * @return True se la sede è già registrata, false altrimenti
 */
/**@}*/
bool isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN);

/**
 * \addtogroup date
 * @{*/

/**
 * Procedura utilizzata per caricare una struttura di tipo: date, con la data odierna
 *
 * \pre Tutte le evenutali informazioni precedentemente contenute nel parametro time, andranno perse una volta che
 * \pre questa procedura verrà richiamata.
 *
 * @param[out] *d: puntatore ad una struttura di tipo: date
 */
void getCurrentDate(date* d);

/**
 * Procedura utilizzata per caricare il valore: year di una struttura data
 *
 * \pre Le evenutali informazioni precedentemente contenute nel parametro time->year, andranno perse una volta che
 * \pre questa procedura verrà richiamata.
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] current: valore che specifica l'anno corrente
 */
void getYear(date* time, unsigned int current);

/**
 * Procedura utilizzata per caricare il valore: month di una struttura data
 *
 * \pre Le evenutali informazioni precedentemente contenute nel parametro time->month, andranno perse una volta che
 * \pre questa procedura verrà richiamata.
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] *current: puntatore ad una struttura di tipo: date, che indica la data corrente
 */
void getMonth(date *time, date *current);

/**
 * Procedura utilizata per caricare il valore: day di una struttura date
 *
 * \pre Le evenutali informazioni precedentemente contenute nel parametro time->day, andranno perse una volta che
 * \pre questa procedura verrà richiamata.

 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] *current: puntatore ad una struttura di tipo: date, che indica la data corrente
 */
void getDay(date* time, date* current);

/**
 * Modulo coordinatore ulizizzato per caricare una struttura di tipo: date;
 *
 *
 * \pre Le evenutali informazioni precedentemente contenute nel parametro time, andranno perse una volta che
 * \pre questa procedura verrà richiamata.
 *
 * \sa getYear(date* time, unsigned int current)
 *
 * \sa getMonth(date *time, unsigned int currentMonth)
 *
 * \sa getDay(date* time, date* current)
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 */
void getDate(date* time);

/**
 * Modulo coordinatore, utilizzato per specificare il tempo di esposizione di una mostra.
 *
 *
 * \pre Le evenutali informazioni precedentemente contenute nei parametri timeStart e timeEnd, andranno perse una volta
 * \pre che questa procedura verrà richiamata.
 *
 * \sa getDate(date* time)
 *
 * @param[out] *timeStart: puntatore ad una struttura date che rappresenta la data di partenza
 * @param[out] *timeEnd: punatore ad una struttura date che rappresenta la data di fine
 */
void getExpositionTime(date* timeStart, date* timeEnd);

/**
 * Procedura utilizzata per recuperare la data di terminazione della mostra, il cui identificativo è rappresentato da
 * id, dal file Artshow.txt caricando tale data nelle struttura timeEnd.
 *
 * \pre Le evenutali informazioni precedentemente contenute nel parametro timeEnd, andranno perse una volta che
 * \pre questa procedura verrà richiamata.
 *
 * @param[out] *timeEnd: puntatore ad una struttura di tipo date rappresentante la data di fine di una mostra
 * @param[in] id: valore intero senza segno rappresentante l'identificatore della mostra
 */
void fgetDateEnd(date *timeEnd, unsigned int id);

/**
 * Procedura utilizzata per ferificare se all'interno del file Artshow.txt ci sono mostre che sono terminate, se si esse
 * vengono eliminate dal file.
 *
 * \sa isShowOver(unsigned int id)
 *
 * \sa delateArtshow(unsigned int idArtshow)
 */
void listenerTimeExpired();

/**
 * Funzione utilizzata per verificare se, dato un certo anno esso è bisestile
 *
 * @param[in] year: valore che rappresenta una annata
 * @return True se l'anno è bisestile, falso altrimenti
 */
bool isLeapYear(unsigned int year);

/**
 * Funzione utilizzata per verificare se la data timeStart è precedente alla data timeEnd
 *
 * \pre Se tutti gli attributi dei parametri timeStart e timeEnd non contengono valori, il corretto funzionamento della
 * \pre funzione non è grantito.
 *
 * @param[in] *timeStart: puntatore ad una struttura date che rappresenta la data di partenza
 * @param[in] *timeEnd: punatore ad una struttura date che rappresenta la data di fine
 * @return: Restituisce True se la data rappresentata da timeStart è precedente alla data rappresentata da timeEnd, false altrimenti
 */
 /**@}*/
bool isPrevious(date* timeStart, date* timeEnd);

/**
 * \addtogroup localManager
 * @{*/

/**
 * Procedura utilizzata per caricare il valore fiscalCode[] di una struttura localManager
 *
 * @param[out] *fiscalCode: puntatore ad una stringa che conterra il codice fiscale di un manager locale
 */
void getFiscalCode(char* fiscalCode);

/**
 * Modulo coordinatore per caricare una generica struttura: localManager:
 *
 * \sa getFiscalCode(char* fiscalCode)
 *
 * \sa getName(char* name)
 *
 * \sa getSurname(char *surname)
 *
 * @param[out] *manager: puntatore ad una struttora di tipo: localManager
 */
/**@}*/
void getLocalManager(localManager* manager);

/**
 * \addtogroup artwork
 * @{*/

 /**
 * Funzione utilizzata per assegnare, ad un opera d'arte un identificativo
 *
 * @return l'identificativo dell'opera
 */
unsigned int getIdArtwork();

/**
 * Procedura per caricare il name[] della struttura artwork
 *
 * @param[out] *artworkName: puntatore ad una stringa che conterrà il nome dell'opera
 */
void getArtworkName(char* artworkName);

/**
 * Funzione utilizzata per specificare il tipo di opera
 *
 * @return Il numero che rappresenta il tipo dell'opera
 */
enum operaType getOperaType();

/**
 * procedura per caricare il kind[] della struttura artwork
 *
 * @param[out] *kind: puntatore ad una stringa che conterrà il genere dell'opera
 */
void getKind(char* kind);

/**
 * Procedura per caricare il historPeriod[] della struttura artwork
 *
 * @param[out] *historPeriod: puntatore ad una stringa che contterra il periodo storico in cui è stata realizzata l'opera
 */
void getHistorPeriod(char* historPeriod);

/**
 * Funzione utilizzata per specificare se la data di produzione dell'opera è avanti cristo
 *
 * @return True se l'utente specifica che l'opera è avanti cristo, false altrimenti
 */
bool isBC();

/**
 * Funzione untilizzata per specificare l'anno in cui è stata prodotta l'opera
 *
 * \note Tale funzione verifica se l'anno di produzione di un'opera d'arte, nel caso essa fosse A.C., non sià superiore
 * \note all'anno 40.000 A.C. (anno a cui risale la prima opera d'arte scoperta)
 *
 * @param[in] BC: valore booleano che specifica se la data a cui ci si riferisce è prima o dopo cristo
 * @return L'anno di produzione dell'opera
 */
unsigned int getProdYear(bool BC);

/**
 * Modulo coordinatore utilizzato per caricare una generica struttura artwork.
 *
 * \pre Tutte le informazioni contenute nel parametro artw, andranno perse al termine di questa procedura.
 *
 * \sa getIdArtwork()
 *
 * \sa getArtworkName(char* artworkName)
 *
 * \sa operaType getOperaType()
 *
 * \sa getKind(char* kind)
 *
 * \sa getHistorPeriod(char* historPeriod)
 *
 * \sa isBC()
 *
 * \sa getProdYear(bool BC)
 *
 * @param[out] *artw: puntatore ad una struttura di tipo artwork
 */
void getArtwork(artwork* artw);

/**
 * Procedura utilizzata per decidere quali opere d'arte dovranno essere inserite nella mostra
 *
 * @param[in,out] IDs[]: vettore di interi che contiene gli identificativi delle opere d'arte
 * @param[in] dim: dimensione del vettore
 */
void chooseArtwork(unsigned int IDs[], unsigned int dim);

/**
 * Tale procedura viene utilizzata per mostrare all'utente le informazioni dell'opera passata come parametro.
 *
 * \pre Il parametro artwork dovrà essere necessariamente caricato in precedenza, altrimenti non è garantito il corretto
 * \pre funzionamento della procedura.
 *
 * @param[in] num: identificativo dell'opera d'arte
 * @param[in] *artwork: puntatore ad una struttura di tipo artwork, rappresentante un'opera d'arte
 */
void printArtwork(int num, artwork* artwork);

/**
 * Tale procedura permette di mostrare all'utente le opere che sono associate alla mostra il cui identificativo
 * corrisponde al parametro idArtshow.
 *
 * @param[in] idArtshow: identificativo della mostra
 */
void printArtworksInShow(unsigned int idArtshow);

/**
 * Procedura utilizzata per estrapolare dalla stringa str le informazioni relative ad una opera d'arte.
 * \pre la stringa str deve essere estrapolata dal file Artworks.txt altrimenti il corretto funzionamento
 * \pre della procedura non è garantito.
 *
 * @param[in] str[]: stringa contenente le informazioni di un'opera d'arte
 * @param[out] *artwork: puntatore ad una struttura di tipo artwork, in essa verrano caricati i dati estrapolati da str
 */
void loadArtwork(char str[], artwork *artwork);

/**
 * Funzione utilizzata per verificare l'esistenza del indentificativo ID, per un opera d'arte
 *
 * @param[in] ID: Identificativo di cui si verificerà l'esistenza
 * @return True se il valore è esistente, falso altrimenti
 */
bool IDExists(unsigned int ID, bool isFileArtshow);

/**
 * Tale funzione verifica se all'interno del file Artworks.txt, l'opera il cui nome è rappresentato da
 * artName è già stata registrata o meno.
 *
 * @param[in] *artName: puntatore ad una stringa rappresentante il nome di un'opera d'arte
 * @return true se l'opera è già stata registrata nel sistema, falso altriemnti
 */
bool isArtworkAlredyReg(char* artName);

/**
 * Tale funzione carica il vettore idsArtwork, con gli identificativi delle opere, che la mostra identificata da
 * idArtshow, ha al suo interno.
 *
 * @param[in] idArtshow: intero senza segno, rappresentante l'identificativo di una mostra
 * @param[in,out] idsArtwork: vettore di interi senza segno, dove ciascun valore del vettore rappresenta un
 * identificativo di un'opera
 * @return l'indice relativo all'ultima posizione dele vettore idsArtworks
 */
unsigned int fgetIdsArtwork(unsigned int idArtshow, unsigned int idsArtwork[]);
/**@}*/

/**
 * \defgroup Show Mostra
 * \addtogroup Show
 * @{*/

/**
 * Funzione utilizzata per restituire l'identificativo di una mostra
 *
 * @return L'identificativo di una mostra
 */
unsigned int getIDShow();

/**
 * Modulo coordinatore utilizzato per caricare le strutture: timeStart, timeEnd, manager;
 *
 * \sa getLocalManager(localManager* manager)
 *
 * \sa getExpositionTime(date* timeStart, date* timeEnd)
 *
 * \sa chooseArtwork(unsigned int IDs[], unsigned int dim)
 *
 * \post La stringa che viene restituita, dopo che è stata utilizzata, deve essere liberata tramite la free()
 *
 * @param[in] *timeStart: puntatore ad una struttura date che rappresenta la data di inizio di una mostra
 * @param[in] *timeEnd: punntatore ad una struttura date che rappresenta la data di fine di una mostra
 * @param[in] *manager: puntatore ad una struttura localManager che rappresenta il il manager locale della mostra
 * @return Vettore di identificativi di opere d'arte
 */
char* getShow(date *timeStart, date* timeEnd, localManager* manager);

/**
 * Tale procedura viene utilizzata per eliminare dal file Artshow.txt e dal file Reservations.txt la mostra il cui
 * identificativo è idArtshow.
 *
 * @param[in] idArtshow: valore intero senza segno rappresentante l'identificativo di una mostra
 */
void delateArtshow(unsigned int idArtshow);

/**
 * Funzione utilizzata per verificare se, la mostra con identificativo id, è terminata basandosi sulla data odierna.
 *
 * \note se la data di terminazione della mosra corrisponde alla data odierna, allora la funzione
 * \note restituirà il valore true
 *
 * \sa isPrevious(date* timeStart, date* timeEnd)
 *
 * @param id: intero senza segno rappresentante un'identificativo di una mostra
 * @return True se la mostra è terminata, falso altrimenti
 */
bool isShowOver(unsigned int id);


/**
 * Tale procedura permette la visualizzazione delle informazioni relative ad una mostra, ricercando essa tramite id
 *
 * @param[in] id: intero senza segno rappresentante l'identificativo di una mostra
 */
void assArtshow(unsigned int id);

/**
 * Tale funzione permette di all'utente di selezionare la mostra e registrarsi attreverso la procedura:
 *
 * \sa bookClient(const unsigned int IDArtshow, char *newUsername)
 *
 * @param[in] username: stringa rappresentante il nome l'username dell'utente che vuole registrarsi ad una mostra
 */
void selectArtshow(char *username);

/**
 * Tale procedura è utilizzata per modificare l'username dell'utente all'interno del file Reservations.txt, sostituendo
 * il precedente username con il parametro newUsername.
 *
 * \pre I parametri oldUsername e newUsername, se nulli non garantiscono il corretto funzionamento della procedura
 *
 * @param[in] *oldUsername stringa rappresentante l'username dell'utente client da sostituire
 * @param [in] *newUsername stringa rappresentante l'username dell'utente client che sostituirà il precedente
 */
void editRes(char *oldUsername, char *newUsername);

/**
 * Tale procedura permette di visualizzare le mostre disponibili nel sistema
 */
void printShow();

/**
 * Tale funzione verifica se un utente può disdire una prenotazione rispettando i vincoli temporali.
 * 
 * \pre Il parametro idShow deve essere un identificativo esistente, altrimenti il corretto funzionamento della funzione non è garantito
 *  
 * @param[in] idShow: valore intero rappresentante l'identificativo della mostra prenotata.
 */
bool deleteReservationCheck(int idShow);

/**
 * Tale funzione è utilizzata per mostrare all'utente gli identificativi di tutte le mostre a cui si è iscritto.
 * 
 * \pre Il parametro *username non deve essere NULL altrimenti il corretto funzionamento della funzione non è garantito.
 * 
 * @param[in] *username: stringa rappresentante l'username dell'utente.
 */
bool printIdReservations(char* username);

/**
 * Tale funzione permette di eliminare il nome utente rappresentanto dal parametro username, da una prenotazione ad una
 * mostra il cui identificativo è idshow.
 *
 * \pre se l'usernmae dovesse essere NULL, il corretto funzionamento della funzione non è garantito.
 *
 * @param *username: stringa rappresentante l'username dell'utente
 * @param idshow: intero senza segno rappresentante l'identificativo di una mostra
 * @return true se è stato possibile cancellare l'username dal file, false altrimenti
 */
bool deleteClientFromRes(char *username, unsigned int idshow);

/**@}*/
#endif //GALLERIADARTE_ARTSHOW_H
