//
//  main.c
//  CircularQueue-v1
//  A C program to demonstrate linked list based implementation of circular linked list
//  Created by Rockabye Saw on 20/06/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;

// A node store in Queue
struct Node
{
    int data;
    Position next;
};

// The queue, front stores the front node of LL and rear stores the
// last node of LL
struct Queue;
typedef struct Queue* PtrToQueue;
typedef PtrToQueue Queue;
struct Queue {
    Position front;
    Position rear;
};

// A utility function to create a new linked list node.
Position createNode(int input_data)
{
    Position newNode = malloc(sizeof(struct Node));
    newNode->data = input_data;
    newNode->next = NULL;
    return newNode;
}

// A utility function to create an empty queue
Queue createQueue()
{
    Queue newQueue = malloc(sizeof(struct Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    return newQueue;
}

// The function to add a data to queue
void Enqueue(Queue output_queue, int input_data)
{
    Position temp = createNode(input_data);
    // If queue is empty, then new node is front and rear both
    if (output_queue->rear == NULL)
    {
        output_queue->front = temp;
        output_queue->rear = temp;
        return;
    }
    
    // Add the new node at the end of queue and change rear
    output_queue->rear->next = temp;
    output_queue->rear = temp;
    // Make the rear node pointer pointer to front
    output_queue->rear->next = output_queue->front;
}

void Dequeue(Queue output_queue)
{
    // If queue is empty, return NULL.
    if(output_queue->front == NULL)
        return;
    
    // Store previous front and move front one node ahead
    Position temp = output_queue->front;
    output_queue->front = temp->next;
    // Make the front node pointer pointer to rear
    output_queue->rear->next = output_queue->front;
    
    free(temp);
}


// Function to print whole queue
void Display(Queue q)
{
    Position temp = q->front;
    
    while (temp->next != q->front) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main(int argc, const char * argv[]) {
    Queue queue = createQueue();
    Enqueue(queue, 10);
    Enqueue(queue, 20);
    Enqueue(queue, 30);
    Dequeue(queue);
    printf("Queue Front : %d \n", queue->front->data);
    printf("Queue Rear : %d", queue->rear->data);
    Display(queue);
    return 0;
}
