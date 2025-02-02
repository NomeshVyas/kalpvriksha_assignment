#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Node *createLinkedList(){
    Node *head = (Node *) malloc(sizeof(Node));
    head = NULL;
    return head;
}

void insertAtBeginning(Node **head, int value){
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
        insertAtBeginning(head, value);
        return;
    }
    Node *node = createNode(value);
    Node *traversedNode = *head;
    while(traversedNode->next)
        traversedNode = traversedNode->next;
    traversedNode->next = node;
}

void deleteFirstNode(Node **head){
    if(*head == NULL){
        printf("List is already empty\n");
        return;
    }
    Node *nodeToBeDeleted = *head;
    (*head) = (*head)->next;
    free(nodeToBeDeleted);
}

void deleteLastNode(Node **head){
    if(*head == NULL || (*head)->next == NULL)
        deleteFirstNode(head);
    Node *previous = NULL;
    Node *current = *head;
    while(current->next){
        previous = current;
        current = current->next;
    }
    previous->next = NULL;
    free(current);
}

void printList(Node *head, char *tag){
    printf(head ? "%s -> " : "%s -> Empty", tag);
    while(head){
        printf("%d  ", head->data);
        head = head->next;
    }
    printf("\n");
}

void handleLinkedListInput(Node **head){
    int size, value;
    printf("Enter size : ");
    scanf("%d", &size);
    if(size < 1)
        return;
    for(int i = 0; i < size; i++){
        printf("Enter %d-node : ", i + 1);
        scanf("%d", &value);
        insertAtEnd(head, value);
    }
}

int findLinkedListLength(Node *head){
    int length = 0;
    while(head){
        length++;
        head = head->next;
    }
    return length;
}

void checkInvalidSize(Node *head){
    if(head == NULL){
        printf("Invalid Size\n");
        exit(0);
    }
}

int handleIntegerInput(char *prompt){
    int number;
    printf("%s : ", prompt);
    scanf("%d", &number);
    return number;
}