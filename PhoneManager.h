#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include "Phone.h"

extern Phone *phones;       
extern int phoneCount;      // Hal-hazırda neçə telefon var

void addPhone();
void listPhones();
void editPhoneByIndex(int index);
void deletePhoneByIndex(int index);

#endif
