#ifndef GALLERIADARTE_ARTSHOW_H
#define GALLERIADARTE_ARTSHOW_H

#define MAX_LEN_SHOW 400
#define MAX_LEN_ARTWORK 235
#define MAX_ARTWORKS 60

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
 * @param[in,out] *streetName: puntatore ad una stringa che contenerrà il nome della via in cui è situata una struttura
 */
void getStreet(char *streetName);

/**
 * Carica il valore: houseNum[] di una struttura exhiPlace
 *
 * @param[in,out] *houseNum: puntatore ad una stringa che contenerrà il numero civico di una struttura
 */
void getHouseNum(char *houseNum);

/**
 * Carica il valore: city[] di una struttura exhiPlace
 *
 * @param[in,out] *place: puntatore ad una stringa che conterrà il nome della città in cui è situata la struttura
 */
void getCity(char *city);

/**
 * Carica il valore: structure[] di una struttura exhiPlace
 *
 * @param[in,out] *structure: puntatore ad una stringa che conterrà il nome della struttura
 */
void getNameStructure(char *structure);

/**
 * \brief Carica l'intera struttura
 *
 * Modulo coordinatore, utilizzato per caricare una generica struttura, exhiPlace;
 * sfruttando le procedure:
 *
 * \sa getStreet(char *streetName)
 *
 * \sa getHouseNum(char *houseNum)
 *
 * \sa getCity(char *city)
 *
 * \sa getNameStructure(char *structure)
 *
 * @param[in,out] *place: puntatore ad una struttura di tipo: exhiPlace
 */
void getExhiPlace(exhiPlace *place);

/**
 * Tale procedura viene utilizzata per dividere in token la stringa str, recuperata da file,
 * per poi caricare i token nella struttura place.
 *
 * \sa loadGallery(char str[], exhiPlace *place)
 *
 * @param[in] str[]: stringa da dividere in token
 * @param[out] *place: puntatore ad una struttura di tipo exhiPlace
 */
void loadGallery(char str[], exhiPlace *place);

/**
 * Funzione utilizzata per verificare se una sede della galleria d'arte è gia registrata
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
 * @param[in,out] *d: puntatore ad una struttura di tipo: date
 */
void getCurrentDate(date* d);

/**
 * Procedura utilizzata per caricare il valore: year di una struttura data
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] current: valore che specifica l'anno corrente
 */
void getYear(date* time, unsigned int current);

/**
 * Procedura utilizzata per caricare il valore: month di una struttura data
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] *current: puntatore ad una struttura di tipo: date, che indica la data corrente
 */
void getMonth(date *time, date *current);

/**
 * Procedura utilizata per caricare il valore: day di una struttura date
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 * @param[in] *current: puntatore ad una struttura di tipo: date, che indica la data corrente
 */
void getDay(date* time, date* current);

/**
 * Modulo coordinatore ulizizzato per caricare una struttura di tipo: date;
 * sfrutta le procedure:
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
 * Modulo coordinatore, utilizzato per specificare il tempo di esposizione di esposizione di una mostra
 * sfruttando le procedure:
 *
 * \sa getDate(date* time)
 *
 * @param[in,out] *timeStart: puntatore ad una struttura date che rappresenta la data di partenza
 * @param[in,out] *timeEnd: punatore ad una struttura date che rappresenta la data di fine
 */
void getExpositionTime(date* timeStart, date* timeEnd);

/**
 * Procedura utilizzata per recuperare la data di terminazione della mostra il cui identificativo è rappresentato da
 * id, dal file Artshow.txt, caricando tale data nelle struttura timeEnd.
 *
 * @param[in,out] *timeEnd: puntatore ad una struttura di tipo date rappresentante la data di fine di una mostra
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
 *  Procedura utilizzata per caricare il valore fiscalCode[] di una struttura localManager
 *
 * @param[in,out] *fiscalCode: puntatore ad una stringa che conterra il codice fiscale di un manager locale
 */
void getFiscalCode(char* fiscalCode);

/**
 * Modulo coordinatore per caricare una generica struttura: localManager, esso sfrutta le procedure:
 *
 * \sa getFiscalCode(char* fiscalCode)
 *
 * \sa getName(char* name) guarda anche \ref
 *
 * @param[in,out] *manager: puntatore ad una struttora di tipo: localManager
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
 * @param[in,out] *artworkName: puntatore ad una stringa che conterrà il nome dell'opera
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
 * @param[in,out] *kind: puntatore ad una stringa che conterrà il genere dell'opera
 */
void getKind(char* kind);

/**
 * Procedura per caricare il historPeriod[] della struttura artwork
 *
 * @param[in,out] *historPeriod: puntatore ad una stringa che contterra il periodo storico in cui è stata realizzata l'opera
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
 * @param[in] BC: valore booleano che specifica se la data a cui ci si riferisce è prima o dopo cristo
 * @return L'anno di produzione dell'opera
 */
unsigned int getProdYear(bool BC);

/**
 * Modulo coordinatore utilizzato per caricare una generica struttura artwork, sfrutta:
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
 * @param[in,out] *artw: puntatore ad una struttura di tipo artwork
 */
void getArtwork(artwork* artw);

/**
 * Procedura utilizzata per decidere quali opere d'arte dovranno essere inserite nella mostra
 *
 * @param[in,out] IDs[]: vettore di interi che contiene gli identificativi delle opere d'arte
 * @param[in,out] dim: dimensione del vettore
 */
void chooseArtwork(unsigned int IDs[], unsigned int dim);


void printArtwork(int num, artwork* artwork);


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
bool IDExists(unsigned int ID);
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
 * Modulo coordinatore utilizzato per caricare le strutture: timeStart, timeEnd, manager; sfruttando:
 *
 * \sa getLocalManager(localManager* manager)
 *
 * \sa getExpositionTime(date* timeStart, date* timeEnd)
 *
 * \sa chooseArtwork(unsigned int IDs[], unsigned int dim)
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
/**@}*/


void selectArtshow(char *username);
void assArtshow(unsigned int id);
#endif //GALLERIADARTE_ARTSHOW_H
