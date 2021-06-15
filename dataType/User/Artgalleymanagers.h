//
// Created by iMuSL on 28/05/2021.
//

#ifndef GALLERIADARTE_ARTGALLEYMANAGERS_H
#define GALLERIADARTE_ARTGALLEYMANAGERS_H

bool saveArtGalleyManager(Users *user);
bool isGalleryManagAlredyReg(char *userName, char *userEmail, char mode);
bool getManagerLog(Users *user, exhiPlace *place, char *uNameORuEmail, char * uPw);

void editManagerFile(Users *user, exhiPlace *place, unsigned int choice);
void delateManager(Users *users);
void registerArtwork();

char* getShow(date *timeStart, date* timeEnd, localManager* manager);
void recordShow(char* nameStructure);

#endif //GALLERIADARTE_ARTGALLEYMANAGERS_H
