//
//  main.cpp
//  ShellSort
//
//  Created by Rockabye Saw on 22/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

void shellSort(int array[], int n) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = array[i];
            int j;
            
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}

void printArray(int array[], int size) {
  int i;
  for (i = 0; i < size; i++)
    std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    int data[] = {9, 8, 3, 7, 5, 6, 4, 1};
    int size = sizeof(data) / sizeof(data[0]);
    shellSort(data, size);
    std::cout << "\nArray after sorting: \n";
    printArray(data, size);
    
    return 0;
}
