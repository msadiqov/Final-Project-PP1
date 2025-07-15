// Phone.h
#ifndef PHONE_H
#define PHONE_H

typedef struct Seller {
    char name[50];
    // other fields if any
} Seller;

typedef struct Phone {
    int id;
    char brand[50];
    char model[50];
    int storage;
    double price;
    char condition[20];
    Seller seller;
} Phone;

void printPhone(const Phone *p);  // change here to const

void inputPhone(Phone *p);  // input can remain non-const

#endif
