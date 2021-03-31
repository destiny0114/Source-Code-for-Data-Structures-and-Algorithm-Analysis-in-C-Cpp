//
//  main.cpp
//  Tree
//
//  Created by Rockabye Saw on 14/01/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//
//  树是非线性结构的一种，它可以用于大量数据来访问，例如电脑的文件系统。
//  线性结构的有数组，链表，栈，队列，双队列，串(一维数组)。
//  树结构就行树形一样里面会有一个根(root)，然后衍生到两个或多个节点(nodes),
//  当然这个根与节点之间连接点我们都会叫条边也就是树枝(edges)。
//  树的用语:
//  1. 根(root)位于树最高层，仅有一个而已
//  2. 条边(edges)位于根与节点之间或者节点与节点之间
//  3. 孩子(child)是那个节点有父母(parent)的节点
//  4. 父母(parent)是个节点有条边(edges)衍生去孩子(child)的节点
//  5. 叶子(leaf)是那个节点没有孩子的节点
//  6. 高度(height)是那一行的节点
//  7. 深度(depth)是从根部(root)衍生到最后一个节点
//  树的遍历:
//  Depth-First Search (DFS)
//  Breadth-First Search (BFS)
//  DFS是用来遍历整个树的节点，从根部开始的，BFS是用来遍历整个树的高度和深度
//  树的种类:
//  General Tree - 没规定父母和孩子数量,至于其他类型参考以下名称项目
//  Binary Tree
//  Binary Search Tree (BST)
//  AVL Tree
//  Red-Black Tree
//  N-ary Tree - 没规定孩子数量

#include <iostream>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    
    Node(int val) {
        this->data = val;
        
        left = NULL;
        right = NULL;
    }
};

int main(int argc, const char * argv[]) {
    /*create root*/
      struct Node* root = new Node(1);
      /* following is the tree after above statement
    
               1
              / \
            NULL NULL
      */
    
      root->left = new Node(2);
      root->right = new Node(3);
      /* 2 and 3 become left and right children of 1
                       1
                      / \
                     2    3
                    / \  /  \
                 NULL NULL NULL NULL
      */
    
      root->left->left = new Node(4);
      /* 4 becomes left child of 2
                 1
              /     \
             2      3
            / \     / \
            4 NULL NULL NULL
           / \
        NULL NULL
      */
    
      return 0;
}
