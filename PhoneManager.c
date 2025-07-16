#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
                                        //*************************************LISTING***************** 
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

                        //*********************************************SEARCHING********************************* */

// Helper function to check if a string is already in the list
int isInList(char list[][50], int size, const char *value) {
    for (int i = 0; i < size; i++) {
        if (strcasecmp(list[i], value) == 0) return 1;
    }
    return 0;
}

void listDistinctValues(const char *field) {
    char distinct[100][50];
    int count = 0;

    for (int i = 0; i < phoneCount; i++) {
        const char *val = NULL;
        if (strcmp(field, "id") == 0) {
            char buf[20];
            sprintf(buf, "%d", phones[i].id);
            val = buf;
        } else if (strcmp(field, "brand") == 0) val = phones[i].brand;
        else if (strcmp(field, "model") == 0) val = phones[i].model;
        else if (strcmp(field, "storage") == 0) {
            static char buf[20];
            sprintf(buf, "%d", phones[i].storage);
            val = buf;
        } else if (strcmp(field, "price") == 0) {
            static char buf[20];
            sprintf(buf, "%.2f", phones[i].price);
            val = buf;
        } else if (strcmp(field, "condition") == 0) val = phones[i].condition;
        else if (strcmp(field, "seller") == 0) val = phones[i].seller.name;

        // Check if already in distinct list
        if (val && !isInList(distinct, count, val)) {
            strncpy(distinct[count], val, 49);
            distinct[count][49] = '\0';
            count++;
        }
    }

    printf("Existing values for '%s':\n", field);
    for (int i = 0; i < count; i++) {
        printf(" - %s\n", distinct[i]);
    }
}

void searchPhones() {
    if (phoneCount == 0) {
        printf(">>> No phones available.\n");
        return;
    }

    char key[20];
    const char *allowedFields[] = {"id", "brand", "model", "storage", "price", "condition", "seller"};

    // Choose field
    while (1) {
        printf("\nSearch by (id/brand/model/storage/price/condition/seller): ");
        scanf("%s", key);

        for (int i = 0; key[i]; i++) key[i] = tolower(key[i]);

        int valid = 0;
        for (int i = 0; i < 7; i++) {
            if (strcmp(key, allowedFields[i]) == 0) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            printf(">>> Invalid field. Try again.\n");
        } else break;
    }

    while (1) {
        char value[100];
        printf("Enter value (or 'exit' to quit): ");
        getchar(); // clear leftover newline
        fgets(value, sizeof(value), stdin);
        value[strcspn(value, "\n")] = '\0';

        if (strcasecmp(value, "exit") == 0) {
            printf("Exiting search.\n");
            break;
        }

        int foundCount = 0;
        for (int i = 0; i < phoneCount; i++) {
            Phone *p = &phones[i];
            int match = 0;

            if (strcmp(key, "id") == 0 && atoi(value) == p->id) match = 1;
            else if (strcmp(key, "brand") == 0 && strcasecmp(p->brand, value) == 0) match = 1;
            else if (strcmp(key, "model") == 0 && strcasecmp(p->model, value) == 0) match = 1;
            else if (strcmp(key, "storage") == 0 && atoi(value) == p->storage) match = 1;
            else if (strcmp(key, "price") == 0 && atof(value) == p->price) match = 1;
            else if (strcmp(key, "condition") == 0 && strcasecmp(p->condition, value) == 0) match = 1;
            else if (strcmp(key, "seller") == 0 && strcasecmp(p->seller.name, value) == 0) match = 1;

            if (match) {
                printf("\n");
                printPhone(p);
                foundCount++;
            }
        }

        if (foundCount == 0) {
            printf(">>> No matches found for '%s'.\n", value);
            listDistinctValues(key);
            printf("Try again or type 'exit' to quit.\n");
        } else {
            printf("\n>>> Found %d match(es).\n", foundCount);
            // You can add edit/delete choice here if you want
            break;
        }
    }
}



                                       // ************************************SORTING****************************
void sortPhones() {
    char field[20], order[10];
    int ascending = 1;

    printf("Sort by (id/brand/model/price/storage/condition/seller): ");
    scanf("%s", field);
    printf("Order (asc/desc): ");
    scanf("%s", order);

    if (strcasecmp(order, "desc") == 0) {
        ascending = 0;
    } else if (strcasecmp(order, "asc") != 0) {
        printf(">>> Invalid sort order. Use 'asc' or 'desc'.\n");
        return;
    }

    // Normalize field
    for (int i = 0; field[i]; i++) {
        field[i] = tolower(field[i]);
    }

    int valid = 1;

    for (int i = 0; i < phoneCount - 1; i++) {
        for (int j = i + 1; j < phoneCount; j++) {
            int cmp = 0;

            if (strcmp(field, "id") == 0) {
                cmp = phones[i].id - phones[j].id;
            } else if (strcmp(field, "brand") == 0) {
                cmp = strcasecmp(phones[i].brand, phones[j].brand);
            } else if (strcmp(field, "model") == 0) {
                cmp = strcasecmp(phones[i].model, phones[j].model);
            } else if (strcmp(field, "price") == 0) {
                cmp = (phones[i].price > phones[j].price) ? 1 : (phones[i].price < phones[j].price) ? -1 : 0;
            } else if (strcmp(field, "storage") == 0) {
                cmp = phones[i].storage - phones[j].storage;
            } else if (strcmp(field, "condition") == 0) {
                cmp = strcasecmp(phones[i].condition, phones[j].condition);
            } else if (strcmp(field, "seller") == 0) {
                cmp = strcasecmp(phones[i].seller.name, phones[j].seller.name);
            } else {
                valid = 0;
                break;
            }

            if ((ascending && cmp > 0) || (!ascending && cmp < 0)) {
                Phone tmp = phones[i];
                phones[i] = phones[j];
                phones[j] = tmp;
            }
        }
        if (!valid) break;
    }

    if (!valid) {
        printf(">>> Invalid sort field. Please try again.\n");
        return;
    }

    printf(">>> Phones sorted by %s (%s):\n", field, ascending ? "ASC" : "DESC");
    listPhones();
}


                              //****************************************FILTERING****************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void filterPhones() {
    char brand[50] = "", model[50] = "", condition[20] = "", sellerName[50] = "";
    char minPriceStr[20], maxPriceStr[20], storageStr[20];

    printf("\n--- FILTER PHONES ---\n");
    printf("Leave blank (just press Enter) to skip a field.\n");

    printf("Brand: ");
    fgets(brand, sizeof(brand), stdin);
    brand[strcspn(brand, "\n")] = 0;

    printf("Model: ");
    fgets(model, sizeof(model), stdin);
    model[strcspn(model, "\n")] = 0;

    printf("Condition (New/Used): ");
    fgets(condition, sizeof(condition), stdin);
    condition[strcspn(condition, "\n")] = 0;

    printf("Min Price: ");
    fgets(minPriceStr, sizeof(minPriceStr), stdin);
    minPriceStr[strcspn(minPriceStr, "\n")] = 0;

    printf("Max Price: ");
    fgets(maxPriceStr, sizeof(maxPriceStr), stdin);
    maxPriceStr[strcspn(maxPriceStr, "\n")] = 0;

    printf("Storage (GB): ");
    fgets(storageStr, sizeof(storageStr), stdin);
    storageStr[strcspn(storageStr, "\n")] = 0;

    printf("Seller Name: ");
    fgets(sellerName, sizeof(sellerName), stdin);
    sellerName[strcspn(sellerName, "\n")] = 0;

    // Parse numbers
    double minPrice = strlen(minPriceStr) == 0 ? 0.0 : atof(minPriceStr);
    double maxPrice = strlen(maxPriceStr) == 0 ? 1e9 : atof(maxPriceStr);
    int storage = strlen(storageStr) == 0 ? -1 : atoi(storageStr);

    // Header
    printf("\n%-6s %-15s %-15s %-12s %-12s %-15s %-20s %-15s\n",
           "ID", "Brand", "Model", "Storage", "Price", "Condition", "Seller Name", "Seller Phone");
    printf("------------------------------------------------------------------------------------------------------------\n");

    int count = 0, newCount = 0, usedCount = 0;

    for (int i = 0; i < phoneCount; i++) {
        Phone *p = &phones[i];

        if (strlen(brand) > 0 && strcasecmp(p->brand, brand) != 0) continue;
        if (strlen(model) > 0 && strcasecmp(p->model, model) != 0) continue;
        if (strlen(condition) > 0 && strcasecmp(p->condition, condition) != 0) continue;
        if (p->price < minPrice || p->price > maxPrice) continue;
        if (storage != -1 && p->storage != storage) continue;
        if (strlen(sellerName) > 0 && strcasecmp(p->seller.name, sellerName) != 0) continue;

        printf("%-6d %-15s %-15s %-12d %-12.2f %-15s %-20s %-15s\n",
               p->id, p->brand, p->model, p->storage, p->price, p->condition, p->seller.name, p->seller.phone);

        count++;
        if (strcasecmp(p->condition, "new") == 0) newCount++;
        else if (strcasecmp(p->condition, "used") == 0) usedCount++;
    }

    if (count == 0) {
        printf("No matching phones found.\n");
    } else {
        printf("\n>>> Filtered phones: %d\n", count);
        printf(">>> New: %d | Used: %d\n", newCount, usedCount);
    }
}
