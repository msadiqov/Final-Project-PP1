#include <stdio.h>
#include <string.h>
#include "Phone.h"

void inputPhone(Phone *p) {
    printf("Enter ID: ");
    scanf("%d", &p->id);
    printf("Enter Brand: ");
    scanf("%s", p->brand);
    printf("Enter Model: ");
    scanf("%s", p->model);
    printf("Enter Storage (GB): ");
    scanf("%d", &p->storage);
    printf("Enter Price: ");
    scanf("%lf", &p->price);
    printf("Enter Condition (new/used): ");
    scanf("%s", p->condition);
    printf("Enter Seller Name: ");
    scanf("%s", p->seller.name);

}

void printPhone(const Phone *p) {
    printf("ID: %d | %s %s | Storage: %dGB | Price: %.2f | Condition: %s\n",
           p->id, p->brand, p->model, p->storage, p->price, p->condition);
    printf("Seller: %s\n", p->seller.name);
}
