#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct stackUsingArray {
    int *array;
    unsigned capacity;
    int top;
} Stack;

Stack *createStack(unsigned capacity){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->array = (int *) malloc (capacity * sizeof(int));
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

bool isFull(Stack *stack){
    return stack->top == stack->capacity - 1;
}

bool isEmpty(Stack *stack){
    return stack->top == -1;
}

void push(Stack *stack, int value){
    if(isFull(stack)){
        printf("Overflow\n");
        return;
    }
    stack->array[++stack->top] = value;
}

int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("Underflow\n");
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

int peek(Stack *stack){
    if(isEmpty(stack)){
        printf("Queue is Empty\n");
        return INT_MIN;
    }
    return stack->array[stack->top];
}

int size(Stack *stack){
    return stack->top + 1;
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
    int size = handleIntegerInput("Enter size for stack");
    Stack *stack = createStack(size);
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
4.  size                    O(1)                            O(1)
5.  isEmpty                 O(1)                            O(1)
6.  isFull                  O(1)                            O(1)
*/