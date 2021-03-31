//
//  main.c
//  Stack-v2
//  Stack数组实现
//  Created by Rockabye Saw on 05/05/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS ( -1 ) // directly make stack empty by top = -1
#define MinStackSize ( 5 )

struct StackRecord;
typedef struct StackRecord *Stack;

int IsEmpty( Stack S );
int IsFull( Stack S );
Stack CreateStack( int MaxElements );
void DisposeStack( Stack S );
void MakeEmpty( Stack S );
void Push( int X, Stack S );
int Top( Stack S );
void Pop( Stack S );
int TopAndPop( Stack S );

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    int *Array;
};

int main(int argc, const char * argv[]) {
    Stack S;
    int i;

    S = CreateStack( 12 );
    for( i = 0; i < 10; i++ )
        Push( i, S );

    while( !IsEmpty( S ) )
    {
        printf( "%d\n", Top( S ) );
        Pop( S );
    }

    DisposeStack( S );
    return 0;
}

int IsEmpty( Stack S )
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull( Stack S )
{
    return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack( int MaxElements )
{
    Stack S;
    
    if (MaxElements < MinStackSize)
        perror("Stack Size too small !");
    
    S = malloc(sizeof(struct StackRecord));
    
    if (S == NULL)
        perror("Out of Space");
    
    S->Array = malloc( sizeof(int) * MaxElements );
    
    if (S->Array == NULL)
        perror("Out of Space !");
    
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void MakeEmpty( Stack S )
{
    S->TopOfStack = EmptyTOS;
}

void DisposeStack( Stack S )
{
    if ( S != NULL )
    {
        free( S->Array );
        free( S );
    }
}

void Push( int X, Stack S )
{
    if (IsFull(S))
        perror("Full Stack");
    else
        S->Array[++S->TopOfStack] = X;
}

int Top( Stack S )
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    perror("Empty Stack");
    return 0;
}

void Pop( Stack S )
{
    if( IsEmpty( S ) )
        perror( "Empty stack" );
    else
        S->TopOfStack--;
}

int TopAndPop( Stack S )
{
    if( !IsEmpty( S ) )
        return S->Array[ S->TopOfStack-- ];
    perror("Empty stack");
    return 0;
}
