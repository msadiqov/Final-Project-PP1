#ifndef PHONEFILESERVICE_H
#define PHONEFILESERVICE_H

#include "main.h"

int loadFromFile(Phone **phones, const char *filename, int *capacity);
int saveToFile(Phone *phones, int count, const char *filename);

#endif
