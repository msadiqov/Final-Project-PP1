#include <string.h>
#include <stdlib.h>
#include "PhoneSearchService.h"

int *searchByBrand(Phone *phones, int count, const char *brand, int *resultCount) {
    int *indexes = malloc(count * sizeof(int));
    *resultCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(phones[i].brand, brand) == 0) {
            indexes[(*resultCount)++] = i;
        }
    }
    return indexes;
}

int *filterPhones(Phone *phones, int count, const char *condition, double minPrice, const char *seller, int *resultCount) {
    int *indexes = malloc(count * sizeof(int));
    *resultCount = 0;
    for (int i = 0; i < count; i++) {
        if ((strcmp(condition, "-") == 0 || strcmp(phones[i].condition, condition) == 0) &&
            (minPrice < 0 || phones[i].price >= minPrice) &&
            (strcmp(seller, "-") == 0 || strcmp(phones[i].seller.name, seller) == 0)) {
            indexes[(*resultCount)++] = i;
        }
    }
    return indexes;
}
