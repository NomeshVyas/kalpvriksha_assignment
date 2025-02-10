#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000

typedef struct node {
    char *name;
    struct node *next;
} Node;

int findStringLength(char *string){
    int length = 0;
    while(*string && *string != ',' && *string != ']'){
        length++;
        string++;
    }
    return length;
}

char *createCopyString(char *string){
    char *copyString = (char *) malloc((findStringLength(string) + 1) * sizeof(char));
    int i = 0;
    while(*string && *string != ',' && *string != ' ' && *string != ']'){
        copyString[i++] = *string;
        string++;
    }
    copyString[i] = '\0';
    return copyString;
}

bool isExist(char *alreadyExistName, char *name){
    while(*alreadyExistName && *name){
        if(*alreadyExistName != *name) return false;
        alreadyExistName++;
        name++;
    }
    return *alreadyExistName == '\0' && *name == '\0';
}

Node *createNode(char *name){
    Node *node = (Node *) malloc(sizeof(Node));
    node->name = createCopyString(name);
    node->next = NULL;
    return node;
}

void insertAtEnd(Node **head, char *name){
    Node *node = createNode(name);
    if(*head == NULL){
        *head = node;
        return;
    }
    Node *tail = *head;
    while(tail->next && !isExist(tail->name, node->name))
        tail = tail->next;
    if(isExist(tail->name, node->name))
        free(node);
    else
        tail->next = node;
}

bool skip(char c){
    return c == ',' || c == ' ' || c == '[' || c == ']';
}

char *handleStringInput(char *prompt){
    printf("%s : ", prompt);
    char *input = (char *) malloc(MAX * sizeof(char));
    scanf("%[^\n]%*c", input);
    return input;
}

Node *createListFromString(char *string){
    Node *head = NULL;
    int i = 1;
    while(*string && *string != ']'){
        while(skip(*string)) string++;
        insertAtEnd(&head, string);
        while(*string && !skip(*string)) string++;
    }
    return head;
}

void printList(Node *head){
    printf("\nList : ");
    if(head == NULL){
        printf("Empty");
        return;
    }
    bool first = true;
    while(head){
        printf(first ? "[%s" : ", %s", head->name);
        first = false;
        head = head->next;
    }
    printf("]");
}

int main(){
    char *input = handleStringInput("Enter File Names");
    Node *head = createListFromString(input);
    printList(head);
    return 0;
}