//
//  main.cpp
//  BubbleSort
//
//  Created by Rockabye Saw on 03/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

void bubbleSort(int array[], int size) {
  for (int step = 0; step < size - 1; ++step) {
    int swapped = 0;
    for (int i = 0; i < size - step - 1; ++i) {
      if (array[i] > array[i + 1]) {
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        swapped = 1;
      }
    }
    if (swapped == 0)
      break;
  }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    std::cout << "  " << array[i];
  }
  std::cout << "\n";
}

int main(int argc, const char * argv[]) {
    int data[] = {-2, 45, 0, 11, -9};
    int size = sizeof(data) / sizeof(data[0]);
    bubbleSort(data, size);
    std::cout << "Sorted Array in Ascending Order:\n";
    printArray(data, size);
    return 0;
}
