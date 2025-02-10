#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *createNode(int data){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

char *handleStringInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter numbers : ");
    scanf("%[^\n]%*c", string);
    return string;
}

void insertAtEnd(Node **head, int value){
    Node *node = createNode(value);
    if(*head == NULL){
        *head = node;
        return;
    }
    Node *tail = *head;
    while(tail->next)
        tail = tail->next;
    tail->next = node;
}

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

Node *construtList(char *string){
    Node *head = NULL;
    int number = 0;
    while(*string){
        if(isNumber(*string)){
            number = number * 10 + *string - '0';
        } else if(*string == '\0' || *string == ' ') {
            insertAtEnd(&head, number);
            number = 0;
            while(*string == ' ') string++;
        } else {
            printf("Invalid Inputs...");
            exit(0);
        }
        if(*string) string++;
    }
    return head;
}

Node *saparateOddEven(Node *head){
    Node *dummyEvenHead = createNode(0);
    Node *dummyOddHead = createNode(0);
    Node *evenTail = dummyEvenHead;
    Node *oddTail = dummyOddHead;

    while(head){
        if(head->data & 1){
            oddTail->next = head;
            oddTail = head;
        } else {
            evenTail->next = head;
            evenTail = head;
        }
        head = head->next;
    }
    oddTail->next = NULL;
    evenTail->next = dummyOddHead->next;
    return dummyEvenHead->next;
}

void printList(Node *head){
    printf("\nList : ");
    if(head == NULL){
        printf("Empty");
        return;
    }
    while(head){
        printf("%d  ", head->data);
        head = head->next;
    }
}

int main(){
    char *stringInput = handleStringInput();
    printf("%s\n", stringInput);
    Node *head = construtList(stringInput);
    printList(head);
    Node *modifiedList = saparateOddEven(head);
    printList(modifiedList);
    return 0;
}

// 17 : 20