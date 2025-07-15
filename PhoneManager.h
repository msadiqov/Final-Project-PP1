#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include "main.h"

extern Phone *phones;
extern int phoneCount;
extern int capacity;

void ensureCapacity();
void addPhone();
void listPhones();
void editPhone();
void deletePhone();
void searchPhones();
void sortPhones();
void filterPhones();

#endif
