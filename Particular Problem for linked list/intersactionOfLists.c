/*
There are two linked lists, each containing the roll numbers of students who have enrolled for a particular game:
- The first list represents the students who have registered for pool.
- The second list represents the students who have registered for fuse ball.

Your task is to find the students who have enrolled in both games and check whether a given student is playing both games.
*/ 
  
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
    printf("\nEnter Linked List size : ");
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
    printf("\n%s Linked List : \n", heading);
    while(traversalNode){
        printf(" %d ->", traversalNode->data);
        traversalNode = traversalNode->next;
    }
    printf(" END");
}

int searchPrompt(){
    int number;
    printf("\nEnter the Value you want to search in Intersaction : ");
    scanf("%d", &number);
    return number;
}

Node *getMiddle(Node *head){
    Node *slow = head;
    Node *fast = head->next;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node *mergeTwoSortedLists(Node *listOnehead, Node *listTwoHead){
    Node *dummyHead = createNode(0);
    Node *tailOfSortedList = dummyHead;
    while(listOnehead && listTwoHead){
        if(listOnehead->data < listTwoHead->data){
            tailOfSortedList->next = listOnehead;
            tailOfSortedList = listOnehead;
            listOnehead = listOnehead->next;
        } else {
            tailOfSortedList->next = listTwoHead;
            tailOfSortedList = listTwoHead;
            listTwoHead = listTwoHead->next;
        }
    }
    tailOfSortedList->next = listOnehead ? listOnehead : listTwoHead;
    return dummyHead->next;
}

Node *mergeSort(Node *head){
    if(!head || head->next == NULL)
        return head;
    Node *middleNode = getMiddle(head);
    Node *nextHalfHead = middleNode->next;
    middleNode->next = NULL;
    head = mergeSort(head);
    nextHalfHead = mergeSort(nextHalfHead);

    return mergeTwoSortedLists(head, nextHalfHead);
}

Node *findIntersactionList(Node *listOneHead, Node *listTwoHead){
    listOneHead = mergeSort(listOneHead);
    listTwoHead = mergeSort(listTwoHead);
    Node *dummyHeadOfIntersaction = createNode(0);
    Node *tailOfIntersaction = dummyHeadOfIntersaction;

    while(listOneHead && listTwoHead){
        if(listOneHead->data == listTwoHead->data){
            tailOfIntersaction->next = listOneHead;
            tailOfIntersaction = listOneHead;
            listOneHead = listOneHead->next;
            listTwoHead = listTwoHead->next;
        } else if(listOneHead->data < listTwoHead->data){
            listOneHead = listOneHead->next;
        } else {
            listTwoHead = listTwoHead->next;
        }
    }
    return dummyHeadOfIntersaction->next;
}

bool searchInList(Node *head, int value){
    while(head){
        if(head->data == value)
            return true;
        head = head->next;
    }
    return false;
}

void handleOutput(bool check){
    if(check)
        printf("\nValue exist in intersaction list.");
    else
        printf("\nValue not exist in intersaction list.");
}

int main(){
    Node *listOneHead = handleInput();
    printList(listOneHead, "First");
    Node *listTwoHead = handleInput();
    printList(listTwoHead, "Second");
    Node *intersactionList = findIntersactionList(listOneHead, listTwoHead);
    printList(intersactionList, "Intersaction");
    int valueToBeSearched = searchPrompt();
    bool check = searchInList(intersactionList, valueToBeSearched);
    handleOutput(check);
    return 0;
}
/*
Time Complexity ->
mergeSort = O(n logn) + O(n logn)
search = O(n)
~ O(n logn)
*/

/*
No.     List One                                List two                            Intersaction List                           Find        Output
1.      2->8->6->4->1                           1->4->2->3->9->8->0                 1->2->4->8                                  8           true
2.      9->7->5->3                              8->6->4->2                          NULL                                        9           false
*/