#ifndef PHONESEARCHSERVICE_H
#define PHONESEARCHSERVICE_H

#include "Phone.h"

int *searchByBrand(Phone *phones, int count, const char *brand, int *resultCount);
int *filterPhones(Phone *phones, int count, const char *condition, double minPrice, const char *seller, int *resultCount);

#endif
