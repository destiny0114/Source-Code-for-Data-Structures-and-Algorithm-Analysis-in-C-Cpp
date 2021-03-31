//
//  main.c
//  Stack-v1
//  Implementation of stack using linked list
//  Created by Rockabye Saw on 01/05/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//  Stack是可以限制Insertion和Deletion只能在一个位置上进行（runtime）的表
//  Stack实现方法有两种：
//  1.链表 Linked List（Stack-v1)
//  2.数组 Array（Stack-v2)
//  如果用数组实现Stack好处是不需要利用指针，那么首先要提前准备空间（Capacity)，
//  如果这点做不到还是用链表实现

#include <stdlib.h>
#include <stdio.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    int Data;
    PtrToNode Next;
};

int IsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void MakeEmpty( Stack S );
void Push( int X, Stack S );
int Top( Stack S );
void Pop( Stack S );

int main(int argc, const char * argv[]) {
    Stack S;
    S = CreateStack();
    
    Push( 0, S );
    Push( 1, S );

    Pop( S );
    
    printf("%d\n", Top( S ));
    DisposeStack( S );
    return 0;
}

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack(void)
{
    Stack S;
    S = malloc(sizeof(struct Node));
    
    if(S == NULL)
    {
        perror("Out of Space !");
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

void MakeEmpty(Stack S)
{
    if(S == NULL)
        perror("Must use CreateStack First");
    else
        do
        {
            Pop(S);
        } while (!IsEmpty(S));
}

void DisposeStack(Stack S)
{
    MakeEmpty(S);
    free(S);
}

void Push( int X, Stack S )
{
    PtrToNode TmpCell;
    
    TmpCell = malloc(sizeof(struct Node));
    
    if(TmpCell == NULL)
        perror("Out of Space !");
    else
    {
        TmpCell->Data = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

int Top( Stack S )
{
    if (!IsEmpty(S))
        return S->Next->Data;
    perror("Empty Stack");
    return 0;
}

void Pop( Stack S )
{
    PtrToNode FirstCell;
    
    if( IsEmpty( S ) )
        perror("Empty stack");
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
}
