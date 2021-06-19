#ifndef GALLERIADARTE_ARTSHOW_H
#define GALLERIADARTE_ARTSHOW_H

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
    char fiscalCode[16];
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
 * @{
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
 * \sa Artshow.h::getStreet(char *streetName)
 *
 * \sa Artshow.h::getHouseNum(char *houseNum)
 *
 * \sa Artshow.h::getCity(char *city)
 *
 * \sa Artshow.h::getNameStructure(char *structure)
 *
 * @param[in,out] *place: puntatore ad una struttura di tipo: exhiPlace
 */

void getExhiPlace(exhiPlace *place);

/**
 * Tale procedura viene utilizzata per dividere in token la stringa str, recuperata da file,
 * per poi caricare i token nella struttura place.
 *
 * \sa Artshow.c::loadGallery(char str[], exhiPlace *place)
 *
 * Per ulteriori informazioni vedi anche \sa Artshow.c::loadGallery(char str[], exhiPlace *place)
 *
 * @param[in] str[]: stringa da dividere in token
 * @param[out] *place: puntatore ad una struttura di tipo exhiPlace
 */
void loadGallery(char str[], exhiPlace *place);

/**
 * Funzione utilizzata per verificare se una sede della galleria d'arte è gia registrata
 *
 * \sa Artshow.c::isGalleryAlredyReg(char *galCity, char *galStreet, char *galHouseN)
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
 * @{
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
 * \sa Artshow.h::getYear(date* time, unsigned int current)
 *
 * \sa Artshow.h::getMonth(date *time, unsigned int currentMonth)
 *
 * \sa Artshow.h::getDay(date* time, date* current)
 *
 * @param[out] *time: puntatore ad una struttura di tipo: date
 */
void getDate(date* time);

/**
 * Modulo coordinatore, utilizzato per specificare il tempo di esposizione di esposizione di una mostra
 * sfruttando le procedure:
 *
 * getDate(date* time)
 *
 * @param[in,out] *timeStart: puntatore ad una struttura date che rappresenta la data di partenza
 * @param[in,out] *timeEnd: punatore ad una struttura date che rappresenta la data di fine
 */
void getExpositionTime(date* timeStart, date* timeEnd);

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
 * @{
 *  Procedura utilizzata per caricare il valore fiscalCode[] di una struttura localManager
 *
 * @param[in,out] *fiscalCode: puntatore ad una stringa che conterra il codice fiscale di un manager locale
 */
void getFiscalCode(char* fiscalCode);

/**
 * Modulo coordinatore per caricare una generica struttura: localManager, esso sfrutta le procedure:
 *
 * \sa Artshow.h::getFiscalCode(char* fiscalCode)
 *
 * \sa Artshow.h::getName(char* name) guarda anche \ref
 *
 * @param[in,out] *manager: puntatore ad una struttora di tipo: localManager
 */
/**@}*/
void getLocalManager(localManager* manager);

/**
 * \addtogroup artwork
 * @{
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
 * \sa Artshow.h::unsigned int getIdArtwork()
 *
 * \sa Artshow.h::getArtworkName(char* artworkName)
 *
 * \sa Artshow.h::operaType getOperaType()
 *
 * \sa Artshow.h::getKind(char* kind)
 *
 * \sa Artshow.h::getHistorPeriod(char* historPeriod)
 *
 * \sa Artshow.h::isBC()
 *
 * \sa Artshow.h::getProdYear(bool BC)
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

/**
 * Funzione utilizzata per verificare l'esistenza del indentificativo ID, per un opera d'arte
 *
 * @param[in] ID: Identificativo di cui si verificerà l'esistenza
 * @return True se il valore è esistente, falso altrimenti
 */
bool IDExists(unsigned int ID);
/**@}*/

/**
 * Funzione utilizzata per restituire l'identificativo di una mostra
 *
 * @return L'identificativo di una mostra
 */
unsigned int getIDShow();

/**
 * Modulo coordinatore utilizzato per caricare le strutture: timeStart, timeEnd, manager; sfruttando:
 *
 * \sa Artshow.h::getLocalManager(localManager* manager)
 *
 * \sa Artshow.h::getExpositionTime(date* timeStart, date* timeEnd)
 *
 * \sa Artshow.h::chooseArtwork(unsigned int IDs[], unsigned int dim)
 *
 * @param[in] *timeStart: puntatore ad una struttura date che rappresenta la data di inizio di una mostra
 * @param[in] *timeEnd: punntatore ad una struttura date che rappresenta la data di fine di una mostra
 * @param[in] *manager: puntatore ad una struttura localManager che rappresenta il il manager locale della mostra
 * @return Vettore di identificativi di opere d'arte
 */
char* getShow(date *timeStart, date* timeEnd, localManager* manager);

//Procedura di lettura e stampa delle opere
void loadArtwork(char str[], artwork *artwork);
void printArtwork(int num, artwork artwork);

void printArtshow(FILE *file, unsigned int ido);

#endif //GALLERIADARTE_ARTSHOW_H
