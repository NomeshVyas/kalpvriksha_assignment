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

void printList(Node *head, char *heading){
    Node *traversalNode = head;
    printf("\nLinked List %s : \n", heading);
    while(traversalNode){
        printf(" %d ->", traversalNode->data);
        traversalNode = traversalNode->next;
    }
    printf(" END");
}

void swap(Node *a, Node *b){
    int temporaryVariable = a->data;
    a->data = b->data;
    b->data = temporaryVariable;
}

void bubbleSort(Node *head){
    Node *outerTraversalNode = head;
    Node *innerTraversalNode;
    Node *lastNodeForInnerLoop = head;
    while(lastNodeForInnerLoop->next)
        lastNodeForInnerLoop = lastNodeForInnerLoop->next;

    while(outerTraversalNode->next){
        innerTraversalNode = head;
        while(innerTraversalNode != lastNodeForInnerLoop){
            if(innerTraversalNode->data > innerTraversalNode->next->data)   
                swap(innerTraversalNode, innerTraversalNode->next);
            innerTraversalNode = innerTraversalNode->next;
        }
        lastNodeForInnerLoop = innerTraversalNode;
        outerTraversalNode = outerTraversalNode->next;
    }

}

int main(){
    Node *head = handleInput();
    printList(head, "before bubble sort");
    bubbleSort(head);
    printList(head, "after bubble sort");
    return 0;
}