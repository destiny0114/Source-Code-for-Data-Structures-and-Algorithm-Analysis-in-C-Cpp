//
//  main.cpp
//  BucketSort
//
//  Created by Rockabye Saw on 02/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <iomanip>

#define NARRAY 7   // Array size
#define NBUCKET 6  // Number of buckets
#define INTERVAL 10  // Each bucket capacity

struct Node {
    int data;
    struct Node* next;
};

void bucketSort(int arr[]);
struct Node* insertionSort(struct Node* list);
void print(int arr[]);
void printBuckets(struct Node* list);
int getBucketIndex(int value);

void bucketSort(int arr[]) {
    int i, j;
    struct Node** buckets;
    
    buckets = (struct Node**)malloc(sizeof(struct Node*) * NBUCKET);

    for (i = 0; i < NBUCKET; ++i) {
      buckets[i] = NULL;
    }
    
    for (i = 0; i < NARRAY; ++i) {
        struct Node* current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node*)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }
    
    for (i = 0; i < NBUCKET; i++) {
      std::cout << "Bucket[" << i << "] : ";
      printBuckets(buckets[i]);
      std::cout << std::endl;
    }
    
    for (i = 0; i < NBUCKET; ++i) {
      buckets[i] = insertionSort(buckets[i]);
    }

    std::cout << "-------------" << std::endl;
    std::cout << "Bucktets after sorted" << std::endl;
    for (i = 0; i < NBUCKET; i++) {
      std::cout << "Bucket[" << i << "] : ";
      printBuckets(buckets[i]);
      std::cout << std::endl;
    }
    
    for (j = 0, i = 0; i < NBUCKET; ++i) {
      struct Node *node;
      node = buckets[i];
      while (node != NULL) {
        arr[j++] = node->data;
        node = node->next;
      }
    }
    
    for (i = 0; i < NBUCKET; ++i) {
      struct Node *node;
      node = buckets[i];
      while (node) {
        struct Node *tmp;
        tmp = node;
        node = node->next;
        free(tmp);
      }
    }
    free(buckets);
    return;
}

struct Node* insertionSort(struct Node* list) {
    struct Node* k;
    struct Node* nodeList;
    
    if (list == NULL || list->next == NULL) {
      return list;
    }
    
    nodeList = list;
    k = list->next;
    nodeList->next = NULL;
    
    while (k != NULL) {
        struct Node* ptr;
        
        if (nodeList->data > k->data) {
            struct Node* temp;
            temp = k;
            k = k->next;
            temp->next = nodeList;
            nodeList = temp;
            continue;
        }
        
        for (ptr = nodeList; ptr->next != NULL; ptr = ptr->next) {
          if (ptr->next->data > k->data)
            break;
        }
        
        if (ptr->next != NULL) {
          struct Node* temp;
          temp = k;
          k = k->next;
          temp->next = ptr->next;
          ptr->next = temp;
          continue;
        } else {
          ptr->next = k;
          k = k->next;
          ptr->next->next = NULL;
          continue;
        }
    }
    
    return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}

void print(int ar[]) {
  int i;
  for (i = 0; i < NARRAY; ++i) {
    std::cout << std::setw(3) << ar[i];
  }
  std::cout << std::endl;
}

void printBuckets(struct Node *list) {
  struct Node *cur = list;
  while (cur) {
    std::cout << std::setw(3) << cur->data;
    cur = cur->next;
  }
}

int main(int argc, const char * argv[]) {
    int array[NARRAY] = {42, 32, 33, 52, 37, 47, 51};

    std::cout << "Initial array: " << std::endl;
    print(array);
    std::cout << "-------------" << std::endl;

    bucketSort(array);
    std::cout << "-------------" << std::endl;
    std::cout << "Sorted array: " << std::endl;
    print(array);
    return 0;
}
