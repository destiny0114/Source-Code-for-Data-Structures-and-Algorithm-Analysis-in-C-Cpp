//
//  main.cpp
//  SplayTree
//
//  Created by Rockabye Saw on 01/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

struct Node {
    int height;
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data);
Node* insertNode(Node* root, int data);
Node* deleteNode(Node* root, int data);

Node* leftRotate(Node* root);
Node* rightRotate(Node* root);

Node* splay(Node* root, int data);
Node* search(Node* root, int data);

void printPreOrder(Node* temp);

int main(int argc, const char * argv[]) {
    Node* root = createNode(100);
    root->left = createNode(50);
    root->right = createNode(200);
    root->left->left = createNode(40);
    root->left->left->left = createNode(30);
    root->left->left->left->left = createNode(20);
    
    root = insertNode(root, 25);
    root = deleteNode(root, 25);

    root = search(root, 20);
    std::cout << "Preorder traversal of the modified Splay tree is \n";
    printPreOrder(root);
    return 0;
}

Node* createNode(int data) {
    Node* newNode = new Node();
    
    if(!newNode) {
        std::cout << "Memory error\n";
        return NULL;
    }
    
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    root = splay(root, data);
    
    if (root->data == data) {
        return root;
    }
    
    Node* newNode = createNode(data);
    
    if (root->data > data) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    }
    else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }
    return newNode;
}

Node* deleteNode(Node* root, int data) {
    Node* temp = NULL;
    
    if (!root)
        return NULL;
    
    root = splay(root, data);
    
    if (data != root->data)
        return root;
    
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        
        root = splay(root->left, data);
        
        root->right = temp->right;
    }
    free(temp);
    
    return root;
}

Node* search(Node* root, int data) {
    return splay(root, data);
}

Node *splay(Node *root, int data) {
    if (root == NULL || root->data == data)
        return root;
    // Key lies in left subtree
    if (root->data > data) {
        if (root->left == NULL) return root;
        
        // Zig-Zig (Left Left)
        if (root->left->data > data) {
            root->left->left = splay(root->left->left, data);
            
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (root->left->data < data) {
            root->left->right = splay(root->left->right, data);
            
            if (root->left->right != NULL) {
                root->left = leftRotate(root->left);
            }
        }
        
        if (root->left == NULL) {
            return root;
        }
        else {
            root = rightRotate(root);
        }
    }
    // Key lies in right subtree
    else {
        if (root->right == NULL) return root;
        
        // Zag-Zag (Right Right)
        if (root->right->data < data) {
            root->right->right = splay(root->right->right, data);
            
            root = leftRotate(root);
        }
        // Zag-Zig (Right Left)
        else if (root->right->data > data) {
            root->right->left = splay(root->right->left, data);
            
            if (root->right->left != NULL) {
                root->right = rightRotate(root->right);
            }
        }
        
        if (root->right == NULL) {
            return root;
        }
        else {
            root = leftRotate(root);
        }
    }
    return root;
}

Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    
    return newRoot;
}

Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    
    return newRoot;
}

void printPreOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    std::cout << temp->data << ' ';
    printPreOrder(temp->left);
    printPreOrder(temp->right);
}
