//
//  main.c
//  Polynomial 多项式
//  链表里面的每个node里面有coeff和power,然后两个链表进行加法或乘法
//  https://www.geeksforgeeks.org/adding-two-polynomials-using-linked-list/
//  https://www.geeksforgeeks.org/multiplication-of-two-polynomials-using-linked-list/?ref=rp
//  Created by Rockabye Saw on 07/04/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//
// 5x^2 = 5x = coeff ^2 = pow
// Addtion Polynomial
// if the 1st poly pow is same with 2nd poly pow then add coeff together
// if the 1st poly pow not same with 2nd poly put into new poly (answer)
// 1st Polynomial - 5x^2 + 4x^1 + 2
// 2nd Polynomial - 5x^1 + 5
// Answer - 5x^2 + 9x^1 + 7

// Multiplication Polynomial
// the 1st poly first number need to seperate multiply 2nd poly then keep
// going at 1st poly second number and third also
// then all combine like solution below
// 1st Polynomial - 3x^2 + 5x^1 + 6
// 2nd Polynomial - 6x^1 + 8
// (3x^2 x 6x^1) + (3x^2 x 8) = 18^3 + 24^2
// (5x^1 x 6x^1) + (5x^1 x 8) = 30^2 + 40^1
// (6 x 6x^1) + (6 x 8) = 36^1 + 48
// 18^3 + 24^2 + 30^2 + 40^1 + 36^1 + 48
// Answer - 18^3 + 54^2 + 76^1 + 48
#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;
typedef PtrToNode Poly;

struct Node
{
    int coeff;
    int pow;
    Position next;
};

void create_node(int x, int y, Position* temp);
void showaddanswer(List l);
void showmultiplyanswer(List l);

Poly polyadd(Poly poly1, Poly poly2);
void swapnum(int *num1, int *num2);
void removeDuplicates(Position* start);
Poly multiply(Poly poly1, Poly poly2, Poly poly3);


int main(int argc, const char * argv[]) {
    
    Poly poly1 = NULL, poly2 = NULL, poly = NULL;
    // int v1 = 56, v2 = 87;
    // swapnum(&v1, &v2);
      
//    // Create first list of 5x^2 + 4x^1 + 2x^0
//    create_node(5,2,&poly1);
//    create_node(4,1,&poly1);
//    create_node(2,0,&poly1);
//
//    // Create second list of 5x^1 + 5x^0
//    create_node(5,1,&poly2);
//    create_node(5,0,&poly2);
//    create_node(7,3,&poly2);
//
//    printf("1st Number: ");
//    showaddanswer(poly1);
//
//    printf("\n2nd Number: ");
//    showaddanswer(poly2);
//
//    poly = polyadd(poly1, poly2);
//
//    // Display resultant List
//    printf("\nAdded polynomial: ");
//    showaddanswer(poly);
    
    create_node(3, 3, &poly1);
    create_node(6, 1, &poly1);
    create_node(9, 0, &poly1);

    create_node(9, 3, &poly2);
    create_node(8, 2, &poly2);
    create_node(7, 1, &poly2);
    create_node(2, 0, &poly2);

    printf("1st Number: ");
    showmultiplyanswer(poly1);

    printf("\n2nd Number: ");
    showmultiplyanswer(poly2);

    poly = multiply(poly1, poly2, poly);

    // Display resultant List
    printf("\nMultipled polynomial: ");
    showmultiplyanswer(poly);
    
    return 0;
}

void create_node(int x, int y, Position* temp)
{
    Position r, z;
    z = *temp;
    if(z == NULL)
    {
        r =malloc(sizeof(struct Node));
        r->coeff = x;
        r->pow = y;
        *temp = r;
        
        r->next = malloc(sizeof(struct Node));
        r = r->next;
        r->next = NULL;
    }
    else
    {
        r->coeff = x;
        r->pow = y;
        r->next = malloc(sizeof(struct Node));
        r = r->next;
        r->next = NULL;
    }
}

Poly polyadd(Poly poly1, Poly poly2)
{
    Poly res = NULL;
    Poly poly = NULL;
    
    while(poly1 && poly2)
    {
        Position tmp = malloc(sizeof(struct Node));
        if(poly) {
            poly->next = tmp;
        } else {
            res = tmp;
        }
        poly = tmp;
        poly->next = NULL;
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is
        // and move its pointer
        if(poly1->pow > poly2->pow)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }
        
        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is
        // and move its pointer
        else if(poly1->pow < poly2->pow)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }
        
        // If power of both polynomial numbers is same then add their coefficients
        else
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff+poly2->coeff;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        
        // Dynamically create new node
    }
    // if poly1 or poly2 have left meaning 7x^3 add the left into poly
    while(poly1 || poly2)
    {
        Position tmp = malloc(sizeof(struct Node));
        if(poly) {
            poly->next = tmp;
        } else {
            res = tmp;
        }
        poly = tmp;
        poly->next = NULL;
        if(poly1->next)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }
        if(poly2->next)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }
    }
    
    return res;
}

void showaddanswer(List l)
{
    while(l->next != NULL)
    {
        printf("%dx^%d", l->coeff, l->pow);
        l = l->next;
        if(l->next != NULL)
            printf(" + ");
    }
    
    
}

void showmultiplyanswer(List l)
{
    while(l->next != NULL)
    {
        printf("%dx^%d", l->coeff, l->pow);
        l = l->next;
        if(l->next != NULL)
            printf(" + ");
    }
    
    if(l->coeff != 0)
        printf(" + %d\n",l->coeff);
}

void swapnum(int *num1, int *num2)
{
    int tempnum;
    
    tempnum = *num1;
    printf("%d", *num1);  // Ouptut: 1
    *num1 = *num2;
    *num2 = tempnum;
}

void removeDuplicates(Position* start)
{
    Position ptr1, ptr2, dup;
    ptr1 = *start;
  
    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
  
        // Compare the picked element
        // with rest of the elements
        while (ptr2->next != NULL) {
  
            // If powerer of two elements are same
            if (ptr1->pow == ptr2->next->pow) {
  
                // Add their coefficients and put it in 1st element
                ptr1->coeff = ptr1->coeff + ptr2->next->coeff;
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
  
                // remove the 2nd element
                free(dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

Poly multiply(Poly poly1, Poly poly2, Poly poly3)
{
    // Create two pointer and store the
    // address of 1st and 2nd polynomials
    Position ptr1, ptr2;
    ptr1 = poly1;
    ptr2 = poly2;
    while (ptr1 != NULL) {
        while (ptr2 != NULL) {
            int coeff, power;
            
            // Multiply the coefficient of both
            // polynomials and store it in coeff
            coeff = ptr1->coeff * ptr2->coeff;
            
            // Add the powerer of both polynomials
            // and store it in power
            power = ptr1->pow + ptr2->pow;
            
            // Invoke addnode function to create
            // a newnode by passing three parameters
            create_node(coeff, power, &poly3);
            
            // move the pointer of 2nd polynomial
            // two get its next term
            ptr2 = ptr2->next;
        }
        
        // Move the 2nd pointer to the
        // starting point of 2nd polynomial
        ptr2 = poly2;
        
        // move the pointer of 1st polynomial
        ptr1 = ptr1->next;
    }
    
    // this function will be invoke to add
    // the coefficient of the elements
    // having same powerer from the resultant linked list
    removeDuplicates(&poly3);
    return poly3;
}


