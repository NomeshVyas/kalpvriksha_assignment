#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct stack {
    Node *head;
} Stack;

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

Stack *createStack(){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

bool isEmpty(Stack *stack){
    return stack->head == NULL;
}

void push(Stack *stack, int value){
    Node *node = createNode(value);
    if(node == NULL){
        stack->head = node;
        return;
    }
    node->next = stack->head;
    stack->head = node;
}

int pop(Stack *stack){
    if(isEmpty(stack)) return INT_MIN;
    Node *nodeToBeDeleted = stack->head;
    stack->head = stack->head->next;
    int returnValue = nodeToBeDeleted->data;
    free(nodeToBeDeleted);
    return returnValue;
}

int peek(Stack *stack){
    if(isEmpty(stack))
        return INT_MIN;
    return stack->head->data;
}

int size(Stack *stack){
    int length = 0;
    Node *traversalNode = stack->head;
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

void printStack(Stack *stack){
    if(isEmpty(stack)) return;
    int value = pop(stack);
    printStack(stack);
    push(stack, value);
    printf("%d  ", peek(stack));
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
            push(stack, value);
            break;
        case 2:
            pop(stack);
            break;
        case 3:
            if(isEmpty(stack)){
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

/*
Complexity Analysis ->
No. Operation               Time Complexity                 Space Complexity
1.  push                    O(1)                            O(1)
2.  pop                     O(1)                            O(1)
3.  peek                    O(1)                            O(1)
4.  size                    O(n)                            O(1)
5.  isEmpty                 O(1)                            O(1)
*/