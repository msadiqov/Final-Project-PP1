#include <stdio.h>
#include <string.h>
#include "PhoneManager.h"

void searchByBrand() {
    char brand[50];
    printf("Enter brand to search: ");
    scanf(" %[^\n]", brand);

    int found = 0;
    for (int i = 0; i < phoneCount; i++) {
        if (strcasecmp(phones[i].brand, brand) == 0) {
            printPhone(phones[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No phones found with brand '%s'.\n", brand);
    }
}
