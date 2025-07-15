#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include "Phone.h"

void addPhone(Phone **phones, int *count, int *capacity);
void listPhones(Phone *phones, int count);
void editPhone(Phone *phones, int count, int id);
void deletePhone(Phone *phones, int *count, int id);

#endif
