//
//  main.c
//  CursorImplementationLinkedList
//
//  Created by Rockabye Saw on 13/04/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//
// 当其他语言没指针我们可以使用这个Array来实现像CursorLinkedlList（游标链表）
// 前提一定要准备备用空间
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define SpaceSize 100

typedef int PtrToNode;
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

struct Node CursorSpace [SpaceSize];

static Position
CursorAlloc( void )
{
    Position P;
    
    P = CursorSpace[ 0 ].Next;
    CursorSpace[ 0 ].Next = CursorSpace[ P ].Next;
    
    return P;
}

static void
CursorFree(Position P)
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

void InitializeCursorSpace(void)
{
    int i;

    for( i = 0; i < SpaceSize; i++ )
        CursorSpace[ i ].Next = i + 1;
    
    CursorSpace[ SpaceSize - 1 ].Next = 0;
}


int main(int argc, char *argvector[])
{
    int a[5]= {1000,812,654,700,548};
    List L;
    Position P;
    int i;
    InitializeCursorSpace();
    L = MakeEmpty( 0 );
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
        if( ( i % 2 == 0 ) == ( Find( i, L ) != 0 ) )
            printf( "Find fails\n" );

    printf( "Finished deletions\n" );

    PrintList( L );

    DeleteList( L );

    PrintList( L );
    return 0;
}



List MakeEmpty( List L )
{
    if( L )
        DeleteList( L );
    // L = malloc( sizeof( struct Node ) );
    L = CursorAlloc();
    if( L == 0 )
        perror( "Out of memory!" );
    // L->Next = NULL;
    CursorSpace[L].Next = 0;
    return L;
}

int IsEmpty( List L )
{
    // 表前面没连接
    // return L->Next == NULL;
    return CursorSpace[L].Next == 0;
}

int IsLast( Position P, List L )
{
    // 最后没连接
    // return P->Next == NULL;
    return CursorSpace[P].Next == 0;
}


Position Find( ElementType X, List L )
{
    Position P;
    
    // P = L->Next;
    P = CursorSpace[L].Next;
    // 如果前面没连接华语X不一样的话就给回位置前面
    // while( P != NULL && P->Element != X )
        // P = P->Next;
    while (P && CursorSpace[P].Element != X) {
        P = CursorSpace[P].Next;
    }
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
    
//    if( !IsLast( P, L ) )  /* Assumption of header use */
//    {                      /* X is found; delete it */
//        TmpCell = P->Next;
//        P->Next = TmpCell->Next;  /* Bypass deleted cell */
//        free( TmpCell );
//    }
    
    if (!IsLast(P, L)) {
        TmpCell = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

Position FindPrevious( ElementType X, List L )
{
    Position P;
    
    P = L;
    // while( P->Next != NULL && P->Next->Element != X )
        // P = P->Next;
    while (CursorSpace[P].Next && CursorSpace[CursorSpace[P].Next].Element != X) {
        P = CursorSpace[P].Next;
    }
    
    return P;
}


void Insert( ElementType X, List L, Position P )
{
    Position TmpCell;
    
    // TmpCell = malloc( sizeof( struct Node ) ); // 可以写成new struct node
    TmpCell = CursorAlloc();
    if( TmpCell == 0 )
        perror( "Out of space!!!" );
    
    // 现在我们要插入256
    // tmp的元素 = 1 因为插在node 1
    // tmp元素1指针812 = 新元素2的指针812
    // 元素1指针256 = 新node 2 256
    // 总之新的插入变成header, 旧header在第二个变成node

    // TmpCell->Element = X;
    // TmpCell->Next = P->Next;
    // P->Next = TmpCell;
    CursorSpace[TmpCell].Element = X;
    CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
}


#if 0
/* Incorrect DeleteList algorithm */

void DeleteList( List L )
{
    Position P;
    
    // P = L->Next;  /* Header assumed */
    P = CursorSpace[L].Next
    // L->Next = NULL;
    CursorSpace[L].Next = 0;
//    while( P != NULL )
//    {
//        free( P );
//        P = P->Next;
//    }
    while( P != 0 )
    {
        CursorFree(P)
        P = CursorSpace[P].Next;
    }
}
#endif
/* Correct DeleteList algorithm */

void DeleteList( List L )
{
    Position P, Tmp;
    
    // P = L->Next;  /* Header assumed */
    P = CursorSpace[L].Next;
    // L->Next = NULL;
    CursorSpace[L].Next = 0;
//    while( P != NULL )
//    {
//        Tmp = P->Next;
//        free( P );
//        P = Tmp;
//    }
    while (P != 0) {
        Tmp = CursorSpace[P].Next;
        CursorFree(P);
        P = Tmp;
    }
}

Position Header( List L )
{
    return L;
}

Position First( List L )
{
    // return L->Next;
    return CursorSpace[L].Next;
}

Position Advance( Position P )
{
    // return P->Next;
    return CursorSpace[P].Next;
}

ElementType Retrieve( Position P )
{
    // return P->Element;
    return CursorSpace[P].Element;
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
