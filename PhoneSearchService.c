// PhoneSearchService.c - Full search with delete/edit options
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "PhoneManager.h"
#include "Phone.h"

void printPhone(Phone p);
void editPhoneByIndex(int index);
void deletePhoneByIndex(int index);

void searchPhone() {
    if (phoneCount == 0) {
        printf("No phones available.\n");
        return;
    }

    char field[20], value[50];
    printf("Search by (id/brand/model/storage/price/condition/seller_name/seller_phone): ");
    scanf(" %s", field);
    printf("Enter value: ");
    scanf(" %[^]", value);

    int found = 0;
    for (int i = 0; i < phoneCount; i++) {
        int match = 0;
        if (strcmp(field, "id") == 0 && atoi(value) == phones[i].id)
            match = 1;
        else if (strcmp(field, "brand") == 0 && strcasecmp(value, phones[i].brand) == 0)
            match = 1;
        else if (strcmp(field, "model") == 0 && strcasecmp(value, phones[i].model) == 0)
            match = 1;
        else if (strcmp(field, "storage") == 0 && atoi(value) == phones[i].storage)
            match = 1;
        else if (strcmp(field, "price") == 0 && atof(value) == phones[i].price)
            match = 1;
        else if (strcmp(field, "condition") == 0 && strcasecmp(value, phones[i].condition) == 0)
            match = 1;
        else if ((strcmp(field, "seller_name") == 0 || strcmp(field, "seller") == 0) && strcasecmp(value, phones[i].seller.name) == 0)
            match = 1;
        else if (strcmp(field, "seller_phone") == 0 && strcmp(value, phones[i].seller.phone) == 0)
            match = 1;

        if (match) {
            found = 1;
            printf("\nMatch found at index %d:\n", i);
            printPhone(phones[i]);
            printf("Do you want to delete (d), edit (e), or skip (n)? ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'd') {
                deletePhoneByIndex(i);
                break;
            } else if (choice == 'e') {
                editPhoneByIndex(i);
                break;
            }
        }
    }
    if (!found) {
        printf("No matchig phones found.\n");
    }
}
