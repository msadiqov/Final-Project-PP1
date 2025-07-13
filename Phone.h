#ifndef PHONE_H
#define PHONE_H

#include "Seller.h"

typedef struct {
    int id;
    char brand[50];
    char model[50];
    int storage;
    double price;
    char condition[20]; // New / Used
    Seller seller;
} Phone;

void inputPhone(Phone *p);
void printPhone(Phone p);

#endif
