
#ifndef GALLERIADARTE_INIT_H
#define GALLERIADARTE_INIT_H

#include <stdbool.h>
#include "../dataType/User/Users.h"

void init();
bool userOperation(Users *user, bool *access);
bool managerOperation(Users *user, exhiPlace *place, bool *access);
bool home(Users *user, exhiPlace *place, bool *access);
#endif //GALLERIADARTE_INIT_H
