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

typedef struct stack {
    Queue *queue;
} Stack;

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

bool isEmptyQueue(Queue *queue){
    return queue->front == NULL;
}

void enqueue(Queue *queue, int value){
    Node *node = createNode(value);
    if(isEmptyQueue(queue)){
        queue->rear = node;
        queue->front = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
}

int dequeue(Queue *queue){
    if(isEmptyQueue(queue)){
        printf("Underflow\n");
        return INT_MIN;
    }
    Node *nodeToBeDeleted = queue->front;
    queue->front = queue->front->next;
    int value = nodeToBeDeleted->data;
    free(nodeToBeDeleted);
    return value;
}

int sizeOfQueue(Queue *queue){
    Node *traversalNode = queue->front;
    int length = 0;
    while(traversalNode){
        length++;
        traversalNode = traversalNode->next;
    }
    return length;
}

Stack *createStack(){ 
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->queue = (Queue *) malloc(sizeof(Queue));
    stack->queue->front = NULL;
    stack->queue->rear = NULL;
    return stack;
}

bool isEmptyStack(Stack *stack){
    return isEmptyQueue(stack->queue);
}

void push(Stack **stack, int value){
    enqueue((*stack)->queue, value);
}

int pop(Stack **stack){
    if(isEmptyStack(*stack)) return INT_MIN;
    Queue *temporaryQueue = createQueue();
    while(sizeOfQueue((*stack)->queue) > 1)
        enqueue(temporaryQueue, dequeue((*stack)->queue));
    (*stack)->queue = temporaryQueue;
    return dequeue((*stack)->queue);
}

int handleIntegerInput(char *inputPrompt){
    int number;
    printf("\n%s : ", inputPrompt);
    scanf("%d", &number);
    return number;
}

int peek(Stack *stack){
    if(isEmptyStack(stack))
        return INT_MIN;
    return stack->queue->rear->data;
}

void printStack(Stack *stack){
    if(isEmptyStack(stack)) return;
    Node *traversedNode = stack->queue->front;
    while (traversedNode){
        printf("%d  ", traversedNode->data);
        traversedNode = traversedNode->next;
    }
}

int menuPrompt(){
    printf("\n\nSelect Operations : \n");
    printf("1 for push : ");
    printf("\n2 for pop : ");
    printf("\n3 for display : ");
    printf("\n4 for peek : ");
    printf("\n5 for exit : ");
    int operation = handleIntegerInput("select operation");
    return operation;
}

void menu(){
    Stack *stack = createStack();
    while(1){
        int operation = menuPrompt();
        int value;
        switch (operation)
        {
        case 1:
            value = handleIntegerInput("Enter value");
            push(&stack, value);
            break;
        case 2:
            pop(&stack);
            break;
        case 3:
            if(isEmptyStack(stack)){
                printf("\nStack : Empty");
            } else {
                printf("\nStack -> ");        
                printStack(stack);
            }
            break;
        case 4:
            value = peek(stack);
            if(value == INT_MIN)
                printf("\nEmpty");
            else
                printf("\nPeek : %d", value);
            break;
        case 5:
            printf("\nExiting...");
            exit(0);
            break;
        default:
            printf("\nInvalid option");
            break;
        }
    }
    free(stack);
}

int main(){
    menu();
    return 0;
}