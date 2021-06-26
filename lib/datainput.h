//
// Created by Ragnar.exe on 03/05/2021.
//
/**
 * \file datainput.h
 * \brief Funzioni per lettura valori da tastiera
 * Funzioni utilizzate per la lettura da tastiera di valori di diverso tipo
 * \author Esposito Daniele, Ivone Danilo
 */

#ifndef GALLERIADARTE_DATAINPUT_H
#define GALLERIADARTE_DATAINPUT_H

/**
 * \brief Leggi un valore intero da tastiera.
 * Tale funzione viene utilizzata per prendere da tastiera un valore intero.
 * \param[in] representation Base di rappresentazione del valore intero
 * \return Il valore intero nella base representation
 */
int getInt(int representation);

/**
 * \brief Leggi un valore intero short da tastiera.
 * Questa funzione consente di leggere un valore intero dallo standard input.
 * \param representation Base di rappresentazione del valore intero
 * \return Il valore intero nella base representation
 */
int getShort(int representation);

/**
 * \brief Leggi un valore intero senza segno da tastiera
 * Tale funzione viene utilizzata per prendere da tastiera un valore intero senza segno. 
 * \param representation Base di rappresentazione del valore intero
 * \return il valore intero senza segno nella base representation
 */
unsigned int getUInt(int representation);

float getFloat();

double getDouble();

/**
 * \brief Confronta se un primo parametro con un secondo parametro.
 * Tale funzione viene utilizzata per confrontare se il parametro p1 è maggiore, uguale o minore del parametro p2.
 * \param *p1 puntatore primo parametro
 * \param *p2 puntatore secondo parametro
 * \return 0 se i due parametri sono uguai, 1 se p1 > p2 e -1 se p1 < p2
 */
int unsignedIntCompare(const void *p1, const void *p2);

#endif //GALLERIADARTE_DATAINPUT_H
