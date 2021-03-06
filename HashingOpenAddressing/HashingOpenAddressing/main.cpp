//
//  main.cpp
//  HashingOpenAddressing
//
//  Created by Rockabye Saw on 10/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

template<typename K, typename V>

class HashNode
{
public:
    V value;
    K key;
      
    HashNode(K key, V value) {
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>

class HashMap {
    HashNode<K, V>** arr;
    int capacity;
    int size;
    HashNode<K, V>* dummy;
    
public:
    HashMap() {
        capacity = 20;
        size = 0;
        arr = new HashNode<K,V>*[capacity];
          
        for(int i = 0 ; i < capacity ; i++)
            arr[i] = NULL;
          
        dummy = new HashNode<K, V>(-1, -1);
    }
    
    int hashCode(K key) {
        return key % capacity;
    }
    
    void insertNode(K key, V value) {
        HashNode<K, V>* temp = new HashNode<K, V>(key, value);
        
        int hashIndex = hashCode(key);
        
        while(arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1) {
            hashIndex++;
            hashIndex %= capacity;
        }
        
        if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
            size++;
        
        arr[hashIndex] = temp;
    }
    
    V deleteNode(int key) {
        int hashIndex = hashCode(key);
        
        while(arr[hashIndex] != NULL) {
            if(arr[hashIndex]->key == key) {
                HashNode<K, V> *temp = arr[hashIndex];
                
                arr[hashIndex] = dummy;
                
                size--;
                return temp->value;
            }
            
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
    
    V search(int key) {
        int hashIndex = hashCode(key);
        
        while(arr[hashIndex] != NULL) {
            if(arr[hashIndex]->key == key)
                return arr[hashIndex]->value;
            
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
    
    int sizeofMap() {
        return size;
    }
      
    bool isEmpty() {
        return size == 0;
    }
    
    void display() {
        for(int i = 0 ; i < capacity; i++) {
            if(arr[i] != NULL && arr[i]->key != -1)
                std::cout << "key = " << arr[i]->key
                     << "  value = "<< arr[i]->value << std::endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    HashMap<int, int> *h = new HashMap<int, int>;
    h->insertNode(1, 76);
    h->insertNode(2, 93);
    h->insertNode(3, 40);
    h->insertNode(3, 3);
    
    h->display();
    std::cout << h->search(1) << std::endl;

    return 0;
}
