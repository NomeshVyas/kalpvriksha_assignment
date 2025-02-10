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

int handleIntInput(char *prompt){
    printf("\n%s : ", prompt);
    int number;
    scanf("%d%*c", &number);
    return number;
}

char *handleStringInput(){
    printf("Enter List : ");
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

Node *findMiddle(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node *merge(Node *left, Node *right){
    Node *dummyHead = createNode(0);
    Node *tail = dummyHead;
    while(left && right){
        if(left->data >= right->data){
            tail->next = left;
            tail = left;
            left = left->next;
        } else {
            tail->next = right;
            tail = right;
            right = right->next;
        }
    }
    tail->next = left ? left : right;
    return dummyHead->next;
}

Node *mergeSort(Node *head){
    if(head == NULL || head->next == NULL) return head;
    Node *middle = findMiddle(head);
    Node *secondHead = middle->next;
    middle->next = NULL;
    head = mergeSort(head);
    secondHead = mergeSort(secondHead);
    return merge(head, secondHead);
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

Node *getTail(Node *head){
    while(head->next)
        head = head->next;
    return head;
}

Node *sortInKGroups(Node *head, int k){
    if(head == NULL || head->next == NULL) return head;
    Node *current = head;
    int count = 1;
    while(current && count < k){
        count++;
        current = current->next;
    }
    if(count < k) return head;
    Node *tailNext = sortInKGroups(current->next, k);
    current->next = NULL;
    head = mergeSort(head);
    Node *newTail = getTail(head);
    newTail->next = tailNext;
    return head;
}

int main(){
    char *string = handleStringInput();
    Node *head = constuctList(string);
    int k = handleIntInput("Enter value for K");
    printList(head);
    head = sortInKGroups(head, k);
    printList(head);
    free(string);
    return 0;
}