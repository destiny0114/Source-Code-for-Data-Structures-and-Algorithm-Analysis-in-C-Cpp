//
//  main.cpp
//  BinaryTree
//
//  Created by Rockabye Saw on 19/01/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//
//  二叉树(Binary Tree)是每个节点不能多过两个孩子。
//  二叉树遍历方法有DFS和BFS。
//  DFS分成-
//  PreOrder root-left-right
//  InOrder left-root-right
//  PostOrder left-right-root
//  DFS编写最好用Stack,而BFS是Queue
//  https://en.wikipedia.org/wiki/Tree_traversal
#include <iostream>
#include <stack>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data);

void printPreOrder(Node* temp);
void printInOrder(Node* temp);
void printPostOrder(Node* temp);

void printLevelOrder(Node* root);
void printGivenLevel(Node* root, int level);
int maxDepth(Node* node);

void iterativePreOrder(Node* temp);
void iterativeInOrder(Node* temp);
void iterativePostOrder(Node* temp);

void iterativeLevelOrder(Node* root);

int main(int argc, const char * argv[]) {
    Node* root = createNode(10);
    root->left = createNode(11);
    root->left->left = createNode(7);
    root->right = createNode(9);
    root->right->left = createNode(15);
    root->right->right = createNode(8);
    //      10
    //  11      9
    // 7       15   8
    //
    printPostOrder(root);
    iterativePostOrder(root);
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
// DFS
void printPreOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    
    std::cout << temp->data << ' ';
    printPreOrder(temp->left);
    printPreOrder(temp->right);
}

void printInOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    
    printInOrder(temp->left);
    std::cout << temp->data << ' ';
    printInOrder(temp->right);
}

void printPostOrder(Node* temp) {
    if (temp == NULL) {
        return;
    }
    
    printPostOrder(temp->left);
    printPostOrder(temp->right);
    std::cout << temp->data << ' ';
}
// BFS
void printLevelOrder(Node* root) {
    int h = maxDepth(root);
    int i;
    for (i = 1; i <= h; i++)
        printGivenLevel(root, i);
}

void printGivenLevel(Node* root, int level) {
    if(root == NULL)
        return;
    
    if(level == 1)
        std::cout << root->data << ' ';
    else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

int maxDepth(Node* node) {
    if (node == NULL)
        return 0;
    else
    {
        int ldepth = maxDepth(node->left);
        int rdepth = maxDepth(node->right);
        
        if (ldepth > rdepth)
            return ldepth + 1;
        else return rdepth + 1;
    }
}
// Iterative DFS Travesal Without Recursion
void iterativePreOrder(Node* temp) {
    if (temp == NULL)
        return;
    
    std::stack<Node*> stack;
    stack.push(temp);
    
    while (!stack.empty()) {
        Node* curr = stack.top();
        stack.pop();
        
        std::cout << curr->data << " ";
        
        if(curr->right != NULL)
            stack.push(curr->right);
        
        if(curr->left != NULL)
            stack.push(curr->left);
        
        // important note - right child is pushed first so that left child
        // is processed first (FIFO order)
    }
}

void iterativeInOrder(Node* temp) {
    if (temp == NULL)
        return;
    
    std::stack<Node*> stack;
    Node* curr = temp;
    
    while (!stack.empty() || curr != NULL) {
        if (curr != NULL) {
            stack.push(curr);
            curr = curr->left;
        } else {
            curr = stack.top();
            stack.pop();
            std::cout << curr->data << " ";
            curr = curr->right;
        }
    }
}

void iterativePostOrder(Node* temp) {
    if(temp == NULL)
        return;
    
    std::stack<Node*> stack;
    std::stack<Node*> output;
    Node* curr = temp;
    
    stack.push(curr);
    
    while (!stack.empty()) {
        Node* curr = stack.top();
        stack.pop();
        
        output.push(curr);
        
        if(curr->left != NULL)
            stack.push(curr->left);
        
        if(curr->right != NULL)
            stack.push(curr->right);
    }
    
    while (!output.empty()) {
        curr = output.top();
        output.pop();
        std::cout << curr->data << " ";
    }
    
    // important node - https://www.geeksforgeeks.org/iterative-postorder-traversal/
}
// Iterative BFS Travesal Without Recursion
void iterativeLevelOrder(Node* root) {
    if(root == NULL)
        return;
    
    std::queue<Node*> queue;
    Node* curr = root;
    queue.push(curr);
    
    do {
        curr = queue.front();
        queue.pop();
        
        std::cout << curr->data << " ";

        if(curr->left != NULL)
            queue.push(curr->left);
        
        if(curr->right)
            queue.push(curr->right);

    } while (!queue.empty());
}
