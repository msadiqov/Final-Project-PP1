#include <stdio.h>
#include <string.h>
#include "PhoneManager.h"
#include "Phone.h"

Phone phones[MAX_PHONES];
int phoneCount = 0;

void addPhone() {
    if (phoneCount < MAX_PHONES) {
        inputPhone(&phones[phoneCount]);
        phoneCount++;
        printf("Phone added.\n");
    } else {
        printf("Phone list full.\n");
    }
}

void listPhones() {
    for (int i = 0; i < phoneCount; i++) {
        printPhone(phones[i]);
    }
}

void editPhone() {
    int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    for (int i = 0; i < phoneCount; i++) {
        if (phones[i].id == id) {
            printf("Editing phone ID %d:\n", id);
            inputPhone(&phones[i]);
            return;
        }
    }
    printf("Phone not found.\n");
}

void deletePhone() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < phoneCount; i++) {
        if (phones[i].id == id) {
            for (int j = i; j < phoneCount - 1; j++) {
                phones[j] = phones[j + 1];
            }
            phoneCount--;
            printf("Phone deleted.\n");
            return;
        }
    }
    printf("Phone not found.\n");
}
