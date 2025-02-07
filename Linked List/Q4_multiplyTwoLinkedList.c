#include <stdio.h>
#include <stdlib.h>
#define MAX 200

typedef struct node{
    int data;
    struct node *next;
} Node;

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

void insertAtFirst(Node **head, int value){
    Node *node = createNode(value);
    if(*head == NULL){
        *head = node;
        return;
    }
    node->next = *head;
    *head = node;
}

void insertAtEnd(Node **head, int value){
    if(*head == NULL){
        insertAtFirst(head, value);
        return;
    }
    Node *tail = *head;
    while(tail->next)
        tail = tail->next;
    Node *node = createNode(value);
    tail->next = node;
}

int getInt(char *input){
    if(*input >= '0' && *input <= '9')
        return *input - '0';
    printf("\nInvalid Input");
    exit(0);
}

Node *handleInput(){    
    Node *head = NULL;
    char *input = (char *) malloc(MAX * sizeof(char));
    printf("Enter Number as Linked List : ");
    scanf("%[^\n]%*c", input);
    if(*input == '\0'){
        printf("Invalid Input...");
        exit(0);
    }
    while(*input){
        while(*input == ' ') input++;
        int digit = getInt(input);
        insertAtFirst(&head, digit);
        if(*input) input++;
    }
    return head;
}

void printList(Node *head){
    if(head == NULL){
        printf("\nNumber : ");
        return;
    }
    printList(head->next);
    printf("%d  ", head->data);
}

Node *addTwoNums(Node* firstNumber, Node* secondNumber, int carry){
    if(!firstNumber && !secondNumber )
        return carry ? createNode(carry) : NULL;
    int value = carry;
    if(firstNumber) value += firstNumber->data;
    if(secondNumber) value += secondNumber->data;
    carry = value / 10;
    value = value % 10;
    Node *node = createNode(value);
    if(firstNumber && !secondNumber)
        node->next = addTwoNums(firstNumber->next, secondNumber, carry);
    else if(!firstNumber && secondNumber)
        node->next = addTwoNums(firstNumber, secondNumber->next, carry);
    else
        node->next = addTwoNums(firstNumber->next, secondNumber->next, carry);
    return node;
}

Node *multiplyWithDigit(Node *number, int digit){
    int carry = 0, value;
    Node *multipliedList = NULL;
    while(number){
        value = digit * number->data + carry;
        carry = value / 10;
        value %= 10;
        insertAtEnd(&multipliedList, value);
        number = number->next;
    }
    if(carry) insertAtEnd(&multipliedList, carry);
    return multipliedList;
}

Node *multiply(Node *number1, Node *number2){
    Node *multipliedList = NULL, *tempList = NULL;
    int leadingZeros = 0;
    while(number1){
        tempList = multiplyWithDigit(number2, number1->data);
        for(int i = 0; i < leadingZeros; i++)
            insertAtFirst(&tempList, 0);
        multipliedList = addTwoNums(multipliedList, tempList, 0);
        number1 = number1->next;
        leadingZeros++;
        free(tempList);
    }
    return multipliedList;
}

int main(){
    Node *number1 = handleInput();
    Node *number2 = handleInput();
    printList(number1);
    printList(number2);
    Node *multipliedNumber = multiply(number1, number2);
    printList(multipliedNumber);
    return 0;
}