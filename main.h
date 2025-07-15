#ifndef MAIN_H
#define MAIN_H

#define MAX_LEN 100

typedef struct {
    char name[50];    // Seller full name, e.g., Ali_Mammadov
    char phone[30];   // Seller phone number, e.g., 0501234567
} Seller;

typedef struct {
    int id;
    char brand[30];
    char model[30];
    int storage;         // GB
    double price;
    char condition[15];  // new / used
    Seller seller;       // nested struct
} Phone;

#endif
