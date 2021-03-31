//
//  main.cpp
//  FibonacciHeap
//
//  Created by Rockabye Saw on 24/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
    Node* parent; // Parent pointer
    Node* child; // Child pointer
    Node* left; // Pointer to the Node on the left
    Node* right; // Pointer to the Node on the right
    int key; // Value of the Node
    int degree; // Degree of the Node
    char mark; // Black or white mark of the Node
    char c; // Flag for assisting in the Find Node function
};

struct Node* mini = NULL;

int no_of_Nodes = 0;

void insertion(int val) {
    struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
    new_Node->key = val;
    new_Node->degree = 0;
    new_Node->mark = 'W';
    new_Node->c = 'N';
    new_Node->parent = NULL;
    new_Node->child = NULL;
    new_Node->left = new_Node;
    new_Node->right = new_Node;
    if (mini != NULL) {
        (mini->left)->right = new_Node;
        new_Node->right = mini;
        new_Node->left = mini->left;
        mini->left = new_Node;
        if (new_Node->key < mini->key)
            mini = new_Node;
    }
    else {
        mini = new_Node;
    }
    no_of_Nodes++;
}

void Fibonnaci_link(struct Node* ptr2, struct Node* ptr1) {
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        mini = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}

void Consolidate() {
    int temp1;
    float temp2 = (log(no_of_Nodes)) / (log(2));
    int temp3 = temp2;
    struct Node* arr[temp3];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    Node* ptr1 = mini;
    Node* ptr2;
    Node* ptr3;
    Node* ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL) {
            ptr2 = arr[temp1];
            if (ptr1->key > ptr2->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = NULL;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL) {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

void Extract_min() {
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else {
        Node* temp = mini;
        Node* pntr;
        pntr = temp;
        Node* x = NULL;
        if (temp->child != NULL) {

            x = temp->child;
            do {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        mini = temp->right;
        if (temp == temp->right && temp->child == NULL)
            mini = NULL;
        else {
            mini = temp->right;
            Consolidate();
        }
        no_of_Nodes--;
    }
}

void Cut(struct Node* found, struct Node* temp) {
    if (found == found->right)
        temp->child = NULL;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}

void Cascase_cut(struct Node* temp) {
    Node* ptr5 = temp->parent;
    if (ptr5 != NULL) {
        if (temp->mark == 'W') {
            temp->mark = 'B';
        }
        else {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}

void Decrease_key(struct Node* found, int val)
{
    if (mini == NULL)
        cout << "The Heap is Empty" << endl;

    if (found == NULL)
        cout << "Node not found in the Heap" << endl;

    found->key = val;

    struct Node* temp = found->parent;
    if (temp != NULL && found->key < temp->key) {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key)
        mini = found;
}

void Find(struct Node* mini, int old_val, int val) {
    struct Node* found = NULL;
    Node* temp5 = mini;
    temp5->c = 'Y';
    Node* found_ptr = NULL;
    if (temp5->key == old_val) {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == NULL) {
        if (temp5->child != NULL)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}

void Deletion(int val) {
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else {
        Find(mini, val, 0);

        Extract_min();
        cout << "Key Deleted" << endl;
    }
}

void display()
{
    Node* ptr = mini;
    if (ptr == NULL)
        cout << "The Heap is Empty" << endl;

    else {
        cout << "The root Nodes of Heap are: " << endl;
        do {
            cout << ptr->key;
            ptr = ptr->right;
            if (ptr != mini) {
                cout << "-->";
            }
        } while (ptr != mini && ptr->right != NULL);
        cout << endl
            << "The heap has " << no_of_Nodes << " Nodes" << endl
            << endl;
    }
}

int main() {
    cout << "Creating an initial heap" << endl;
    insertion(5);
    insertion(2);
    insertion(8);

    display();

    cout << "Extracting min" << endl;
    Extract_min();
    display();

    cout << "Decrease value of 8 to 7" << endl;
    Find(mini, 8, 7);
    display();

    cout << "Delete the Node 7" << endl;
    Deletion(7);
    display();

    return 0;
}
