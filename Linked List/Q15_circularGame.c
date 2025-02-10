#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 1000

typedef struct node {
    char *id;
    struct node *next;
} Node;

int stringLength(char *string){
    int length = 0;
    while(*string && *string != '"' && *string != ','){
        length++;
        string++;
    }
    return length;
}

char *createStringCopy(char *string){
    int length = stringLength(string);
    char *copyString = (char *) malloc((length + 1) * sizeof(char));
    int i = 0;
    while(*string && *string != '"' &&*string != ','){
        copyString[i++] = *string;
        string++;
    }
    copyString[i] = '\0';
    return copyString;
}

Node *createNode(char *id, Node *next){
    Node *node = (Node *) malloc(sizeof(Node));
    node->id = createStringCopy(id);
    node->next = next;
    return node;
}

bool isExist(char *nodeId, char *id){
    while(*nodeId && *id){
        if(*nodeId != *id) return false;
        nodeId++;
        id++;
    }
    return *nodeId == '\0' && *id == '\0';
}

void insertAtEnd(Node **head, char *id){
    if(*head == NULL){
        Node *node = createNode(id, NULL);
        node->next = node;
        *head = node;
        return;
    }
    Node *tail = *head;
    Node *node = createNode(id, *head);
    while(tail->next != *head && !isExist(tail->id, node->id))
        tail = tail->next;
    if(isExist(tail->id, node->id)) return;
    tail->next = node;
}

char *handleStringInput(char *prompt){
    printf("\n%s : \n", prompt);
    char *string = (char *) malloc(MAX * sizeof(char));
    scanf("%[^\n]%*c", string);
    return string;
}


bool skip(char character){
    return character == '"' || character == ',' || character == ' ';
}

bool isNumber(char character){
    return character >= '0' && character <= '9';
}

bool isValid(char *string){
    if(string[0] != 'I' || string[1] != 'T' || string[2] != 'T' || string[3] != '/' || !isNumber(string[4])) return false;
    string += 4;
    while(*string && *string != '"' && *string != ','){
        if(!isNumber(*string)) return false;
        string++;
    }
    return true;
}

Node *createList(char *string){
    Node *head = NULL;
    while(*string){
        while(skip(*string)) string++;
        if(isValid(string))
            insertAtEnd(&head, string);
        while(*string && *string != '"' && *string != ',') string++;
    }
    return head;
}

void printList(Node *head, char *string){
    printf("\n%s ->\n", string);
    bool first = true;
    while (head){
        printf(first ? "\"%s\"" : ", \"%s\"", head->id);
        first = false;
        head = head->next;
    }
}

int handleIntInput(char *prompt){
    int number;
    printf("%s : ", prompt);
    scanf("%d%*c", &number);
    return number;
}

bool isOnlyOneLeft(Node *head){
    return head && head->next == head;
}

int findLengthOfCircularList(Node *head){
    if(head == NULL) return 0;
    Node *tail = head;
    int count = 1;
    while(tail->next != head){
        count++;
        tail = tail->next;
    }
    return count;
}

Node *findTail(Node *head){
    Node *tail = head->next;
    while(tail != head) 
        tail = tail->next;
    return tail;
}

Node *performGame(Node *circularListHead, int k){
    int count = 0;
    int length = findLengthOfCircularList(circularListHead);
    k = k % length;
    Node *prev = findTail(circularListHead);
    Node *current = circularListHead;
    Node *dummyHead = createNode("\0", NULL);
    Node *tail = dummyHead; 
    while(!isOnlyOneLeft(current)){
        count++;
        if(count == k){
            prev->next = current->next;
            tail->next = current;
            tail = current;
            current = prev->next;
            count = 0;
        } else {
            prev = current;
            current = current->next;
        }
    }
    current->next = NULL;
    tail->next = current;
    return dummyHead->next;
}

int main(){
    char *gameIDsStringInput = handleStringInput("Enter Player's IDs");
    Node *gameIDs = createList(gameIDsStringInput);
    int k = handleIntInput("Enter value for K");
    Node *eliminationList = performGame(gameIDs, k);
    printList(eliminationList, "After Game");
    return 0;
}