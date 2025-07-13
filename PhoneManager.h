#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include "Phone.h"

#define MAX_PHONES 100

extern Phone phones[MAX_PHONES];
extern int phoneCount;

void addPhone();
void listPhones();
void editPhone();
void deletePhone();

#endif
