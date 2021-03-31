//
//  main.cpp
//  AVLTree
//
//  Created by Rockabye Saw on 29/01/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//
//  AVL是第一个平衡树，平衡树高度不能少过等于1, 如果少过等于1就要使用旋转来达到平衡.
//  相比AVL和红黑树还是建议使用红黑树来插入删除，不过红黑树是没有将严厉的平衡树, 如果是
//  查询就使用AVL。
//  https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
//  https://www.geeksforgeeks.org/avl-tree-set-2-deletion/?ref=lbp
//  https://www.youtube.com/watch?v=jDM6_TnYIqE&t=1294s
//  https://www.youtube.com/watch?v=rbg7Qf8GkQ4&t=1026s

#include <iostream>
#include <stack>

struct Node {
    int height;
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data);
Node* insertNode(Node* node, int data);
Node* deleteNode(Node* node, int data);

Node* rebalance(Node* node, int data);

Node* leftRotate(Node* root);
Node* rightRotate(Node* root);

Node* findMinNode(Node* node);

int max(int a, int b);
int height(Node* node);

int getBalanceFactor(Node* rootLeft, Node* rootRight);

void printPreOrder(Node* temp);

int main(int argc, const char * argv[]) {
    Node* root = NULL;
    int keys[] = { 9, 5, 10, 0, 6, 11, -1, 1, 2 };
    for (int key : keys)
        root = insertNode(root, key);
    
    root = deleteNode(root, 10);
    
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

Node* insertNode(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;
    
    
    node->height = 1 + max(height(node->left), height(node->right));
    // If this node becomes unbalanced, then rebalance it
    int balanceFactor = getBalanceFactor(node->left, node->right);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balanceFactor > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balanceFactor < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* deleteNode(Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = deleteNode(node->left, data);
    else if (data > node->data)
        node->right = deleteNode(node->right, data);
    else {
        // node with only one child or no child
        if(node->left == NULL) {
            Node* temp = node->right;
            
            // No child case
            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else // One child case
                *node = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else if(node->right == NULL) {
            Node* temp = node->left;
            
            // No child case
            if (temp == NULL) {
                temp = node;
                node = NULL;
            }
            else // One child case
                *node = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = findMinNode(node->right);
            
            // Copy the inorder successor's
            // data to this node
            node->data = temp->data;
            
            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }
    }
    
    if (node == NULL)
        return node;
    
    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = getBalanceFactor(node->left, node->right);

    // If this node becomes unbalanced,
    // then there are 4 cases
    
    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(node->left->left, node->left->right) >= 0)
        return rightRotate(node);
    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(node->left->left, node->left->right) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(node->right->right, node->right->left) <= 0)
        return leftRotate(node);
    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(node->right->right, node->right->left) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* rebalance(Node* node, int data) {
    int balanceFactor = getBalanceFactor(node->left, node->right);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balanceFactor > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balanceFactor < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    
    return newRoot;
}

Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    
    return newRoot;
}

Node* findMinNode(Node* node) {
    Node* curr = node;
    
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(Node* rootLeft, Node* rootRight) {
    return height(rootLeft) - height(rootRight);
}

void printPreOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    std::cout << temp->data << ' ';
    printPreOrder(temp->left);
    printPreOrder(temp->right);
}
