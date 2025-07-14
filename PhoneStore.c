// PhoneStore.c - Main menu with save confirmation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Phone.h"

#define MAX 100

Phone *phones = NULL;
int phoneCount = 0;

// Load phones from file
void loadPhonesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    phones = malloc(sizeof(Phone) * MAX);
    while (fread(&phones[phoneCount], sizeof(Phone), 1, file)) {
        phoneCount++;
    }
    fclose(file);
}

// Save phones to file
void savePhonesToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < phoneCount; i++) {
        fwrite(&phones[i], sizeof(Phone), 1, file);
    }
    fclose(file);
}

// Add a phone
void addPhone() {
    phones = realloc(phones, sizeof(Phone) * (phoneCount + 1));

    printf("Enter brand: ");
    scanf("%s", phones[phoneCount].brand);

    printf("Enter model: ");
    scanf("%s", phones[phoneCount].model);

    printf("Enter price: ");
    scanf("%f", &phones[phoneCount].price);

    printf("Enter RAM (GB): ");
    scanf("%d", &phones[phoneCount].specs.ram);

    printf("Enter storage (GB): ");
    scanf("%d", &phones[phoneCount].specs.storage);

    printf("Enter screen size (inches): ");
    scanf("%f", &phones[phoneCount].specs.screenSize);

    phoneCount++;
    printf("Phone added successfully!\n");
}

// List all phones
void listPhones() {
    for (int i = 0; i < phoneCount; i++) {
        printf("%d. %s %s - $%.2f [%dGB RAM, %dGB Storage, %.1f\"]\n",
            i + 1,
            phones[i].brand,
            phones[i].model,
            phones[i].price,
            phones[i].specs.ram,
            phones[i].specs.storage,
            phones[i].specs.screenSize);
    }
}

// Search phone by model
void searchPhone() {
    char model[50];
    printf("Enter model to search: ");
    scanf("%s", model);
    for (int i = 0; i < phoneCount; i++) {
        if (strcmp(phones[i].model, model) == 0) {
            printf("Found: %s %s - $%.2f\n", phones[i].brand, phones[i].model, phones[i].price);
            return;
        }
    }
    printf("Phone not found.\n");
}

// Filter phones by min price
void filterPhones() {
    float minPrice;
    printf("Enter minimum price: ");
    scanf("%f", &minPrice);
    for (int i = 0; i < phoneCount; i++) {
        if (phones[i].price >= minPrice) {
            printf("%s %s - $%.2f\n", phones[i].brand, phones[i].model, phones[i].price);
        }
    }
}

// Sort phones by price ascending
void sortPhones() {
    for (int i = 0; i < phoneCount - 1; i++) {
        for (int j = i + 1; j < phoneCount; j++) {
            if (phones[i].price > phones[j].price) {
                Phone temp = phones[i];
                phones[i] = phones[j];
                phones[j] = temp;
            }
        }
    }
    printf("Phones sorted by price (ascending).\n");
}

void menu() {
    int choice;
    do {
        printf("\n=== PHONE STORE MENU ===\n");
        printf("1. Add Phone\n");
        printf("2. List Phones\n");
        printf("3. Search Phone\n");
        printf("4. Filter Phones\n");
        printf("5. Sort Phones\n");
        printf("6. Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: addPhone(); break;
            case 2: listPhones(); break;
            case 3: searchPhone(); break;
            case 4: filterPhones(); break;
            case 5: sortPhones(); break;
            case 6:
                printf("Do you want to save changes to file before exit? (y/n): ");
                char save;
                scanf(" %c", &save);
                if (save == 'y' || save == 'Y') {
                    savePhonesToFile("phone.txt");
                    printf("Changes saved.\n");
                } else {
                    printf("Changes discarded.\n");
                }
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);
}

int main() {
    loadPhonesFromFile("phone.txt");
    menu();
    free(phones);
    return 0;
}
