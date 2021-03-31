//
//  main.cpp
//  InsertionSort
//
//  Created by Rockabye Saw on 22/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

void insertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        
        int j = i - 1;
        
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    int data[] = {9, 5, 1, 4, 3};
    int size = sizeof(data) / sizeof(data[0]);
    insertionSort(data, size);
    std::cout << "Sorted array in ascending order:\n";
    printArray(data, size);
    return 0;
}
