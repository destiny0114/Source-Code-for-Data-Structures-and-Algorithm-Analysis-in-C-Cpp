//
//  main.c
//  Queue-v1
//  C program for array implementation of queue
//  Created by Rockabye Saw on 20/06/2020.
//  Copyright © 2020 Rockabye Saw. All rights reserved.
//
//  Queue是FIFO （First In First Out)
//  队列也是表不过他插入在另一端进行，而删除也在另一端进行。
//  队列可以通过数组和链表来实现。
//  队列中一定会有Rear的队尾和叫Front的队头。
//  队列的插入操作叫Enqueue的入队，他是插入在队尾。
//  队列的删除操作叫Dequeue的出队，他是删除在队头。
//  队列的链表实现请查看Queue-v2项目。

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Queue;

struct Node
{
    int front; // last item of queue
    int rear;  // first item of queue
    int size;  // size of queue
    int capacity;  // capacity of queue
    int *array; // create array
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue createQueue(int input_capacity)
{
    int capacity = input_capacity;

    PtrToNode newQueue;
    newQueue = malloc(sizeof(Queue));
    newQueue->capacity = capacity;
    newQueue->front = 0;
    newQueue->size = 0;
    newQueue->rear = capacity - 1;
    newQueue->array = malloc(sizeof(int) * newQueue->capacity);
    
    if (newQueue->array == NULL) {
        perror("Out of Space !");
    }
    return newQueue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(Queue output_queue)
{
    return (output_queue->size ==  output_queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue output_queue)
{
    return (output_queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void Enqueue(Queue output_queue, int n)
{
    if(isFull(output_queue))
        return;
    output_queue->rear = (output_queue->rear + 1) %
    output_queue->capacity;
    output_queue->array[output_queue->rear] = n;
    output_queue->size = output_queue->size + 1;
    printf("%d enqueued to queue\n", n);
}

// Function to remove an item from queue.
// It changes front and size
int Dequeue(Queue output_queue)
{
    if(isEmpty(output_queue))
        return -1;
    int n = output_queue->array[output_queue->front];
    output_queue->front = (output_queue->front + 1) %
    output_queue->capacity;
    output_queue->size = output_queue->size - 1;
    return n;
}

// Function to get front of queue
int Front(Queue output_queue)
{
    if(isEmpty(output_queue))
        return -1;
    return output_queue->array[output_queue->front];
}

// Function to get rear of queue
int Rear(Queue output_queue)
{
    if(isEmpty(output_queue))
        return -1;
    return output_queue->array[output_queue->rear];
}

// Function to print whole queue
void Display(Queue output_queue)
{
    int i = output_queue->front;
    printf("Whole queue is ");
    
    while (i < output_queue->rear + 1)
    {
        printf("%d ", output_queue->array[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    Queue queue = createQueue(1000);
    
    Enqueue(queue, 10);
    Enqueue(queue, 20);
    Enqueue(queue, 30);
    Enqueue(queue, 40);
    
    printf("%d dequeued from queue\n\n",
           Dequeue(queue));
    
    printf("Front item is %d\n", Front(queue));
    printf("Rear item is %d\n", Rear(queue));
    Display(queue);
    
    return 0;
}
