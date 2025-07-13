#include <stdio.h>
#include "PhoneManager.h"
#include "PhoneFileService.h"

void searchByBrand();

void menu() {
    int choice;
    do {
        printf("\n=== PHONE STORE MENU ===\n");
        printf("1. Add Phone\n");
        printf("2. List Phones\n");
        printf("3. Search by Brand\n");
        printf("4. Edit Phone\n");
        printf("5. Delete Phone\n");
        printf("6. Save & Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPhone(); break;
            case 2: listPhones(); break;
            case 3: searchByBrand(); break;
            case 4: editPhone(); break;
            case 5: deletePhone(); break;
            case 6:
                savePhonesToFile();
                printf("Exiting and saving data...\n");
                break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

int main() {
    loadPhonesFromFile();
    menu();
    return 0;
}
