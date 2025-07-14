// PhoneManager.c (update)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "PhoneManager.h"
#include "Phone.h"

Phone phones[MAX_PHONES];
int phoneCount = 0;

void addPhone() {
    Phone p;
    int exists;
    do {
        exists = 0;
        printf("ID: ");
        if (scanf("%d", &p.id) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        for (int i = 0; i < phoneCount; i++) {
            if (phones[i].id == p.id) {
                exists = 1;
                printf("ID already exists. Enter a different ID.\n");
                break;
            }
        }
    } while (exists);

    printf("Brand: ");
    scanf(" %[^\n]", p.brand);
    printf("Model: ");
    scanf(" %[^\n]", p.model);
    printf("Storage (GB): ");
    scanf("%d", &p.storage);
    printf("Price: ");
    scanf("%lf", &p.price);
    printf("Condition (New/Used): ");
    scanf(" %[^\n]", p.condition);
    inputSeller(&p.seller);


    phones[phoneCount++] = p;
    printf("Phone added.\n");
}

void listPhones() {
    printf("\nTotal phones: %d\n", phoneCount);
    for (int i = 0; i < phoneCount; i++) {
        printPhone(phones[i]);
    }
}

void editPhoneByIndex(int index) {
    printf("Editing phone ID %d:\n", phones[index].id);
    inputPhone(&phones[index]);
}

void deletePhoneByIndex(int index) {
    for (int j = index; j < phoneCount - 1; j++) {
        phones[j] = phones[j + 1];
    }
    phoneCount--;
    printf("Phone deleted.\n");
}
