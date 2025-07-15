#include "PhoneFileService.h"
#include <stdio.h>
#include <stdlib.h>

int loadFromFile(Phone **phones, const char *filename, int *capacity) {
    FILE *file = fopen(filename, "rb");
    if (!file) return 0;

    int phoneCount = 0;
    fread(&phoneCount, sizeof(int), 1, file);

    *capacity = phoneCount > 5 ? phoneCount : 5;
    *phones = realloc(*phones, (*capacity) * sizeof(Phone));
    if (*phones == NULL) {
        fclose(file);
        return 0;
    }

    fread(*phones, sizeof(Phone), phoneCount, file);
    fclose(file);
    return phoneCount;
}

int saveToFile(Phone *phones, int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;

    fwrite(&count, sizeof(int), 1, file);
    fwrite(phones, sizeof(Phone), count, file);
    fclose(file);
    return 1;
}
