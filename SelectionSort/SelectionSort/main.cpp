//
//  main.cpp
//  SelectionSort
//
//  Created by Rockabye Saw on 03/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
      int min_idx = step;
      for (int i = step + 1; i < size; i++) {

        if (array[i] < array[min_idx])
          min_idx = i;
      }

      swap(&array[min_idx], &array[step]);
    }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    int data[] = {20, 12, 10, 15, 2};
    int size = sizeof(data) / sizeof(data[0]);
    selectionSort(data, size);
    std::cout << "Sorted array in Acsending Order:\n";
    printArray(data, size);
    return 0;
}
