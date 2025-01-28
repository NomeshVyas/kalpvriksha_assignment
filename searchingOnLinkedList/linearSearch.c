#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

void insertAtEnd(Node **head, int value){
    Node *node = createNode(value);
    if(*head == NULL){
        *head = node;
        return;
    }
    Node *temp = *head;
    while(temp->next)
        temp = temp->next;
    temp->next = node;
}

Node *handleInput(){
    printf("Enter Linked List size : ");
    int length;
    scanf("%d", &length);
    if(length < 1){
        printf("invalid size");
        exit(0);
    }
    int value;
    Node *head = NULL;
    for(int i = 0; i < length; i++){
        printf("Enter value for %d-node : ", i + 1);
        scanf("%d", &value);
        insertAtEnd(&head, value);
    }
    return head;
}

int handleSearchInput(){
    printf("\nEnter value to be searched : ");
    int element;
    scanf("%d", &element);
    return element;
}

void printList(Node *head){
    Node *traversalNode = head;
    printf("\nLinked List : \n");
    while(traversalNode){
        printf(" %d ->", traversalNode->data);
        traversalNode = traversalNode->next;
    }
    printf(" END");
}

int linearSearch(Node *head, int value){
    Node *traversalNode = head;
    int index = 0;
    while(traversalNode){
        if(traversalNode->data == value)
            return index;
        index++;
        traversalNode = traversalNode->next;
        
    }
    return traversalNode ? index : -1;
}

void handleOutput(int index, int element){
    if(index != -1)
        printf("\nelement : %d fount at index : %d", element, index);
    else    
        printf("\nelement not found");
}


int main(){
    Node *head = handleInput();
    int valueToBeSearched = handleSearchInput();
    int index = linearSearch(head, valueToBeSearched);
    handleOutput(index, valueToBeSearched);
    return 0;
}