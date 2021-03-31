//
//  main.c
//  CircularSinglyLinkedList
//
//  Created by Rockabye Saw on 16/04/2020.
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
    struct Node *next;
};

// Insert a node at front of a circular singly linked list
void InsertBegin(Position *head, Position *tail, int data)
{
    Position temp = malloc(sizeof(struct Node));

    temp->data = data;
    temp->next = temp;

    if(*head == NULL)
    {
        *head = temp;
        *tail = temp;
    }
    else
    {
        temp->next = *head;
        (*tail)->next = temp;
        *head = temp;
    }

}

void InsertEnd(Position *head, Position *tail, int data)
{
    Position temp = malloc(sizeof(struct Node));

    temp->data = data;
    temp->next = temp;
    
    if (*head == NULL)
    {
        *head = temp;
        *tail = temp;
    }
    else
    {
        temp->next = (*tail)->next;
        (*tail)->next = temp;
        (*tail) = temp;
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
            temp->next = p->next;
            p->next = temp;
            
            if (p == *tail)
            {
                *tail = temp;
            }
        }
        p = p -> next;
    } while (p != (*head)->next);
}

void InsertBefore(Position *head, Position *tail, int data, int item)
{
    Position temp, curr, prev = NULL;
    curr = (*head);
    
    if ((*head)->data == item)
    {
        InsertBegin(head, tail, data);
        return;
    }
    
    do
    {
        if (curr->data == item)
        {
            temp = malloc(sizeof(struct Node));
            temp->data = data;
            temp->next = curr;
            prev->next = temp;
            
            if(curr == *head)
            {
                *head = temp;
            }
        }
        prev = curr;
        curr = curr -> next;
    } while (curr != (*head));
}


void Delete(Position *head, Position *tail, int data)
{
    if (*head == NULL)  return;
    
    Position curr, prev;
    
    if((*head)->data == data)
    {
        if ((*head)->next == (*head))
        {
            free(*head);
            *head = NULL;
        }
        else
        {
            curr = (*head);
            
            while(curr->next != (*head)) {
                curr = curr->next;
            }
            
            curr->next = (*head)->next;
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
        prev->next = prev->next->next;
        free(curr);
    }
    else
        printf("%d not found in the list.", data);
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
        (*tail)->next = temp->next;
        *head = (*tail)->next;
        free(temp);
    }
}

void DeleteEnd(Position *head, Position *tail)
{
    if (*tail == NULL)  return;
    
    Position temp, prev;
    temp = (*head);
    
    if(temp->next == temp)
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
    }
    else
    {
        do
        {
            prev = temp;
            temp = temp->next;
        } while (temp->next != (*head));
        
        prev->next = (*tail)->next;
        *tail = prev;
        *head = (*tail)->next;
        free(temp);
    }
}

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

int main(int argc, const char * argv[]) {
    // insert code here...
    Position head = NULL, tail = NULL;
    // Insert 8 at begin so linked list become 8
    InsertBegin(&head, &tail, 8);
    // Insert 5 at begin so linked list become 5->8
    InsertBegin(&head, &tail, 5);
    // Insert 2 at begin so linked list become 2->5->8
    InsertBegin(&head, &tail, 2);
    // Insert 2 at end so linked list become 2->5->8->10
    InsertEnd(&head, &tail, 10);
    // Insert 2 at end so linked list become 2->5->8->10->12
    InsertEnd(&head, &tail, 12);
    // Insert 9 after 8 so linked list become 2->5->8->9->10->12
    InsertAfter(&head, &tail, 9, 8);
    // Insert 3 before 5 so linked list become 15->2->5->8->9->10->12
    InsertBefore(&head, &tail, 15, 2);
    // Delete Begin so linked list become 2->5->8->9->10->12
    DeleteBegin(&head, &tail);
    //Delete(&head, &tail, 9);
    PrintList(&head);
    return 0;
}
