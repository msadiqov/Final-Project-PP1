#include <stdio.h>
#include "Phone.h"

void inputPhone(Phone *p) {
    printf("ID: ");
    scanf("%d", &p->id);
    printf("Brand: ");
    scanf(" %[^\n]", p->brand);
    printf("Model: ");
    scanf(" %[^\n]", p->model);
    printf("Storage (GB): ");
    scanf("%d", &p->storage);
    printf("Price: ");
    scanf("%lf", &p->price);
    printf("Condition (New/Used): ");
    scanf(" %[^\n]", p->condition);
    inputSeller(&p->seller);
}

void printPhone(Phone p) {
    printf("\n--- Phone ID %d ---\n", p.id);
    printf("Brand: %s\n", p.brand);
    printf("Model: %s\n", p.model);
    printf("Storage: %d GB\n", p.storage);
    printf("Price: %.2f\n", p.price);
    printf("Condition: %s\n", p.condition);
    printSeller(p.seller);
}
