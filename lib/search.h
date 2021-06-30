#ifndef GALLERIADARTE_SEARCH_H
#define GALLERIADARTE_SEARCH_H

/**
 * \file GalleriaDarte.lib.search.h
 * \defgroup research Ricerca delle opere
 * \addtogroup research
 * @{
 */

/**
 * Modulo coordinatore utilizzato per effettuare la ricerca di una opera d'arte.
 *
 * \sa searchName(FILE* file)
 *
 * \sa searchArtAuthor(FILE* file)
 *
 * \sa searchArtType(FILE* file)
 *
 * \sa searchArtKind(FILE* file)
 *
 * \sa searchArtHistorPeriod(FILE* file)
 *
 * \sa searchArtProdYear(FILE* file)
 *
 */
void research();

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite il nome dell'opera.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 *
 * @param[in] *file	puntatore a file
 */
void searchName(FILE* file);

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite il nome e il cognome dell'autore.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 *
 * @param[in] *file	puntatore a file
 */
void searchArtAuthor(FILE* file);

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite il tipo dell'opera.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 *
 * @param[in] *file	puntatore a file

 */
void searchArtType(FILE* file);

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite il genere dell'opera.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 * @param[in] *file puntatore a file
 */
void searchArtKind(FILE* file);

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite il periodo storico dell'opera.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 *
 * @param[in] *file	puntatore a file
 */
void searchArtHistorPeriod(FILE* file);

/**
 * Tale procedura viene utilizzata per ricercare un'opera d'arte tramite l'anno di produzione dell'opera.
 *
 * \pre Il parametro file deve puntare al file Artworks.txt, altrimenti il corretto funzionamento della procedura non è
 * \pre garantito
 *
 * @param[in] *file puntatore a file
 */
void searchArtProdYear(FILE* file);

/**
 * Procedura utilizzata per ricercare una mostra basandosi sul nome della struttura
 */
void searchShowName();

/**@}*/
#endif //GALLERIADARTE_SEARCH_H
