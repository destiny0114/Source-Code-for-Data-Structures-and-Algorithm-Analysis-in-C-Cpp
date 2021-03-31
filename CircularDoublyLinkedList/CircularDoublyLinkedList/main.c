//
//  main.c
//  CircularDoublyLinkedList
//
//  Created by Rockabye Saw on 28/04/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Print all node's data of a circular singly linked list
void PrintList(Position *head)
{
    if(*head == NULL)  return;

    Position current = *head;

    do
    {
        printf("%d ", current->data);
        current = current->next;
    }   while(current != *head);
}

void InsertBegin(Position *head, Position *tail, int data)
{
    Position temp = malloc(sizeof(struct Node));
    temp->data = data;
    temp->prev = temp;
    temp->next = temp;
    
    if(*head == NULL)
    {
        *head = temp;
        *tail = temp;
        temp->prev = *tail;
        temp->next = *head;
    }
    else
    {
        temp->next = *head;
        (*head)->prev = temp;
        
        temp->prev = *tail;
        (*tail)->next = temp;
        
        *head = temp;
    }
}

void InsertEnd(Position *head, Position *tail, int data)
{
    Position temp = malloc(sizeof(struct Node));
    temp->data = data;
    temp->prev = temp;
    temp->next = temp;
    
    if(*head == NULL)
    {
        *head = temp;
        *tail = temp;
        temp->prev = *tail;
        temp->next = *head;
    }
    else
    {
        temp->prev = *tail;
        (*tail)->next = temp;
        
        temp->next = *head;
        (*head)->prev = temp;
        
        *tail = temp;
    }
}

void InsertAfter(Position *head, Position *tail, int data, int item)
{
    Position temp, p;
    p = (*head)->next;
    
    do
    {
        if (p->data == item)
        {
            temp = malloc(sizeof(struct Node));
            temp->data = data;
            
            temp->prev = p;
            temp->next = p->next;
            p->next->prev = temp;
            p->next = temp;
            
            if (p == *tail) {
                (*head)->prev = temp;
                *tail = temp;
            }
        }
        
        p = p->next;
    } while (p != (*head)->next);
}

void InsertBefore(Position *head, Position *tail, int data, int item)
{
    Position temp, p, prev;
    p = (*head);
    
    if ((*head)->data == item)
    {
        InsertBegin(head, tail, data);
        return;
    }
    
    do
    {
        if (p->data == item)
        {
            temp = malloc(sizeof(struct Node));
            temp->data = data;
            
            prev->next = temp;
            temp->next = p;
            temp->prev = prev;
            prev->next->prev = temp;
        }
        
        prev = p;
        p = p->next;
    } while (p != (*head));
}

void DeleteBegin(Position *head, Position *tail)
{
    if (*head == NULL)  return;
    
    Position temp;
    temp = *head;
    
    if(temp->next == temp)
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
    }
    else
    {
        *head = (*head)->next;
        (*head)->prev = *tail;
        (*tail)->next = *head;
        free(temp);
    }
}

void DeleteEnd(Position *head, Position *tail)
{
    if (*tail == NULL)  return;
    
    Position temp;
    temp = *tail;
    
    if(temp->next == temp)
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
    }
    else
    {
        *tail = (*tail)->prev;
        (*tail)->next = *head;
        (*head)->prev = *tail;
        free(temp);
    }
}

void Delete(Position *head, Position *tail, int data)
{
    if (*head == NULL)  return;
    
    Position curr, prev;
    
    curr = (*head);
    
    if((*head)->data == data)
    {
        // if node is only head left
        if ((*head)->next == (*head))
        {
            *head = NULL;
            *tail = NULL;
            free(*head);
        }
        // node is head and still have other node
        else
        {
            curr = (*head);
            
            while(curr->next != (*head)) {
                curr = curr->next;
            }
            curr->next = (*head)->next;
            (*head)->prev = curr;
            (*head) = (*head)->next;
            return;
        }
    }
    else if ((*head)->data != data && (*head)->next == NULL)
    {
         printf("%d not found in the list\n", data);
         return;
    }
    
    curr = (*head);
    
    while (curr->next != (*head) && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr->data == data)
    {
        prev->next = curr->next;
        curr->next->prev = prev;
        // if node is tail
        if (curr == (*tail))
        {
            *tail = prev;
        }
        
        free(curr);
    }
    else
        printf("%d not found in the list.", data);
}

int main(int argc, const char * argv[])
{
    // insert code here...
    Position head = NULL, tail = NULL;
    // Insert 2 at begin so linked list become 2
    InsertBegin(&head, &tail, 2);
    // Insert 4 at begin so linked list become 4->2
    InsertBegin(&head, &tail, 4);
    // Insert 6 at end so linked list become 4->2->6
    InsertEnd(&head, &tail, 6);
    // Insert 8 at end so linked list become 4->2->6->8
    InsertEnd(&head, &tail, 8);
    // Insert 15 after 8 so linked list become 4->2->6->8->15
    InsertAfter(&head, &tail, 15, 8);
    // Insert 25 before 4 so linked list become 25->4->2->6->8->15
    InsertBefore(&head, &tail, 25, 4);
    // Delete Begin so linked list become 4->2->6->8->15
    DeleteBegin(&head, &tail);
    //DeleteEnd(&head, &tail);
    //Delete(&head, &tail, 6);
    PrintList(&head);
    return 0;
}
