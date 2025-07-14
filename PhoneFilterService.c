// PhoneFilterService.c - Filter combinations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Phone.h"
#include "PhoneManager.h"

void printPhone(Phone p);

void filterPhones() {
    if (phoneCount == 0) {
        printf("No phones available.\n");
        return;
    }

    char brand[50] = "", model[50] = "", condition[20] = "", seller_name[50] = "";
    int minStorage = -1, maxStorage = -1;
    double minPrice = -1, maxPrice = -1;

    printf("Enter brand to filter (or '-' to skip): ");
    scanf(" %[^]", brand);

    printf("Enter model to filter (or '-' to skip): ");
    scanf(" %[^]", model);

    printf("Enter condition to filter (New/Used or '-' to skip): ");
    scanf(" %[^]", condition);

    printf("Enter seller name to filter (or '-' to skip): ");
    scanf(" %[^]", seller_name);

    printf("Enter min storage (or -1 to skip): ");
    scanf("%d", &minStorage);

    printf("Enter max storage (or -1 to skip): ");
    scanf("%d", &maxStorage);

    printf("Enter min price (or -1 to skip): ");
    scanf("%lf", &minPrice);

    printf("Enter max price (or -1 to skip): ");
    scanf("%lf", &maxPrice);

    int count = 0;
    for (int i = 0; i < phoneCount; i++) {
        if ((strcmp(brand, "-") != 0 && strcasecmp(phones[i].brand, brand) != 0) ||
            (strcmp(model, "-") != 0 && strcasecmp(phones[i].model, model) != 0) ||
            (strcmp(condition, "-") != 0 && strcasecmp(phones[i].condition, condition) != 0) ||
            (strcmp(seller_name, "-") != 0 && strcasecmp(phones[i].seller.name, seller_name) != 0) ||
            (minStorage != -1 && phones[i].storage < minStorage) ||
            (maxStorage != -1 && phones[i].storage > maxStorage) ||
            (minPrice != -1 && phones[i].price < minPrice) ||
            (maxPrice != -1 && phones[i].price > maxPrice)) {
            continue;
        }
        printPhone(phones[i]);
        count++;
    }

    if (count == 0) {
        printf("No phones match the given filters.\n");
    } else {
        printf("Total matched: %d\n", count);
    }
}
