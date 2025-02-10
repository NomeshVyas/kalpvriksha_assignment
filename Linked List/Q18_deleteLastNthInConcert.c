#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct node {
    char *name;
    struct node *next;
} Node;

Node *createNode(char *name){
    Node *node = (Node *) malloc(sizeof(Node));
    char *nameForNode = (char *) malloc(MAX * sizeof(char));
    node->next = NULL;
    int i = 0;
    while(*name){
        nameForNode[i] = *name;
        name++;
        i++;
    }
    nameForNode[i] = '\0';
    node->name = nameForNode;
    return node;
}

void insertAtEnd(Node **head, char *name){
    Node *node = createNode(name);
    if(*head == NULL){
        *head = node;
        return;
    }
    Node *traversedNode = *head;
    while(traversedNode->next)
        traversedNode = traversedNode->next;
    traversedNode->next = node;
}

int handleIntInput(char *prompt){
    int number;
    printf("\n%s : ", prompt);
    scanf("%d%*c", &number);
    return number;
}

Node *handleInput(){
    Node *head = NULL;
    int size = handleIntInput("Enter size for List");
    char *name = (char *) malloc(MAX * sizeof(char));
    printf("Enter names one by one ->\n");
    for(int i = 0; i < size; i++){
        printf("Name - %d : ", i + 1);
        scanf("%[^\n]%*c", name);
        insertAtEnd(&head, name);
    }
    free(name);
    return head;
}

int getLength(Node *head){
    int len = 0;
    while(head){
        len++;
        head = head->next;
    }
    return len;
}

void printList(Node *head){
    if(head == NULL){
        printf("\nLine : Empty");
        return;
    }
    printf("\nLine : ");
    bool first = true;
    while(head){
        printf(first ? "%s" : " -> %s", head->name);
        first = false;
        head = head->next;
    }
}

void deleteLastNthNode(Node **head, int n){
    int length = getLength(*head);
    if(length < n || n < 1){
        printf("Invalid Input...");
        exit(0);
    }
    length -= n;
    Node *traversedNode = *head;
    if(length == 0){
        *head = (*head)->next;
        free(traversedNode);
        return;
    }
    for(int i = 1; i < length; i++)
        traversedNode = traversedNode->next;
    Node *nodeToBeDeleted = traversedNode->next;
    traversedNode->next = traversedNode->next->next;
    free(nodeToBeDeleted);
}

int main(){
    Node *head = handleInput();
    int n = handleIntInput("Enter value for N");
    printList(head);
    deleteLastNthNode(&head, n);
    printList(head);
    return 0;
}