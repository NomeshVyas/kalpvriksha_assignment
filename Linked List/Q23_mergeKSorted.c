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
    if(*head == NULL){
        *head = createNode(value);
        return;
    }
    Node *tail = *head;
    while(tail->next)
        tail = tail->next;
    tail->next = createNode(value);
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

Node **handleInputAndCreateLists(int numberOfLists){
    Node **lists = (Node **) malloc(numberOfLists * sizeof(Node *));
    for(int i = 0; i < numberOfLists; i++){
        char *string = handleStringInput();
        lists[i] = constuctList(string);
        free(string);
    }
    return lists;
}

int handleIntInput(char *prompt){
    printf("\n%s : ", prompt);
    int number;
    scanf("%d%*c", &number);
    return number;
}

Node* mergeTwoLists(Node* list1, Node* list2) {
    Node *dummyHead = (Node *)malloc(sizeof(Node));
    Node *tail = dummyHead;

    while(list1 && list2){
        if(list1->data < list2->data){
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = list1 ? list1 : list2;
    return dummyHead->next;
}

Node* mergeKLists(Node** lists, int listsSize) {
    if(listsSize == 0) return NULL;
    if(listsSize == 1) return lists[0];
    Node *sorted = NULL;
    int end = listsSize - 1;

    while(end >= 0){
        sorted = mergeTwoLists(sorted, lists[end]);
        end--;
    }
    return sorted;
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

int main(){
    int numberOfLists = handleIntInput("Enter number of lists");
    Node **lists = handleInputAndCreateLists(numberOfLists);
    Node *mergedList = mergeKLists(lists, numberOfLists);
    printList(mergedList);
    return 0;
}