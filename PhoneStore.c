#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Phone.h"
#include "PhoneManager.h"
#include "PhoneFileService.h"
#include "PhoneSearchService.h"
#include "PhoneSortService.h"


#define FILE_NAME "phone.txt"

int main() {
    Phone *phones = NULL;
    int count = 0, capacity = 5;
    int choice;

    count = loadFromFile(&phones, FILE_NAME, &capacity);

    do {
        printf("\n==== PHONE STORE ====\n");
        printf("Total Phones: %d\n", count);
        printf("1. Add Phone\n2. List Phones\n3. Search by Brand\n4. Filter\n5. Sort by Price\n6. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addPhone(&phones, &count, &capacity);
        } else if (choice == 2) {
            listPhones(phones, count);
        } else if (choice == 3) {
            char brand[30];
            printf("Enter brand: ");
            scanf("%s", brand);
            int rc;
            int *res = searchByBrand(phones, count, brand, &rc);
            for (int i = 0; i < rc; i++) printPhone(&phones[res[i]]);
            free(res);
        } else if (choice == 4) {
            char cond[20], seller[50];
            double minPrice;
            printf("Condition (or -): "); scanf("%s", cond);
            printf("Min price (or -1): "); scanf("%lf", &minPrice);
            printf("Seller name (or -): "); scanf("%s", seller);
            int rc;
            int *res = filterPhones(phones, count, cond, minPrice, seller, &rc);
            for (int i = 0; i < rc; i++) printPhone(&phones[res[i]]);
            free(res);
        } else if (choice == 5) {
            sortPhonesByPrice(phones, count);
            printf("Sorted by price.\n");
        } else if (choice == 6) {
            char save;
            printf("Save changes? (y/n): ");
            scanf(" %c", &save);
            if (save == 'y' || save == 'Y') saveToFile(phones, count, FILE_NAME);
        }
    } while (choice != 6);

    free(phones);
    return 0;
}
