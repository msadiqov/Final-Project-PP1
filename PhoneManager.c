#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhoneManager.h"
#include "Phone.h"

void addPhone(Phone **phones, int *count, int *capacity) {
    if (*count >= *capacity) {
        *capacity *= 2;
        *phones = realloc(*phones, (*capacity) * sizeof(Phone));
    }
    inputPhone(&(*phones)[*count]);
    (*count)++;
}

void listPhones(Phone *phones, int count) {
    printf("\n--- Phone List (%d total) ---\n", count);
    for (int i = 0; i < count; i++) {
        printPhone(&phones[i]);
    }
}

void editPhone(Phone *phones, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (phones[i].id == id) {
            printf("Editing phone with ID %d\n", id);
            inputPhone(&phones[i]);
            printf("Phone updated.\n");
            return;
        }
    }
    printf("Phone not found.\n");
}

void deletePhone(Phone *phones, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (phones[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                phones[j] = phones[j + 1];
            }
            (*count)--;
            printf("Phone deleted.\n");
            return;
        }
    }
    printf("Phone not found.\n");
}
