#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct linkedList {
    Node *head;
    Node *tail;
} linkedList;

linkedList *createList(){
    linkedList *list = (linkedList *) malloc(sizeof(linkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *createNode(int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insertAtEnd(linkedList **list, int value){
    Node *node = createNode(value);
    if((*list)->head == NULL){
        (*list)->head = node;
        (*list)->tail = node;
        return;
    }
    node->prev = (*list)->tail;
    (*list)->tail->next = node;
    (*list)->tail = node;
}

Node *handleInput(linkedList **list){
    printf("Enter Sorted Linked List size (minimum length 2) : ");
    int length;
    scanf("%d", &length);
    if(length < 2){
        printf("invalid size");
        exit(0);
    }
    int value;
    printf("Enter elements for sorted list : \n");
    for(int i = 0; i < length; i++){
        printf("Enter value for %d-node : ", i + 1);
        scanf("%d", &value);
        insertAtEnd(list, value);
    }
}

int handleSumInput(){
    printf("\nEnter sum of two nodes you want to find in linked list : ");
    int sum;
    scanf("%d", &sum);
    return sum;
}

void printList(linkedList *list){
    Node *traversalNode = list->head;
    printf("\nList : ");
    while(traversalNode){
        printf("%d -> ", traversalNode->data);
        traversalNode = traversalNode->next;
    }
    printf("END");
}

void searchSum(linkedList *list, int sum){
    if(list->head == NULL){
        printf("\nList is empty.");
        return;
    }
    Node *left = list->head;
    Node *right = list->tail;
    
    while(left != right){
        if(left->data + right->data == sum) break;
        else if(left->data + right->data < sum)
            left = left->next;
        else
            right = right->prev;
    }
    if(left != right)
        printf("\nleft + right = sum -> %d + %d = %d", left->data, right->data, sum);
    else
        printf("\nNot Fount...");
}

int main(){
    linkedList *list = createList();
    handleInput(&list);
    printList(list);
    int sumToBeSearched = handleSumInput();
    searchSum(list, sumToBeSearched);
}