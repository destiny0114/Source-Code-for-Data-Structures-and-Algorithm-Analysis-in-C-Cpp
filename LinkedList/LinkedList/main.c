//  Linked List Set 1
//  链表是为了避免插入和删除线性开销，而且我们需要表允许可以不连续存续，否则需要
//  整体移动。
//  Created by Rockabye Saw on 05/04/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

//  ============        ============        =============       =============     
//  |          |        |          |        |           |       |           |       |           |
//  |    1     |        |    2     |        |     3     |       |      4    |       |      5    |
//  |----------| ====>  |----------| ====>  |-----------| ====> |------------ ====> |------------
//  |   812    |        |   654    |        |   700     |       |     548   |       |      0    |
//  |          |        |          |        |           |       |           |       |           |
//  ============        ============        ============        =============       =============
//      1000                812                 654                 700                 548
//     header
//  图中是链表的基本概念，有5个node, 每个node包含一个元素也就是1和next指针也就是812, 最好元素的指针是null ，header
//  是为了防止表插入前面的问题或者改变了起始端

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( ElementType X, List L );
void Delete( ElementType X, List L );
Position FindPrevious( ElementType X, List L );
void Insert( ElementType X, List L, Position P );
void DeleteList( List L );
Position Header( List L );
Position First( List L );
Position Advance( Position P );
ElementType Retrieve( Position P );
void PrintList( const List L );

struct Node
{
    ElementType Element;
    Position    Next;
};


int main(int argc, char *argvector[])
{
    int a[5]= {1000,812,654,700,548};
    List L;
    Position P;
    int i;

    L = MakeEmpty( NULL );
    P = Header( L );
    PrintList( L );

    for( i = 0; i < 10; i++ )
    {
        Insert( i, L, P );
        PrintList( L );
        P = Advance( P );
    }
    for( i = 0; i < 10; i+= 2 )
        Delete( i, L );

    for( i = 0; i < 10; i++ )
        if( ( i % 2 == 0 ) == ( Find( i, L ) != NULL ) )
            printf( "Find fails\n" );

    printf( "Finished deletions\n" );

    PrintList( L );

    DeleteList( L );

    PrintList( L );
    return 0;
}



List MakeEmpty( List L )
{
    if( L != NULL )
        DeleteList( L );
    L = malloc( sizeof( struct Node ) );
    if( L == NULL )
        perror( "Out of memory!" );
    L->Next = NULL;
    return L;
}

int IsEmpty( List L )
{
    // 表前面没连接
    return L->Next == NULL;
}

int IsLast( Position P, List L )
{
    // 前面没连接
    return P->Next == NULL;
}


Position Find( ElementType X, List L )
{
    Position P;
    
    P = L->Next;
    // 如果前面没连接华语X不一样的话就给回位置前面
    while( P != NULL && P->Element != X )
        P = P->Next;
    return P;
}

void Delete( ElementType X, List L )
{
    Position P, TmpCell;
    
    P = FindPrevious( X, L ); // 找出前面
    
    // 比如我们要删除元素3，首先找出元素3后面的指针也就是元素2的指针654，
    // 然后tmp就拿元素2指针的前面（700），元素3指针 tmp = 元素3（700）
    // 元素3指针（654）改去 tmp元素4指针 700
    // 然后释放tmp
    
    if( !IsLast( P, L ) )  /* Assumption of header use */
    {                      /* X is found; delete it */
        TmpCell = P->Next;
        P->Next = TmpCell->Next;  /* Bypass deleted cell */
        free( TmpCell );
    }
}

Position FindPrevious( ElementType X, List L )
{
    Position P;
    
    P = L;
    while( P->Next != NULL && P->Next->Element != X )
        P = P->Next;
    
    return P;
}


void Insert( ElementType X, List L, Position P )
{
    Position TmpCell;
    
    TmpCell = malloc( sizeof( struct Node ) ); // 可以写成new struct node
    if( TmpCell == NULL )
        perror( "Out of space!!!" );
    
    // 现在我们要插入256
    // tmp的元素 = 1 因为插在node 1
    // tmp元素1指针812 = 新元素2的指针812
    // 元素1指针256 = 新node 2 256
    // 总之新的插入变成header, 旧header在第二个变成node

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}


#if 0
/* Incorrect DeleteList algorithm */

void DeleteList( List L )
{
    Position P;
    
    P = L->Next;  /* Header assumed */
    L->Next = NULL;
    while( P != NULL )
    {
        free( P );
        P = P->Next;
    }
}
#endif
/* Correct DeleteList algorithm */

void DeleteList( List L )
{
    Position P, Tmp;
    
    P = L->Next;  /* Header assumed */
    L->Next = NULL;
    while( P != NULL )
    {
        Tmp = P->Next;
        free( P );
        P = Tmp;
    }
}

Position Header( List L )
{
    return L;
}

Position First( List L )
{
    return L->Next;
}

Position Advance( Position P )
{
    return P->Next;
}

ElementType Retrieve( Position P )
{
    return P->Element;
}


void PrintList( const List L )
{
    Position P = Header( L );

    if( IsEmpty( L ) )
        printf( "Empty list\n" );
    else
    {
        do
        {
            P = Advance( P );
            printf( "%d ", Retrieve( P ) );
        } while( !IsLast( P, L ) );
        printf( "\n" );
    }
}
