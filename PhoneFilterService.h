#ifndef PHONEFILESERVICE_H
#define PHONEFILESERVICE_H

#include "Phone.h"

int loadFromFile(Phone **phones, const char *filename, int *capacity);
void saveToFile(Phone *phones, int count, const char *filename);

#endif
