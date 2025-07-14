// PhoneStore.c - Main menu with save confirmation
#include <stdio.h>
#include <stdlib.h>
#include "Phone.h"
#include "PhoneManager.h"
#include "PhoneFileService.h"
#include "PhoneSearchService.h"
#include "PhoneFilterService.h"
#include "PhoneSortService.h"

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