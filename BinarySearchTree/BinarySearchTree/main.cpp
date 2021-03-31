//
//  main.cpp
//  BinarySearchTree
//
//  Created by Rockabye Saw on 21/01/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//
//  查找树(BST)主要是左边要小过与父母，而右边则大过。
//  https://www.geeksforgeeks.org/binary-search-tree-data-structure/
//  https://www.geeksforgeeks.org/binary-search-tree-set-3-iterative-delete/
//  https://www.youtube.com/watch?v=gcULXE7ViZw
//  https://www.youtube.com/watch?v=bmaeYtlO2OE
//  https://www.techiedelight.com/deletion-from-bst/
//  https://www.techiedelight.com/search-given-key-in-bst/
//  https://www.techiedelight.com/insertion-in-bst/
#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data);

void insert(Node*& root, int data);
void insertIterative(Node*& root, int data);

Node* deleteNode(Node*& root, int data);
Node* deleteNodeIterative(Node*& root, int data);

Node* findMinNode(Node* node);
Node* findMaxNode(Node* node);

Node* search(Node* root, int data);
void searchIterative(Node* root, int data);

void printInOrder(Node* temp);

int main(int argc, const char * argv[]) {
    Node* root = NULL;
    int keys[] = { 50, 30, 20, 40, 70, 60, 80, 35 };
    
    for (int key : keys)
        insertIterative(root, key);
    
    //searchIterative(root, 8);
    printInOrder(root);
    std::cout << "\nDelete 30\n";
    root = deleteNodeIterative(root, 30);
    std::cout << "Inorder traversal of the modified tree \n";
    printInOrder(root);
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
    return newNode;
}

void insert(Node*& root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return;
    }
    
    if (data < root->data) {
        insert(root->left, data);
    }
    else {
        insert(root->right, data);
    }
}

void insertIterative(Node*& root, int data) {
    Node* curr = root;
    Node* parent = NULL;
    
    if (root == NULL) {
        root = createNode(data);
        return;
    }
    
    while (curr != NULL) {
        parent = curr;
        
        if (data < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    
    if (data < parent->data) {
        parent->left = createNode(data);
    }
    else {
        parent->right = createNode(data);
    }
}

Node* search(Node* root, int data) {
    if(root == NULL || root->data == data) {
        return root;
    }
    
    if (root->data < data)
         return search(root->right, data);
    
    return search(root->left, data);
}

void searchIterative(Node* root, int data) {
    Node* curr = root;
    Node* parent = NULL;
    
    while (curr != NULL && curr->data != data) {
        parent = curr;
        
        if (data < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    
    if (curr == NULL)
    {
        std::cout << "Key Not found";
        return;
    }
    
    if (parent == NULL)
        std::cout << "The node with key " << data << " is root node";
    
    else if (data < parent->data)
        std::cout << "Given key is left node of node with key " << parent->data;
    
    else
        std::cout << "Given key is right node of node with key " << parent->data;
}

Node* deleteNode(Node*& root, int data) {
    if(root == NULL)
        return root;
    
    if(data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if(data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        // node with only one child or no child
        if(root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // node with two children
        // find min node value on right subtree or find max node value on left subtree
        // copy that min node value and replace this node
        // delete duplicate node value
        // successor is number bigger going bigger like right node bigger than parent
        // predecessor is number smaller going smaller like left node bigger than parent
        Node* successor = findMinNode(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

Node* deleteNodeIterative(Node*& root, int data) {
    Node* curr = root;
    Node* parent = NULL;
    
    while (curr != NULL && curr->data != data) {
        parent = curr;
        
        if (data < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    
    if (curr == NULL) {
        std::cout << "Key " << data
             << " not found in the"
             << " provided BST.\n";
        return root;
    }
    
    // Check if the node to be
    // deleted has atmost one child.
    if(curr->left == NULL || curr->right == NULL) {
        Node* newNode;
        
        if (curr->left == NULL)
            newNode = curr->right;
        else
            newNode = curr->left;
        
        if (parent == NULL) {
            return newNode;
        }
        
        if(curr == parent->left) {
            parent->left = curr;
        }
        else {
            parent->right = curr;
        }
        
        delete curr;
    }
    else {
        // node to be deleted has
        // two children.
        Node* parent = NULL;
        Node* temp;
        
        temp = curr->right;
        
        while (temp->left != NULL) {
            parent = temp;
            temp = temp->left;
        }
        
        if (parent != NULL)
            parent->left = temp->right;
        else
            curr->right = temp->right;
        
        curr->data = temp->data;
        delete temp;
    }
    return root;
}


Node* findMinNode(Node* node) {
    Node* curr = node;
    
    while (curr && curr->left != NULL)
        curr = curr->left;
    
    return curr;
}

Node* findMaxNode(Node* node) {
    Node* curr = node;
    
    while (curr && curr->right != NULL)
        curr = curr->right;
    
    return curr;
}

void printInOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    
    printInOrder(temp->left);
    std::cout << temp->data << ' ';
    printInOrder(temp->right);
}
