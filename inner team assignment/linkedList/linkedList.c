#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct singlyLinkedList {
    Node *head;
    Node *tail;
    int nodeCount;
} linkedList;

Node *createNode(int value){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

linkedList *createLinkedList(){
    linkedList *list = (linkedList *) malloc(sizeof(linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->nodeCount = 0;
    return list;
}

void insertAtBeginning(linkedList **list, int value){
    Node *newNode = createNode(value);
    (*list)->nodeCount += 1;
    if((*list)->head == NULL){
        (*list)->head = newNode;
        (*list)->tail = newNode;
        return;
    }
    newNode->next = (*list)->head;
    (*list)->head = newNode;
}

void insertAtEnd(linkedList **list, int value){
    if((*list)->head == NULL){
        insertAtBeginning(list, value);
        return;
    }
    Node *newNode = createNode(value);
    (*list)->tail->next = newNode;
    (*list)->tail = newNode;
    (*list)->nodeCount += 1;
}

void insertAtPosition(linkedList **list, int position, int value){
    if(position < 1 || (*list)->nodeCount + 1 < position){
        printf("\ninvalid");
        return;
    } else if(position == (*list)->nodeCount + 1){
        insertAtEnd(list, value);
        return;
    }
    Node *traversalNode = (*list)->head;
    for(int i = 1; i < position - 1; i++)
        traversalNode = traversalNode->next;

    Node *newNode = createNode(value);
    newNode->next = traversalNode->next;
    traversalNode->next = newNode;
    (*list)->nodeCount += 1;
}

void display(linkedList *list){
    Node *temp = list->head;
    printf("\n");
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayWithDetails(linkedList *list){
    if(list->head)
        printf("\nCount : %d\tHead : %d\tTail : %d\n", list->nodeCount, list->head->data, list->tail->data);
    else
        printf("\nCount : %d\tHead : NULL\tTail : NULL\n", list->nodeCount);
    Node *temp = list->head;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void updateAtPosition(linkedList **list, int position, int value){
    if(position < 1 || position > (*list)->nodeCount){
        printf("\ninvalid");
        return;
    }
    Node *temp = (*list)->head;
    for(int i = 1; i < position; i++)
        temp = temp->next;
    temp->data = value;
}

void deleteAtBeginning(linkedList **list){
    if((*list)->head == NULL){
        printf("\ninvalid");
        return;
    }
    Node *previousHead = (*list)->head;
    (*list)->head = (*list)->head->next;
    (*list)->nodeCount -= 1;
    free(previousHead);
}

void deleteAtEnd(linkedList **list){
    if((*list)->head == NULL){
        printf("\ninvalid");
        return;
    }
    if((*list)->head->next == NULL){
        (*list)->nodeCount = 0;
        free((*list)->head);
        (*list)->head = (*list)->tail = NULL;
    }
    Node *previousHead = (*list)->head;
    while(previousHead->next->next != NULL)
        previousHead = previousHead->next;

    free((*list)->tail);
    previousHead->next = NULL;
    (*list)->tail = previousHead;
    (*list)->nodeCount -= 1;
}

void deleteAtPosition(linkedList **list, int position){
    if(position < 1 || position > (*list)->nodeCount){
        printf("\ninvalid");
        return;
    } else if(position == (*list)->nodeCount){
        deleteAtEnd(list);
        return;
    } else if(position == 1){
        deleteAtBeginning(list);
        return;
    }
    Node *traversalNode = (*list)->head;
    for(int i = 1; i < position - 1; i++)
        traversalNode = traversalNode->next; 
    Node *deleteNode = traversalNode->next;
    traversalNode->next = traversalNode->next->next;
    (*list)->nodeCount -= 1;
    free(deleteNode);
}