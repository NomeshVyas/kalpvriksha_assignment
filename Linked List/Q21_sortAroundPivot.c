#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000

typedef struct node{
    int data;
    struct node *next;
} Node;

Node *createNode(int data){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
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

void printList(Node *head){
    printf("\nList : ");
    if(head == NULL){
        printf("Empty");
        return;
    }
    bool first = true;
    while(head){
        printf(first ? "%d" : " -> %d", head->data);
        first = false;
        head = head->next;
    }
}

void swap(Node *first, Node *second){
    int temp = first->data;
    first->data = second->data;
    second->data = temp;
}

Node *partition(Node *head, Node *tail){
    Node *pivot = head;
    Node *previous = head;
    Node *current = head;
    while(current != tail->next){
        if(current->data < pivot->data){
            swap(current, previous->next);
            previous = previous->next;
        }
        current = current->next;
    }
    swap(previous, pivot);
    return previous;
}

void quickSort(Node *head, Node *tail){
    if(head == NULL || head == tail) return;
    Node *pivot = partition(head, tail);
    quickSort(head, pivot);
    quickSort(pivot->next, tail);
}


Node *rearangeAndSort(Node *head, int pivot){
    Node *less = createNode(0);
    Node *tailLess = less;
    Node *greatorOrEqual = createNode(0);
    Node *tailGreator = greatorOrEqual;
    while(head){
        if(head->data < pivot){
            tailLess->next = head;
            tailLess = head;
        } else {
            tailGreator->next = head;
            tailGreator = head;
        }
        head = head->next;
    }
    tailLess->next = NULL;
    tailGreator->next = NULL;
    quickSort(less->next, tailLess);
    quickSort(greatorOrEqual->next, tailGreator);
    tailLess->next = greatorOrEqual->next;
    return less->next;
}

char *handleStringInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    scanf("%[^\n]%*c", string);
    return string;
}

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

Node *constuctList(char *string){
    Node *head = NULL;
    while(*string){
        while(*string && !isNumber(*string)) string++;
        if(*string == '\0') break;
        int number = 0;
        while(isNumber(*string)){
            number = number * 10 + *string - '0';
            string++;
        }
        insertAtEnd(&head, number);
    }
    return head;
}

int handleIntInput(){
    int number;
    scanf("%d", &number);
    return number;
}

int main(){
    char *input = handleStringInput();
    Node *head = constuctList(input);
    int pivot = handleIntInput();
    rearangeAndSort(head, pivot);
    printList(head);
    return 0;
}