//
//  main.cpp
//  HashingSeparateChaining
//
//  Created by Rockabye Saw on 10/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <list>

class HashTable {
    int capacity;
    std::list <int> *table;
    
public:
    HashTable(int size);
    void insertItem(int key, int data);
    void deleteItem(int key);
    
    int hashFunction(int key) {
        return (key % capacity);
    }
    
    void displayHash();
};

HashTable::HashTable(int capacity) {
    this->capacity = capacity;
    table = new std::list<int>[capacity];
}

void HashTable::insertItem(int key, int data) {
    int index = hashFunction(key);
    table[index].push_back(data);
}

void HashTable::deleteItem(int key) {
    int index = hashFunction(key);
    std::list<int>::iterator i;
    
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key)
            break;
    }
    
    if (i != table[index].end()) {
        table[index].erase(i);
    }
}

void HashTable::displayHash() {
    std::list<int>::iterator k;

    for (int i = 0; i < capacity; i++) {
        std::cout << "table[" << i << "]";
        for (k = table[i].begin(); k != table[i].end(); k++) {
            std::cout << " --> " << *k;
        }
        std::cout << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    int key[] = {231, 321, 212, 321, 433, 262};
    int data[] = {123, 432, 523, 43, 423, 111};
    int size = sizeof(key) / sizeof(key[0]);
    
    HashTable h(size);

    for (int i = 0; i < size; i++)
      h.insertItem(key[i], data[i]);
    
    h.deleteItem(12);
    h.displayHash();
    
    return 0;
}
