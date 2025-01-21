#include <stdio.h>
#include <stdlib.h>
#include "linkedList.c"

Node *insertRecursively(linkedList **list, Node **head, int position, int value){
    if(position == 1){
        Node *newNode = createNode(value);
        newNode->next = *head;
        (*list)->nodeCount += 1;
        if((*list)->head == *head)
            (*list)->head = newNode;
        if(*head == NULL || (*head)->next == NULL)
            (*list)->tail = newNode;
        return newNode;
    }
    (*head)->next = insertRecursively(list, &((*head)->next), position - 1, value); 
    return *head;   
}

int main(){
    linkedList *list = createLinkedList();
    insertRecursively(&list, &(list->head), 1, 25);
    displayWithDetails(list);
    insertRecursively(&list, &(list->head), 2, 20);
    displayWithDetails(list);
    insertRecursively(&list, &(list->head), 1, 15);
    displayWithDetails(list);
    insertRecursively(&list, &(list->head), 4, 10);
    displayWithDetails(list);
    insertRecursively(&list, &(list->head), 5, 5);
    free(list);
    return 0;
}