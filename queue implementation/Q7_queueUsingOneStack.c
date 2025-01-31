#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct stack {
    Node *top;
} Stack;

typedef struct queue {
    Stack *stack;
} Queue;

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

Stack *createStack(){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

Queue *createQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->stack = createStack();
    return queue;
}

bool isEmptyStack(Stack *stack){
    return stack->top == NULL;
}

void push(Stack *stack, int value){
    Node *node = createNode(value);
    if(node == NULL){
        stack->top = node;
        return;
    }
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack *stack){
    if(isEmptyStack(stack)) return INT_MIN;
    Node *nodeToBeDeleted = stack->top;
    stack->top = stack->top->next;
    int returnValue = nodeToBeDeleted->data;
    free(nodeToBeDeleted);
    return returnValue;
}

int sizeOfStack(Stack *stack){
    int length = 0;
    Node *traversalNode = stack->top;
    while(traversalNode){
        length++;
        traversalNode = traversalNode->next;
    }
    return length;
}

int sizeOfQueue(Queue *queue){
    return sizeOfStack(queue->stack);    
}

bool isEmptyQueue(Queue *queue){
    return isEmptyStack(queue->stack);
}

void enqueue(Queue *queue, int value){
    push(queue->stack, value);
}

int dequeue(Queue *queue){
    if(isEmptyQueue(queue)){
        printf("\nQueue is already empty");
        return INT_MIN;
    } else if(sizeOfQueue(queue) == 1){
        return pop(queue->stack);
    }
    int value = pop(queue->stack);
    dequeue(queue);
    push(queue->stack, value);
}

int front(Queue *queue){
    if(isEmptyQueue(queue)) return INT_MIN;
    Node *top = queue->stack->top;
    while(top->next)
        top = top->next;
    return top->data;
}

int handleIntegerInput(char *inputPrompt){
    int number;
    printf("\n%s : ", inputPrompt);
    scanf("%d", &number);
    return number;
}

void printQueue(Queue *queue){
    if(isEmptyQueue(queue)) return;
    int value = pop(queue->stack);
    printQueue(queue);
    printf("%d  ", value);
    push(queue->stack, value);
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
            if(isEmptyQueue(queue)) {
                printf("\nQueue : Empty");
            } else {
                printf("\nQueue : ");
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
            value = sizeOfQueue(queue);
            printf("\nsize : %d", value);
            break;
        case 6:
            printf("\nExiting...");
            exit(0);
            break;
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
2.  dequeue                 O(n)                            O(n)
3.  front                   O(n)                            O(1)
4.  size                    O(n)                            O(1)
5.  isEmpty                 O(1)                            O(1)
*/