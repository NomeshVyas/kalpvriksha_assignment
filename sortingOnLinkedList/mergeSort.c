#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int length;
    printf("Enter Linked List size : ");
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
    printf("\nLinked List %s : ", heading);
    while(traversalNode){
        printf(" %d ->", traversalNode->data);
        traversalNode = traversalNode->next;
    }
    printf(" END");
}

Node *findMiddleNode(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node *mergeTwoSortedLists(Node *left, Node *right){
    Node *dummyNode = createNode(0);
    Node *sortedNode = dummyNode;

    while(left && right){
        if(left->data < right->data){
            sortedNode->next = left;
            sortedNode = left;
            left = left->next;
        } else {
            sortedNode->next = right;
            sortedNode = right;
            right = right->next;
        }
    }
    if(left) sortedNode->next = left;
    else sortedNode->next = right;

    return dummyNode->next;
}

Node *mergeSort(Node *head){
    if(!head || head->next == NULL) return head;
    Node *middleNode = findMiddleNode(head);
    Node *right = middleNode->next;
    middleNode->next = NULL;
    Node *left = head;
    left = mergeSort(left);
    right = mergeSort(right);
    
    return mergeTwoSortedLists(left, right);
}

int main(){
    Node *head = handleInput();
    printList(head, "before Merge Sort");
    head = mergeSort(head);
    printList(head, "after Merge Sort");
    return 0;
}