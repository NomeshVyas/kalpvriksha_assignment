#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct queue {
    Node *front;
    Node *rear;
} Queue;

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

Queue *createQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

bool isEmpty(Queue *queue){
    return queue->front == NULL;
}

void enqueue(Queue *queue, int value){
    Node *node = createNode(value);
    if(isEmpty(queue)){
        queue->rear = node;
        queue->front = node;
    }
    queue->rear->next = node;
    queue->rear = node;
}

int dequeue(Queue *queue){
    if(isEmpty(queue)){
        printf("Underflow\n");
        return INT_MIN;
    }
    Node *nodeToBeDeleted = queue->front;
    queue->front = queue->front->next;
    int value = nodeToBeDeleted->data;
    free(nodeToBeDeleted);
    return value;
}

int peek(Queue *queue){
    if(isEmpty(queue)){
        printf("Queue is Empty.\n");
        return INT_MIN;
    }
    return queue->front->data;
}

int size(Queue *queue){
    Node *traversalNode = queue->front;
    int length = 0;
    while(traversalNode){
        length++;
        traversalNode = traversalNode->next;
    }
    return length;
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
    Node *traversedNode = queue->front;
    printf("\nQueue : ");
    while (traversedNode){
        printf("%d  ", traversedNode->data);
        traversedNode = traversedNode->next;
    }
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
    Queue *queue = createQueue();
    while(1){
        int operation = menuPrompt();
        int value;
        switch (operation)
        {
        case 1:
            value = handleIntegerInput("Enter value");
            enqueue(queue, value);
            break;
        case 2:
            dequeue(queue);
            break;
        case 3:
            if(isEmpty(queue))
                printf("\nQueue : Empty");
            else
                printQueue(queue);
            break;
        case 4:
            value = peek(queue);
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
/*
Complexity Analysis ->
No. Operation               Time Complexity                 Space Complexity
1.  enqueue                 O(1)                            O(1)
2.  dequeue                 O(1)                            O(1)
3.  front                   O(1)                            O(1)
4.  size                    O(n)                            O(1)
5.  isEmpty                 O(1)                            O(1)
*/