#ifndef SELLER_H
#define SELLER_H

typedef struct {
    char name[50];
    char phone[20];
} Seller;

void inputSeller(Seller *s);
void printSeller(Seller s);

#endif
