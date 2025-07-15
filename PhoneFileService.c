#include "PhoneFileService.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadFromFile(Phone **phones, const char *filename, int *capacity) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    int count = 0;
    Phone temp;

    *capacity = 10;
    *phones = malloc((*capacity) * sizeof(Phone));
    if (!*phones) {
        fclose(file);
        return 0;
    }

    while (fscanf(file, "%d %s %s %d %lf %s %s %s",
                  &temp.id, temp.brand, temp.model,
                  &temp.storage, &temp.price, temp.condition,
                  temp.seller.name, temp.seller.phone) == 8) {

        if (count >= *capacity) {
            *capacity *= 2;
            *phones = realloc(*phones, (*capacity) * sizeof(Phone));
            if (!*phones) break;
        }

        (*phones)[count++] = temp;
    }

    fclose(file);
    return count;
}

int saveToFile(Phone *phones, int count, const char *filename) {
    FILE *file = fopen(filename, "a"); // append mode
    if (!file) return 0;

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %d %.2f %s %s %s\n",
                phones[i].id, phones[i].brand, phones[i].model,
                phones[i].storage, phones[i].price,
                phones[i].condition,
                phones[i].seller.name, phones[i].seller.phone);
    }

    fclose(file);
    return 1;
}
