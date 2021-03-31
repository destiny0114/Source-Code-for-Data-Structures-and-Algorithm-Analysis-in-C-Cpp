//
//  main.cpp
//  LeftistHeap
//
//  Created by Rockabye Saw on 17/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

struct Node {
    int data;
    Node *left;
    Node *right;
    int dist;
};

Node* createNode(int data) {
    Node *temp = new Node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->dist = 0;
    return temp;
}

void swapChildren(Node* root) {
    Node* temp = root->right;
    root->right = root->left;
    root->left = temp;
}

Node* merge(Node* root1, Node* root2) {
    if (!root1)
        return root2;
    
    if (!root2)
        return root1;
    
    if (root1->data < root2->data) {
        if (root1->left == NULL) {
            root1->left = root2;
            return root1;
        }
        else {
            root1->right = merge(root1->right, root2);
            
            if (root1->left->dist < root1->right->dist)
                swapChildren(root1);
            
            root1->dist = 1 + root1->right->dist;
            return root1;
        }
    }
    else {
        if (root2->left == NULL) {
            root2->left = root1;
            return root2;
        }
        else {
            root2->right = merge(root1, root2->right);
            
            if (root2->left->dist < root2->right->dist)
                swapChildren(root2);
            
            root2->dist = 1 + root2->right->dist;
            return root2;
        }
    }
}

Node* insert(Node* root, int data) {
    Node* temp = createNode(data);
    return merge(root, temp);
}

void deleteMin(Node *&root, int &x) {
    x = root->data;
    root = merge(root->left,root->right);
}

int main(int argc, const char * argv[]) {
    Node* h=NULL;
    Node* h1=NULL;
    Node* h2=NULL;
    int x;
    int arr[]= {1, 5, 7, 10, 15};
    int arr1[]= {22, 75};
    
    h = insert(h,arr[0]);
    h = insert(h,arr[1]);;
    h = insert(h,arr[2]);
    h = insert(h,arr[3]);
    h = insert(h,arr[4]);
    h1 = insert(h1,arr1[0]);
    h1 = insert(h1,arr1[1]);
    
    deleteMin(h,x);
    std::cout<< x << std::endl;
    
    deleteMin(h1,x);
    std::cout << x << std::endl;
    
    h = merge(h,h1);
    h2 = h;
    
    deleteMin(h2,x);
    std::cout << x << std::endl;
    
    return 0;
}
