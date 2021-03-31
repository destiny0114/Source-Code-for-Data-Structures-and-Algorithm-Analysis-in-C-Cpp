//
//  main.cpp
//  HeapSort
//
//  Created by Rockabye Saw on 23/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

void heapify(int arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);

    heapify(arr, i, 0);
  }
}

void printArray(int arr[], int n) {
  for (int i = 0; i < n; ++i)
    std::cout << arr[i] << " ";
  std::cout << "\n";
}

int main(int argc, const char * argv[]) {
    int arr[] = {1, 12, 9, 5, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, n);
    
    std::cout << "Sorted array is \n";
    printArray(arr, n);
    
    return 0;
}
