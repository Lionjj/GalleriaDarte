/**
 * \file datainput.h
 * \brief Funzioni per lettura valori da tastiera
 * Funzioni utilizzate per la lettura da tastiera di valori di diverso tipo
 * \author Esposito Daniele, Ivone Danilo
 */

#ifndef GALLERIADARTE_DATAINPUT_H
#define GALLERIADARTE_DATAINPUT_H
/**
 * \file GalleriaDarte/lib/datainput.h
 * \defgroup serviceFunctionsNum Funzioni di servizio su valori numerici
 * \addtogroup serviceFunctionsNum
 * @{
 */
 /**
  * Tale funzione viene utilizzata per prendere da tastiera un valore intero.
  *
  * \pre representation: è la base di rappresentazione del numero (valori ammessi 0, 2<=x<=32)
  *
  * \sa strtol(const char *str, char **endptr, int base)
  *
  * @param[in] representation base di rappresentazione del valore intero
  * @return il valore intero nella base representation
  */
int getInt(int representation);

/**
 * Tale funzione viene utilizzata per prendere da tastiera un valore intero senza segno.
 *
 * \pre representation: è la base di rappresentazione del numero (valori ammessi 0, 2<=x<=32)
 *
 * \sa strtoul(const char *str, char **endptr, int base)
 *
 * @param[in] representation base di rappresentazione del valore intero
 * @return il valore intero senza segno nella base representation
 */
unsigned int getUInt(int representation);

/**
 * Tale funzione viene utilizzata per confrontare se il parametro p1 è maggiore, uguale o minore del parametro p2.
 *
 * @param[in] p1 primo parametro
 * @param[in]p2 secondo parametro
 *
 * @return 0 se i due parametri sono uguai, 1 se p1 > p2, e -1 se p1 < p2
 */
int intCompare(const void *p1, const void *p2);
/**@}*/
#endif //GALLERIADARTE_DATAINPUT_H
