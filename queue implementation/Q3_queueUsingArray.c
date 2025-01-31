#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct queue {
    int *arr;
    unsigned capacity;
    int front;
    int rear;
} Queue;

Queue *createQueue(unsigned capacity){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->arr = (int *) malloc(capacity * sizeof(int));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    return queue;
}

bool isFull(Queue *queue){
    return queue->rear == queue->capacity - 1;
}

bool isEmpty(Queue *queue){
    return queue->front == -1;
}

void enqueue(Queue *queue, int value){
    if(isFull(queue)){
        printf("Overflow\n");
        return;
    }
    queue->arr[++queue->rear] = value;
    if(queue->front == -1) queue->front = 0;
}

int dequeue(Queue *queue){
    if(isEmpty(queue)){
        printf("Underflow\n");
        return INT_MIN;
    }
    int valueToBeDequeued = queue->arr[queue->front++];
    if(queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return valueToBeDequeued;
}

int front(Queue *queue){
    if(queue->front == -1){
        printf("Queue is Empty\n");
        return INT_MIN;
    }
    return queue->arr[queue->front];
}

int size(Queue *queue){
    if(queue->front == -1) return 0;
    return queue->rear - queue->front + 1;
}

int handleIntegerInput(char *inputPrompt){
    int number;
    printf("\n%s : ", inputPrompt);
    scanf("%d", &number);
    return number;
}

void printQueue(Queue *queue){
    if(isEmpty(queue)){
        printf("\nQueue : Empty");
        return;
    }
    for(int i = queue->front; i <= queue->rear; i++)
        printf("%d  ", queue->arr[i]);
}

int menuPrompt(){
    printf("\n\nSelect Operations : \n");
    printf("1 for enqueue : ");
    printf("\n2 for dequeue : ");
    printf("\n3 for display : ");
    printf("\n4 for peek (front) : ");
    printf("\n5 for size : ");
    printf("\n6 for exit : ");
    int operation = handleIntegerInput("select operation");
    return operation;
}

void menu(){
    int sizeOfQueue = handleIntegerInput("Enter queue size");
    if(sizeOfQueue < 1){
        printf("\nInvalid size...");
        exit(0);
    }
    Queue *queue = createQueue(sizeOfQueue);
    while(1){
        int operation = menuPrompt();
        int value;
        switch (operation)
        {
        case 1:
            if(isFull(queue)){
                printf("\nQueue is already full.");
                break;
            }
            value = handleIntegerInput("Enter value");
            enqueue(queue, value);
            break;
        case 2:
            dequeue(queue);
            break;
        case 3:
            if(isEmpty(queue)){
                printf("\nQueue : Empty");
            } else {
                printf("\nQueue -> ");        
                printQueue(queue);
            }
            break;
        case 4:
            value = front(queue);
            if(value == INT_MIN)
                printf("\nEmpty");
            else
                printf("\nFront : %d", value);
            break;
        case 5:
            value = size(queue);
            printf("\nsize : %d", value);
            break;
        case 6:
            printf("\nExiting...");
            exit(0);
        default:
            printf("\nInvalid option");
            break;
        }
    }
    free(queue);
}

int main(){
    menu();
    return 0;
}