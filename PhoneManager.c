#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhoneManager.h"
#include "Phone.h"

// Dinamik massiv üçün global dəyişənlər
Phone *phones = NULL;
int phoneCount = 0;
int capacity = 0;

// Yaddaşın genişlənməsi
void ensureCapacity() {
    if (phoneCount >= capacity) {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        Phone *tmp = realloc(phones, capacity * sizeof(Phone));
        if (tmp == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        phones = tmp;
    }
}

// Yeni telefon əlavə etmə funksiyası
void addPhone() {
    ensureCapacity();
    Phone p;
    printf("Enter phone ID: ");
    while (scanf("%d", &p.id) != 1) {
        printf("Invalid input! Enter an integer for ID: ");
        while (getchar() != '\n'); // buffer təmizlənir
    }
    while (1) {
        int duplicate = 0;
        for (int i = 0; i < phoneCount; i++) {
            if (phones[i].id == p.id) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            printf("ID already exists. Enter a unique ID: ");
            while (scanf("%d", &p.id) != 1) {
                printf("Invalid input! Enter an integer for ID: ");
                while (getchar() != '\n');
            }
        } else {
            break;
        }
    }

    printf("Brand: ");
    scanf(" %49[^\n]", p.brand);
    printf("Model: ");
    scanf(" %49[^\n]", p.model);

    printf("Storage (GB): ");
    while (scanf("%d", &p.storage) != 1) {
        printf("Invalid input! Enter an integer for storage: ");
        while (getchar() != '\n');
    }

    printf("Price: ");
    while (scanf("%lf", &p.price) != 1) {
        printf("Invalid input! Enter a number for price: ");
        while (getchar() != '\n');
    }

    printf("Condition (New/Used): ");
    scanf(" %19[^\n]", p.condition);

    printf("Seller name: ");
    scanf(" %49[^\n]", p.seller.name);
    printf("Seller phone: ");
    scanf(" %19[^\n]", p.seller.phone);

    phones[phoneCount++] = p;
    printf("Phone added successfully!\n");
}

// Bütün telefonları listələmə
void listPhones() {
    printf("Total phones: %d\n", phoneCount);
    for (int i = 0; i < phoneCount; i++) {
        printf("ID: %d\nBrand: %s\nModel: %s\nStorage: %d GB\nPrice: %.2lf\nCondition: %s\nSeller: %s, %s\n\n",
            phones[i].id, phones[i].brand, phones[i].model, phones[i].storage,
            phones[i].price, phones[i].condition, phones[i].seller.name, phones[i].seller.phone);
    }
}

// Telefonu indexə görə redaktə etmə
void editPhoneByIndex(int index) {
    if (index < 0 || index >= phoneCount) {
        printf("Invalid index for editing.\n");
        return;
    }
    printf("Editing phone with ID %d\n", phones[index].id);

    printf("New Brand: ");
    scanf(" %49[^\n]", phones[index].brand);

    printf("New Model: ");
    scanf(" %49[^\n]", phones[index].model);

    printf("New Storage (GB): ");
    while (scanf("%d", &phones[index].storage) != 1) {
        printf("Invalid input! Enter an integer for storage: ");
        while (getchar() != '\n');
    }

    printf("New Price: ");
    while (scanf("%lf", &phones[index].price) != 1) {
        printf("Invalid input! Enter a number for price: ");
        while (getchar() != '\n');
    }

    printf("New Condition (New/Used): ");
    scanf(" %19[^\n]", phones[index].condition);

    printf("New Seller name: ");
    scanf(" %49[^\n]", phones[index].seller.name);

    printf("New Seller phone: ");
    scanf(" %19[^\n]", phones[index].seller.phone);

    printf("Phone updated successfully!\n");
}

// Telefonu indexə görə silmə
void deletePhoneByIndex(int index) {
    if (index < 0 || index >= phoneCount) {
        printf("Invalid index for deletion.\n");
        return;
    }
    for (int i = index; i < phoneCount - 1; i++) {
        phones[i] = phones[i + 1];
    }
    phoneCount--;
    printf("Phone deleted successfully!\n");
}
