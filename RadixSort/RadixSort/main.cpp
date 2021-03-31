//
//  main.cpp
//  RadixSort
//
//  Created by Rockabye Saw on 03/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

int getMax(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

void countingSort(int array[], int size, int place) {
    int output[10];
    int count[10];
    int max = 10;
    
    for (int i = 0; i <= max; ++i) {
      count[i] = 0;
    }
    
    for (int i = 0; i < size; i++) {
        count[(array[i] / place) % 10]++;
    }
    
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }
    
    for (int i = 0; i < size; i++) {
      array[i] = output[i];
    }
}

void radixSort(int array[], int size) {
  int max = getMax(array, size);

  for (int place = 1; max / place > 0; place *= 10)
    countingSort(array, size, place);
}

void printArray(int array[], int size) {
  int i;
  for (i = 0; i < size; i++)
    std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    int array[] = {121, 432, 564, 23, 1, 45, 788};
    int n = sizeof(array) / sizeof(array[0]);
    radixSort(array, n);
    printArray(array, n);
    return 0;
}
