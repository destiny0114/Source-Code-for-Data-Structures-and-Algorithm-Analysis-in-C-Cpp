//
//  main.cpp
//  B-Tree
//
//  Created by Rockabye Saw on 02/02/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

class BTreeNode {
private:
    int *keys;
    int t;
    BTreeNode** Children;
    int n;
    bool leaf;
    
public:
    BTreeNode(int temp, bool bool_leaf);
    
    void insertNonFull(int k);
    void splitChildren(int i, BTreeNode* y);
    void traverse();
    
    int findKey(int k);
    void deletion(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    
    BTreeNode* search(int k);
    
    friend class BTree;
};

class BTree {
private:
    BTreeNode* root;
    int t;
    
public:
    BTree(int temp) {
        root = NULL;
        t = temp;
    }
    
    void traverse() {
        if (root != NULL)
            root->traverse();
    }
    
    BTreeNode* search(int k) {
        if (root == NULL) {
            return NULL;
        }
        return root->search(k);
    }
    
    void insertNode(int k);
    void deleteNode(int k);
};


int main(int argc, const char * argv[]) {
    BTree tree(3);
    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(12);
    tree.insertNode(30);
    tree.insertNode(7);
    tree.insertNode(17);
    
    tree.deleteNode(10);
    tree.deleteNode(7);
    tree.deleteNode(30);
    std::cout << "Traversal of the constucted tree is ";
    tree.traverse();
    return 0;
}

BTreeNode::BTreeNode(int temp, bool bool_leaf) {
    t = temp;
    leaf = bool_leaf;
    
    keys = new int[2 * t - 1];
    Children = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false) {
            Children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    
    if (leaf == false) {
        Children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    
    if (keys[i] == k)
        return this;
    
    if (leaf == true)
        return NULL;
    
    return Children[i]->search(k);
}

void BTree::insertNode(int k) {
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->Children[0] = root;
            s->splitChildren(0, root);
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->Children[i]->insertNonFull(k);
            
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

void BTree::deleteNode(int k) {
    if (!root) {
        std::cout << "The tree is empty\n";
        return;
    }
    
    root->deletion(k);
    
    if (root->n == 0) {
        BTreeNode* temp = root;
        
        if (root->leaf)
          root = NULL;
        else
          root = root->Children[0];

        delete temp;
    }
    return;
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
          keys[i + 1] = keys[i];
          i--;
        }
        
        keys[i + 1] = k;
        n = n + 1;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;
        
        if (Children[i + 1]->n == 2 * t - 1) {
            splitChildren(i + 1, Children[i + 1]);
            
            if (keys[i + 1] < k)
                i++;
        }
        Children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChildren(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    
    if (y->leaf == false) {
        for (int j = 0; i < t; j++)
            z->Children[j] = y->Children[j + t];
    }

    y->n = t - 1;
    
    for (int j = n; j >= i + 1; j--) {
        Children[j + 1] = Children[j];
    }
    
    Children[i + 1] = z;
    
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    
    keys[i] = y->keys[t-1];
    
    n = n + 1;
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void BTreeNode::deletion(int k) {
    int idx = findKey(k);

    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            std::cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = ((idx == n) ? true : false);
        
        if (Children[idx]->n < t)
            fill(idx);
        
        if (flag && idx > n)
            Children[idx - 1]->deletion(k);
        else
            Children[idx]->deletion(k);
    }
    return;
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++)
        keys[i - 1] = keys[i];
    
    n--;
    return;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    
    if (Children[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        Children[idx]->deletion(pred);
    }
    else if (Children[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        Children[idx + 1]->deletion(succ);
    }
    else {
        merge(idx);
        Children[idx]->deletion(k);
    }
    return;
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* curr = Children[idx];
    while (!curr->leaf)
        curr = curr->Children[curr->n];
    return curr->keys[curr->n - 1];
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* curr = Children[idx + 1];
    while (!curr->leaf)
        curr = curr->Children[0];
    return curr->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && Children[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && Children[idx + 1]->n >= t)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = Children[idx];
    BTreeNode* sibling = Children[idx - 1];
    
    for (int i = child->n; i >= 0; --i)
        child->Children[i + 1] = child->Children[i];
    
    child->keys[0] = keys[idx - 1];
    
    if (!child->leaf)
        child->Children[0] = sibling->Children[sibling->n];
    
    keys[idx-1] = sibling->keys[sibling->n-1];
    
    child->n += 1;
    sibling->n -= 1;
    return;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = Children[idx];
    BTreeNode* sibling = Children[idx + 1];
    
    child->keys[child->n] = keys[idx];
    
    if (!child->leaf)
        child->Children[child->n + 1] = sibling->Children[0];
    
    keys[idx] = sibling->keys[0];
    
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->Children[i - 1] = sibling->Children[i];
        
    }
    child->n += 1;
    sibling->n -= 1;
    
    return;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = Children[idx];
    BTreeNode* sibling = Children[idx + 1];
    
    child->keys[t - 1] = keys[idx];
    
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];
    
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->Children[i + t] = sibling->Children[i];
    }
    
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    for (int i = idx + 2; i <= n; ++i)
        Children[i - 1] = Children[i];
    
    child->n += sibling->n+1;
    n--;
    
    delete(sibling);
    return;
}
