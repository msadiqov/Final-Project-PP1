#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhoneManager.h"
#include "Phone.h"
#include "PhoneFileService.h"
#define MAX_PHONES 1000


void loadPhonesFromFile() {
    FILE *fp = fopen(PHONE_FILENAME, "r");
    if (fp == NULL) {
        printf("No existing phone data found. Starting fresh.\n");
        return;
    }

    phoneCount = 0;
    while (fscanf(fp, "%d,%49[^,],%49[^,],%d,%lf,%19[^,],%49[^,],%19[^\n]\n",
                  &phones[phoneCount].id,
                  phones[phoneCount].brand,
                  phones[phoneCount].model,
                  &phones[phoneCount].storage,
                  &phones[phoneCount].price,
                  phones[phoneCount].condition,
                  phones[phoneCount].seller.name,
                  phones[phoneCount].seller.phone) == 8) {
        phoneCount++;
        if (phoneCount >= MAX_PHONES) break;
    }

    fclose(fp);
    printf("%d phones loaded from file.\n", phoneCount);
}

void savePhonesToFile() {
    FILE *fp = fopen(PHONE_FILENAME, "w");
    if (fp == NULL) {
        printf("Error saving to file.\n");
        return;
    }

    for (int i = 0; i < phoneCount; i++) {
        fprintf(fp, "%d,%s,%s,%d,%.2f,%s,%s,%s\n",
                phones[i].id,
                phones[i].brand,
                phones[i].model,
                phones[i].storage,
                phones[i].price,
                phones[i].condition,
                phones[i].seller.name,
                phones[i].seller.phone);
    }

    fclose(fp);
    printf("Phones saved to file '%s'.\n", PHONE_FILENAME);
}
