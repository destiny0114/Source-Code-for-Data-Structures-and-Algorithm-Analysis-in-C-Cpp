//
//  main.cpp
//  BinaryHeap
//
//  Created by Rockabye Saw on 15/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <vector>

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int parent(int i) { return (i - 1) / 2; }

int left(int i) { return (2 * i + 1); }

int right(int i) { return (2 * i + 2); }

void maxHeapify(std::vector<int> &heap, int i) {
    int size = heap.size();
    int largest = i;
    
    int l = left(i);
    int r = right(i);
    
    if (l < size && heap[l] > heap[largest])
        largest = l;
    if (r < size && heap[r] > heap[largest])
        largest = r;
    
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, largest);
    }
}

void minHeapify(std::vector<int> &heap, int i) {
    int size = heap.size();
    int smallest = i;
    
    int l = left(i);
    int r = right(i);
    
    if (l < size && heap[l] < heap[smallest])
        smallest = l;
    if (r < size && heap[r] < heap[smallest])
        smallest = r;
    
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, smallest);
    }
}

int extractMin(std::vector<int> &heap) {
    int size = heap.size();
    
    if (size <= 0)
        return INT_MAX;
    if (size == 1) {
        size--;
        return heap[0];
    }
    
    int root = heap.front();
    heap.front() = heap[heap.size() - 1];
    heap.pop_back();

    minHeapify(heap, 0);
    return root;
}

int extractMax(std::vector<int> &heap) {
    int size = heap.size();
    
    if (size <= 0)
        return INT_MAX;
    if (size == 1) {
        size--;
        return heap[0];
    }
    
    int root = heap.front();
    heap.front() = heap[heap.size() - 1];
    heap.pop_back();

    maxHeapify(heap, 0);
    return root;
}

void decreaseKey(std::vector<int> &heap, int i, int data) {
    heap[i] = data;
    while (i != 0 && heap[parent(i)] > heap[i]) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

void increaseKey(std::vector<int> &heap, int i, int data) {
    if (data < heap[i])
        return;
    
    heap[i] = data;
    while (i > 1 && heap[parent(i)] < heap[i]) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

void insert(std::vector<int> &heap, int data) {
//    int size = heap.size();
//
//    if (size == 0) {
//        heap.push_back(data);
//    }
//    else {
//        heap.push_back(data);
//
//        for (int i = size / 2 - 1; i >= 0; i--) {
            // Max Priority Queue
            //maxHeapify(heap, i);
            // Min Priority Queue
            //minHeapify(heap, i);
//        }
//    }
    heap.push_back(data);
    
    // Max Priority Queue
    //increaseKey(heap, heap.size() - 1, data);
    // Min Priority Queue
    decreaseKey(heap, heap.size() - 1, data);
}

void deleteNode(std::vector<int> &heap, int data) {
    int size = heap.size();
    int i;
    for (i = 0; i < size; i++) {
      if (data == heap[i])
        break;
    }
    swap(&heap[i], &heap[size - 1]);

    heap.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--) {
        // Max Priority Queue
        //maxHeapify(heap, i);
        // Min Priority Queue
        minHeapify(heap, i);
    }
}

void deleteKey(std::vector<int> &heap, int i) {
    decreaseKey(heap, i, INT_MIN);
    // Max Priority Queue
    //extractMax(heap);
    // Min Priority Queue
    extractMin(heap);
}

void printArray(std::vector<int> &heap) {
  for (int i = 0; i < heap.size(); ++i)
    std::cout << heap[i] << " ";
  std::cout << "\n";
}

int main(int argc, const char * argv[]) {
    std::vector<int> heap;

    insert(heap, 3);
    insert(heap, 4);
    insert(heap, 9);
    insert(heap, 5);
    insert(heap, 2);
    insert(heap, 10);
    deleteKey(heap, 1);
    
    printArray(heap);
    return 0;
}
