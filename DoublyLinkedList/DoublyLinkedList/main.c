//  main.c
//  DoublyLinkedList
//  双链表 - 多一个指针叫prev之前只是next指针而已，整个表的y头和尾
//  就有null, node之间可以查prev和next
//  Created by Rockabye Saw on 07/04/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;

// A linked list node
struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

/* Given a reference (pointer to pointer) to the head of a list and
 an int, inserts a new node on the front of the list. */
void push(Position *h, int new_data)
{
    /* 1. allocate node */
    Position new_node = malloc(sizeof(struct Node));
    
    /* 2. put in the data  */
    new_node->data  = new_data;
    
    
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*h);
    new_node->prev = NULL;
    
    
    /* 4. move the head to point to the new node */
    if ((*h) != NULL)
        (*h)->prev = new_node;
    
    /* 5. move the head to point to the new node */
    (*h) = new_node;
}

/* Given a node prev_node, insert a new node after the given
 prev_node */
void insertAfter(Position prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }
    
    /* 2. allocate new node */
    Position new_node = malloc(sizeof(struct Node));
    
    /* 3. put in the data  */
    new_node->data  = new_data;
    
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
    
    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
    
    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;
    
    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

/* Given a node as next_node, insert a new node before the given node */
void insertBefore(Position *h, Position next_node, int new_data)
{
    /*1. check if the given next_node is NULL */
    if (next_node == NULL) {
        printf("the given next node cannot be NULL");
        return;
    }
  
    /* 2. allocate new node */
    Position new_node = malloc(sizeof(struct Node));
  
    /* 3. put in the data */
    new_node->data = new_data;
  
    /* 4. Make prev of new node as prev of next_node */
    new_node->prev = next_node->prev;
  
    /* 5. Make the prev of next_node as new_node */
    next_node->prev = new_node;
  
    /* 6. Make next_node as next of new_node */
    new_node->next = next_node;
  
    /* 7. Change next of new_node's previous node */
    if (new_node->prev != NULL)
        new_node->prev->next = new_node;
    /* 8. If the prev of new_node is NULL, it will be
       the new head node */
    else
        (*h) = new_node;
      
}

/* Given a reference (pointer to pointer) to the head
 of a list and an int, appends a new node at the end  */
void append(Position* h, int new_data)
{
    /* 1. allocate node */
    Position new_node = malloc(sizeof(struct Node));
    
    Position last = *h;  /* used in step 5*/
    
    /* 2. put in the data  */
    new_node->data  = new_data;
    
    /* 3. This new node is going to be the last node, so make next of
     it as NULL*/
    new_node->next = NULL;
    
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*h == NULL)
    {
        new_node->prev = NULL;
        *h = new_node;
        return;
    }
    
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
    
    /* 6. Change the next of last node */
    last->next = new_node;
    
    /* 7. Make last node as previous of new node */
    new_node->prev = last;
    return;
}

int IsLast(Position P)
{
    return P->next == NULL;
}

void delete(Position *h, int data)
{
    Position tmp = *h;
    
    // if deleted node is head
    if(!IsLast(tmp) && tmp->data == data)
    {
        *h = tmp->next;
        if (tmp->next != NULL) {
            tmp->next->prev = NULL;
        }
        free(tmp);
        return;
    }
    
    // if deleted node is not head and also not last
    while (tmp != NULL && tmp->data != data)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            printf("\nNode does not exist\n");
            return;
        }
    }
    
    // if deleted node is last
    if(IsLast(tmp) && tmp->data == data)
    {
        // 1->5->7->8->3->4->NULL 如果删除4
        // 4 prev的3 next = 4的next null 所以3的next变成null
        // 断开4的prev
        tmp->prev->next = tmp->next;
        tmp->prev = NULL;
        free(tmp);
        return;
    }
        
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);
}

// This function prints contents of linked list starting from head
void printList(Position node)
{
    Position last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL) {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
   }
  
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf(" %d ", last->data);
        last = last->prev;
    }
}

int main(int argc, const char * argv[]) {
    /* Start with the empty list */
    //struct Node* head = NULL;
    Position head = NULL;
    // Insert 3. So linked list becomes 3->NULL
    append(&head, 3);
    
    // Insert 7 at the beginning. So linked list becomes 7->3->NULL
    push(&head, 7);
    
    // Insert 1 at the beginning. So linked list becomes 1->7->3->NULL
    push(&head, 1);
    
    // Insert 4 at the end. So linked list becomes 1->7->3->4->NULL
    append(&head, 4);
    
    // Insert 8, after 7. So linked list becomes 1->7->8->3->4->NULL
    insertAfter(head->next, 8);
    
    // Insert 5, before 7. So linked list becomes 1->5->7->8->3->4->NULL
    insertBefore(&head, head->next, 5);
    
    delete(&head, 8);
    
    printf("\n Created Linked list is: ");
    printList(head);
    
    return 0;
}
