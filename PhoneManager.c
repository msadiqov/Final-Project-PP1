#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhoneManager.h"

Phone *phones = NULL;
int phoneCount = 0;
int capacity = 0;

void ensureCapacity() {
    if (phoneCount >= capacity) {
        capacity = capacity == 0 ? 5 : capacity * 2;
        phones = realloc(phones, capacity * sizeof(Phone));
        if (!phones) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
}

void inputPhone(Phone *p) {
    printf("Enter ID: "); scanf("%d", &p->id);
    printf("Enter Brand: "); scanf("%s", p->brand);
    printf("Enter Model: "); scanf("%s", p->model);
    printf("Enter Storage (GB): "); scanf("%d", &p->storage);
    printf("Enter Price: "); scanf("%lf", &p->price);
    printf("Enter Condition (new/used): "); scanf("%s", p->condition);
    printf("Enter Seller Name: "); scanf("%s", p->seller.name);
    printf("Enter Seller Phone: "); scanf("%s", p->seller.phone);
}

void printPhone(const Phone *p) {
    printf("%-6d %-15s %-15s %-12d %-12.2f %-15s %-20s %-15s\n",
           p->id, p->brand, p->model, p->storage, p->price,
           p->condition, p->seller.name, p->seller.phone);
}


void addPhone() {
    ensureCapacity();
    inputPhone(&phones[phoneCount++]);
    printf(">>> Phone added successfully.\n");
}

void listPhones() {
    if (phoneCount == 0) {
        printf("\n  No phones available to display.\n");
        return;
    }

    int newCount = 0, usedCount = 0;

    printf("\n%-6s %-15s %-15s %-12s %-12s %-15s %-20s %-15s\n",
           "ID", "Brand", "Model", "Storage", "Price", "Condition", "Seller Name", "Seller Phone");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < phoneCount; i++) {
        printPhone(&phones[i]);

        if (strcasecmp(phones[i].condition, "new") == 0)
            newCount++;
        else if (strcasecmp(phones[i].condition, "used") == 0)
            usedCount++;
    }

    printf("\n>>>  Total phones: %d\n", phoneCount);
    printf(">>>  New: %d | Used: %d\n", newCount, usedCount);
}


int findIndexById(int id) {
    for (int i = 0; i < phoneCount; i++) {
        if (phones[i].id == id) return i;
    }
    return -1;
}

void editPhone() {
    int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    int index = findIndexById(id);
    if (index == -1) {
        printf("Phone not found.\n");
        return;
    }
    printf("Editing phone ID %d:\n", id);
    inputPhone(&phones[index]);
    printf(">>> Phone updated.\n");
}

void deletePhone() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    int index = findIndexById(id);
    if (index == -1) {
        printf(">>> Phone not found.\n");
        return;
    }
    for (int i = index; i < phoneCount - 1; i++) {
        phones[i] = phones[i + 1];
    }
    phoneCount--;
    printf(">>> Phone deleted.\n");
}

void searchPhones() {
    char term[100];
    printf("Enter search term (brand/model/condition/seller): ");
    scanf("%s", term);
//add asc des and error hand
    int found = 0;
    for (int i = 0; i < phoneCount; i++) {
        if (strstr(phones[i].brand, term) != NULL ||
            strstr(phones[i].model, term) != NULL ||
            strstr(phones[i].condition, term) != NULL ||
            strstr(phones[i].seller.name, term) != NULL) {
            printPhone(&phones[i]);
            printf("1. Edit\t2. Delete\t0. Skip\nChoice: ");
            int c; scanf("%d", &c);
            if (c == 1) inputPhone(&phones[i]);
            else if (c == 2) {
                deletePhone();
                i--; // adjust index after deletion
            }
            found = 1;
        }
    }
    if (!found) printf(">>> No phones found with term '%s'\n", term);
}

void sortPhones() {
    printf("Sort by:\n\t1. Brand\t2. Model\t3. Price\t4. Storage\nChoice: ");
    int c;
    scanf("%d", &c);

    if (c < 1 || c > 4) {
        printf(">>> Invalid choice. Please choose between 1 and 4.\n");
        return;
    }

    for (int i = 0; i < phoneCount - 1; i++) {
        for (int j = i + 1; j < phoneCount; j++) {
            int swap = 0;
            if ((c == 1 && strcmp(phones[i].brand, phones[j].brand) > 0) ||
                (c == 2 && strcmp(phones[i].model, phones[j].model) > 0) ||
                (c == 3 && phones[i].price > phones[j].price) ||
                (c == 4 && phones[i].storage > phones[j].storage)) {
                swap = 1;
            }
            if (swap) {
                Phone tmp = phones[i];
                phones[i] = phones[j];
                phones[j] = tmp;
            }
        }
    }

    printf(">>> Phones sorted successfully.\n");
    listPhones();  //show sorted result
}


void filterPhones() {
    char cond[20], seller[50];
    double minPrice;

    printf("Condition (new/used): ");
    scanf("%s", cond);
    printf("Minimum price: ");
    scanf("%lf", &minPrice);
    printf("Seller name: ");
    scanf("%s", seller);

    int found = 0;
    for (int i = 0; i < phoneCount; i++) {
        if (strcmp(phones[i].condition, cond) == 0 &&
            phones[i].price >= minPrice &&
            strcmp(phones[i].seller.name, seller) == 0) {
            printPhone(&phones[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No phones match the filter criteria.\n");
    }
}
