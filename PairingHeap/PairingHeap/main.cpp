//
//  main.cpp
//  PairingHeap
//
//  Created by Rockabye Saw on 31/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

using namespace std;

// Heap structure
struct HeapNode {
    int key;
    HeapNode *leftChild;
    HeapNode *nextSibling;

    HeapNode():
        leftChild(NULL), nextSibling(NULL) {}

    // creates a new node
    HeapNode(int key_, HeapNode *leftChild_, HeapNode *nextSibling_):
        key(key_), leftChild(leftChild_), nextSibling(nextSibling_) {}
        
        // Adds a child and sibling to the node
    void addChild(HeapNode *node) {
        if(leftChild == NULL)
            leftChild = node;
        else {
            node->nextSibling = leftChild;
            leftChild = node;
        }
    }
};

// Returns true if root of the tree
// is null otherwise returns false
bool Empty(HeapNode *node) {
    return (node == NULL);
}

// Function to merge two heaps
HeapNode *Merge(HeapNode *A, HeapNode *B)
{
    // If any of the two-nodes is null
    // the return the not null node
    if(A == NULL) return B;
    if(B == NULL) return A;
    
    // To maintain the min heap condition compare
    // the nodes and node with minimum value become
    // parent of the other node
    if(A->key < B->key) {
        A->addChild(B);
        return A;
    }
    else {
        B->addChild(A);
        return B;
    }

    return NULL; // Unreachable
}

// Returns the root value of the heap
int Top(HeapNode *node) {
    return node->key;
}

// Function to insert the new node in the heap
HeapNode *Insert(HeapNode *node, int key) {
    return Merge(node, new HeapNode(key, NULL, NULL));
}

// This method is used when we want to delete root node
HeapNode *TwoPassMerge(HeapNode *node) {
    if(node == NULL || node->nextSibling == NULL)
        return node;
    else {
        HeapNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = NULL;
        B->nextSibling = NULL;

        return Merge(Merge(A, B), TwoPassMerge(newNode));
    }

    return NULL; // Unreachable
}

// Function to delete the root node in heap
HeapNode *Delete(HeapNode *node) {
    return TwoPassMerge(node->leftChild);
}

struct PairingHeap {
    HeapNode *root;

    PairingHeap():
        root(NULL) {}

    bool Empty(void) {
        return ::Empty(root);
    }

    int Top(void) {
        return ::Top(root);
    }

    void Insert(int key) {
        root = ::Insert(root, key);
    }

    void Delete(void) {
        root = ::Delete(root);
    }

    void Join(PairingHeap other) {
        root = ::Merge(root, other.root);
    }
    
};

// Driver Code
int main(void) {

    PairingHeap heap1, heap2;
    heap2.Insert(5);
    heap2.Insert(2);

    heap2.Insert(6);
    heap1.Insert(1);
    heap1.Insert(3);
    heap1.Insert(4);
    
    heap1.Join(heap2);
    
    cout << heap1.Top() << endl;
    heap1.Delete();

    cout << heap1.Top() << endl;
    cout<< (heap1.Empty()?"True":"False");
    
    return 0;
}

