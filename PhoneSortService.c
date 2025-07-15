// PhoneManager.c (corrected version)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "PhoneManager.h"
#include "Phone.h"
#include "Seller.h"

Phone *phones = NULL;
int phoneCount = 0;
int capacity = 0;

void ensureCapacity() {
    if (phoneCount >= capacity) {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        phones = realloc(phones, capacity * sizeof(Phone));
        if (!phones) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
}

void inputSeller(Seller* s) {
    printf("Seller name: ");
    scanf(" %[^]", s->name);
    printf("Seller phone: ");
    scanf(" %[^]", s->phone);
}

void inputPhone(Phone* p) {
    printf("ID: ");
    while (scanf("%d", &p->id) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
    }

    printf("Brand: ");
    scanf(" %[^]", p->brand);
    printf("Model: ");
    scanf(" %[^]", p->model);

    printf("Storage (GB): ");
    while (scanf("%d", &p->storage) != 1) {
        printf("Invalid input. Enter a number for storage: ");
        while (getchar() != '\n');
    }

    printf("Price: ");
    while (scanf("%lf", &p->price) != 1) {
        printf("Invalid input. Enter a valid price: ");
        while (getchar() != '\n');
    }

    printf("Condition (New/Used): ");
    scanf(" %[^]", p->condition);

    inputSeller(&p->seller);
}

void printPhone(Phone p) {
    printf("ID: %d\nBrand: %s\nModel: %s\nStorage: %d GB\nPrice: %.2lf\nCondition: %s\nSeller: %s, %s\n\n",
        p.id, p.brand, p.model, p.storage, p.price, p.condition, p.seller.name, p.seller.phone);
}

void addPhone() {
    ensureCapacity();
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

    inputPhone(&p);
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
    if (index >= 0 && index < phoneCount) {
        printf("Editing phone ID %d:\n", phones[index].id);
        inputPhone(&phones[index]);
    }
}

void deletePhoneByIndex(int index) {
    if (index >= 0 && index < phoneCount) {
        for (int j = index; j < phoneCount - 1; j++) {
            phones[j] = phones[j + 1];
        }
        phoneCount--;
        printf("Phone deleted.\n");
    }
}
