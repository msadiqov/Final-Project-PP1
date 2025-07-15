#include "PhoneSortService.h"
#include <stdlib.h>

int comparePrice(const void *a, const void *b) {
    Phone *p1 = (Phone *)a;
    Phone *p2 = (Phone *)b;
    return (p1->price > p2->price) - (p1->price < p2->price);
}

void sortPhonesByPrice(Phone *phones, int count) {
    qsort(phones, count, sizeof(Phone), comparePrice);
}
