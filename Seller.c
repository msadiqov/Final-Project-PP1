#include <stdio.h>
#include "Seller.h"

void inputSeller(Seller *s) {
    printf("Seller name: ");
    scanf(" %[^\n]", s->name);
    printf("Seller phone: ");
    scanf(" %[^\n]", s->phone);
}

void printSeller(Seller s) {
    printf("Seller: %s (%s)\n", s.name, s.phone);
}
