//
//  main.cpp
//  D-Heap
//
//  Created by Rockabye Saw on 16/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <vector>
//全局函数指定多少分叉树，这里是5，代表5叉树。
int k = 5;

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int parent(int i) { return (i - 1) / 2; }

int child(int i, int n) { return (k * i) + n; }

template<typename T>
int getMax(std::vector<T>& heap, int i, int size) {
    T largest = heap[i];
    int childIndex = 0;
    int tempIndex = i;
    
    for(int j = 0; j < k - 1; j++) {
        childIndex = child(i, j);
        
        if(childIndex < size && heap[childIndex] > largest) {
            largest = heap[childIndex];
            tempIndex = childIndex;
        }
    }
    
    return tempIndex;
}

template<typename T>
int getMin(std::vector<T>& heap, int i, int size) {
    T largest = heap[i];
    int childIndex = 0;
    int tempIndex = i;
    
    for(int j = 0; j < k - 1; j++) {
        childIndex = child(i, j);
        
        if(childIndex < size && heap[childIndex] < largest) {
            largest = heap[childIndex];
            tempIndex = childIndex;
        }
    }
    
    return tempIndex;
}

template<typename T>
void maxHeapify(std::vector<T>& heap, int i, int size) {
    if (i < size) {
        int tempIndex = getMax(heap, i, size);
        
        if (tempIndex != i) {
            swap(&heap[i], &heap[tempIndex]);
            maxHeapify(heap, tempIndex, size);
        }
    }
}

template<typename T>
void minHeapify(std::vector<T>& heap, int i, int size) {
    if (i < size) {
        int tempIndex = getMin(heap, i, size);
        
        if (tempIndex != i) {
            swap(&heap[i], &heap[tempIndex]);
            minHeapify(heap, tempIndex, size);
        }
    }
}

template<typename T>
void buildHeap(std::vector<T>& heap) {
    for(int i = (heap.size() - 1) / k; i >= 0; i--)
        maxHeapify(heap, i, heap.size());
    
}


template<typename T>
void heapSort(std::vector<T>& heap) {
    buildHeap(heap);
    for(int i = heap.size() - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        maxHeapify(heap, 0, i);
    }
}


template<typename T>
void printHeap(const std::vector<T>& heap) {
    for(auto x : heap) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    std::vector<int> heap {2,4,7,1,4,8,9,31,83,28,48,94,87,16,36};

    std::cout << "Befor build heap:\n";
    printHeap(heap);
    
    buildHeap(heap);
    std::cout << "After build heap:\n";
    printHeap(heap);
    
//    std::cout << "After sort:\n";
//    heapSort(heap);
//    printHeap(heap);

    return 0;
}
