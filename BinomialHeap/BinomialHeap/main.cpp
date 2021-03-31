//
//  main.cpp
//  BinomialHeap
//
//  Created by Rockabye Saw on 18/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <list>

struct Node {
    int data, degree;
    Node *child, *sibling, *parent;
};

Node* createNode(int key) {
    Node *temp = new Node;
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

Node* mergeBinomialTrees(Node* b1, Node* b2) {
    if (b1->data > b2->data)
        std::swap(b1, b2);
    
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    
    return b1;
}

std::list<Node*> unionBionomialHeap(std::list<Node*> l1, std::list<Node*> l2) {
    std::list<Node*> _new;
    std::list<Node*>::iterator it = l1.begin();
    std::list<Node*>::iterator ot = l2.begin();
    
    while (it != l1.end() && ot != l2.end()) {
        if ((*it)->degree <= (*ot)->degree) {
            _new.push_back(*it);
            it++;
        } else {
            _new.push_back(*ot);
            ot++;
        }
    }
    
    while (it != l1.end()) {
        _new.push_back(*it);
        it++;
    }
    
    while (ot != l2.end()) {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}

std::list<Node*> adjust(std::list<Node*> heap) {
    if (heap.size() <= 1)
        return heap;
    
    std::list<Node*> new_heap;
    std::list<Node*>::iterator it1, it2, it3;
    
    it1 = it2 = it3 = heap.begin();
    
    if (heap.size() == 2) {
        it2 = it1;
        it2++;
        it3 = heap.end();
    } else {
        it2++;
        it3 = it2;
        it3++;
    }
    
    while (it1 != heap.end()) {
        if (it2 == heap.end())
            it1++;
        else if ((*it1)->degree < (*it2)->degree) {
            it1++;
            it2++;
            if(it3 != heap.end())
                it3++;
        }
        else if (it3 != heap.end() && (*it1)->degree == (*it2)->degree &&
                 (*it1)->degree == (*it3)->degree) {
            it1++;
            it2++;
            it3++;
        }
        else if ((*it1)->degree == (*it2)->degree) {
            *it1 = mergeBinomialTrees(*it1, *it2);
            it2 = heap.erase(it2);
            if(it3 != heap.end())
                it3++;
        }
    }
    
    return heap;
}

std::list<Node*> insertATreeInHeap(std::list<Node*> heap, Node *tree) {
    std::list<Node*> temp;
  
    temp.push_back(tree);
    temp = unionBionomialHeap(heap,temp);
  
    return adjust(temp);
}

std::list<Node*> removeMinFromTreeReturnBHeap(Node *tree) {
    std::list<Node*> heap;
    Node *temp = tree->child;
    Node *lo;
    
    while (temp) {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        heap.push_front(lo);
    }
    return heap;
}

std::list<Node*> insert(std::list<Node*> head, int key) {
    Node *temp = createNode(key);
    return insertATreeInHeap(head, temp);
}

Node* getMin(std::list<Node*> heap) {
    std::list<Node*>::iterator it = heap.begin();
    
    Node *temp = *it;
    while (it != heap.end()) {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

std::list<Node*> extractMin(std::list<Node*> heap) {
    std::list<Node*> new_heap, lo;
    Node* temp;
    
    temp = getMin(heap);
    std::list<Node*>::iterator it;
    it = heap.begin();
    
    while (it != heap.end()) {
        if (*it != temp) {
            new_heap.push_back(*it);
        }
        it++;
    }
    lo = removeMinFromTreeReturnBHeap(temp);
    new_heap = unionBionomialHeap(new_heap, lo);
    new_heap = adjust(new_heap);
    return new_heap;
}

Node *findNode(Node *h, int val) {
    if (h == NULL)
      return NULL;
  
    if (h->data == val)
        return h;
  
    Node *res = findNode(h->child, val);
    
    if (res != NULL)
       return res;
  
    return findNode(h->sibling, val);
}

void printTree(Node *h) {
    while (h) {
        std::cout << h->data << " ";
        printTree(h->child);
        h = h->sibling;
    }
}
  
void printHeap(std::list<Node*> heap) {
    std::list<Node*> ::iterator it;
    it = heap.begin();
    while (it != heap.end()) {
        printTree(*it);
        it++;
    }
}

int main(int argc, const char * argv[]) {
    int ch, key;
    std::list<Node*> heap;
    
    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 30);
    heap = insert(heap, 40);
    heap = insert(heap, 50);

    std::cout << "Heap elements after insertion:\n";
    printHeap(heap);
    
    Node *temp = getMin(heap);
    std::cout << "\nMinimum element of heap " << temp->data << "\n";
    
    // Delete minimum element of heap
    heap = extractMin(heap);
    std::cout << "Heap after deletion of minimum element\n";
    printTree(heap);
    
    return 0;
}
