
#ifndef GALLERIADARTE_INIT_H
#define GALLERIADARTE_INIT_H

#include <stdbool.h>
#include "../dataType/User/Users.h"

void init();
bool userOperation(User *user, bool *access);
bool managerOperation(User *user, exhiPlace *place, bool *access);
bool home(User *user, exhiPlace *place, bool *access);
#endif //GALLERIADARTE_INIT_H
