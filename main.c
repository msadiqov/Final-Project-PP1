#include <stdio.h>
#include <stdlib.h>
#include "PhoneManager.h"
#include "PhoneFileService.h"

#define FILE_NAME "phone.txt"

int main() {
    phoneCount = loadFromFile(&phones, FILE_NAME, &capacity);

    int choice;
    do {
        printf("\n========================================================\n");
        printf("\t\tWelcome to PhonetiCode\n");
        printf("========================================================\n");
        printf("\t1>> Add Phone\t\t 2>> List Phones\n");
        printf("\t3>> Search Phone\t 4>> Filter Phones\n");
        printf("\t5>> Sort Phones\t\t 6>> Save & Exit\n");
        printf("=========================================================\n");
        printf("Choose an option (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPhone(); break;
            case 2: listPhones(); break;
            case 3: searchPhones(); break;
            case 4: filterPhones(); break;
            case 5: sortPhones(); break;
            case 6:
                printf("Save changes? (y/n): ");
                char save;
                scanf(" %c", &save);
                if (save == 'y' || save == 'Y') {
                    if (saveToFile(phones, phoneCount, FILE_NAME))
                        printf("Saved successfully.\n");
                    else
                        printf("Failed to save.\n");
                }
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 6);

    free(phones);
    return 0;
}
