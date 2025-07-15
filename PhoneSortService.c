// PhoneSortService.c - Sort by any field ASC/DESC with error handling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Phone.h"
#include "PhoneManager.h"

char sortField[20];
int sortAsc;

// Compare two phones based on a given field and sort direction (asc/desc)
int comparePhones(const void* a, const void* b, const char* field, int asc) {
    const Phone* p1 = (const Phone*)a;
    const Phone* p2 = (const Phone*)b;
    int result = 0;

    if (strcmp(field, "id") == 0)
        result = p1->id - p2->id;
    else if (strcmp(field, "storage") == 0)
        result = p1->storage - p2->storage;
    else if (strcmp(field, "price") == 0)
        result = (p1->price > p2->price) - (p1->price < p2->price);
    else if (strcmp(field, "brand") == 0)
        result = strcasecmp(p1->brand, p2->brand);
    else if (strcmp(field, "model") == 0)
        result = strcasecmp(p1->model, p2->model);
    else if (strcmp(field, "condition") == 0)
        result = strcasecmp(p1->condition, p2->condition);
    else if (strcmp(field, "seller") == 0 || strcmp(field, "seller_name") == 0)
        result = strcasecmp(p1->seller.name, p2->seller.name);
    else if (strcmp(field, "seller_phone") == 0)
        result = strcmp(p1->seller.phone, p2->seller.phone);

    return asc ? result : -result;
}

int sortComparator(const void* a, const void* b) {
    return comparePhones(a, b, sortField, sortAsc);
}

// Minimal check if the sort order is valid
int isValidField(const char* field) {
    const char* validFields[] = {
        "id", "brand", "model", "storage", "price", "condition", "seller", "seller_name", "seller_phone"
    };
    int n = sizeof(validFields) / sizeof(validFields[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(field, validFields[i]) == 0)
            return 1;
    }
    return 0;
}

void sortPhones() {
    if (phoneCount == 0) {
        printf("No phones to sort.\n");
        return;
    }

    printf("Sort by (id/brand/model/storage/price/condition/seller/seller_phone): ");
    scanf(" %19s", sortField);

    if (!isValidField(sortField)) {
        printf("Error: Invalid field '%s'. Sorting aborted.\n", sortField);
        return;
    }

    printf("Order (asc/desc): ");
    char order[10];
    scanf(" %9s", order);

    if (strcmp(order, "asc") != 0 && strcmp(order, "desc") != 0) {
        printf("Error: Invalid sort order '%s'. Use 'asc' or 'desc'.\n", order);
        return;
    }

    sortAsc = (strcmp(order, "asc") == 0);
    
     // Perform sorting
    qsort(phones, phoneCount, sizeof(Phone), sortComparator);
    printf("✅ Phones sorted by %s (%s):\n", sortField, order);
    for (int i = 0; i < phoneCount; i++) {
        printPhone(phones[i]);
    }
}


