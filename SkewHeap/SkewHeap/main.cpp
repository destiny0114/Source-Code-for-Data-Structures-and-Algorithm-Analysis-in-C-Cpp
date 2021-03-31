//
//  main.cpp
//  SkewHeap
//
//  Created by Rockabye Saw on 17/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

struct SkewHeap {
    int data;
    SkewHeap* right;
    SkewHeap* left;
    
    SkewHeap() {
        data = 0;
        right = NULL;
        left = NULL;
    }
    
    SkewHeap* merge(SkewHeap* root1, SkewHeap* root2) {
        if (root1 == NULL)
            return root2;
        if (root2 == NULL)
            return root1;
        
        SkewHeap* temp;
        
        if (root1->data > root2->data) {
            temp = root1;
            
            root1 = root2;
            root2 = temp;
        }
        
        temp = root1->left;
        
        root1->left = root1->right;
        root1->right = temp;
        
        
        root1->left = merge(root2, root1->left);
        
        return root1;
    }
    
    SkewHeap* construct(SkewHeap* root, int heap[], int n) {
        SkewHeap* temp;
        for (int i = 0; i < n; i++) {
            temp = new SkewHeap;
            temp->data = heap[i];
            root = merge(root, temp);
        }
        return root;
    }
    
    void inorder(SkewHeap* root) {
        if (root == NULL)
            return;
        else {
            inorder(root->left);
            std::cout << root->data << "  ";
            inorder(root->right);
        }
        return;
    }
};

int main(int argc, const char * argv[]) {
    SkewHeap heap, *temp1 = NULL, *temp2 = NULL;
    
    int heap1[] = { 12, 5, 10 };
    int heap2[] = { 3, 7, 8, 14 };
    int n1 = sizeof(heap1) / sizeof(heap1[0]);
    int n2 = sizeof(heap2) / sizeof(heap2[0]);
    temp1 = heap.construct(temp1, heap1, n1);
    temp2 = heap.construct(temp2, heap2, n2);
    
    temp1 = heap.merge(temp1, temp2);
    
    std::cout << "Merged Heap is: " << std::endl;
    heap.inorder(temp1);
    return 0;
}
