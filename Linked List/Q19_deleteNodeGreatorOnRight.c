#include "linkedList.c"

bool isSmaller(Node *head){
    int value = head->data;
    while(head){
        if(value < head->data) return true;
        head = head->next;
    }
    return false;
}

Node * deleteNodesThatHaveGreaterNodeOnRight(Node *head){
    Node *dummyHead = createNode(0);
    Node *tail = dummyHead;
    while(head){
        if(!isSmaller(head)){
            tail->next = head;
            tail = head;
        }
        head = head->next;
    }
    tail->next = NULL;
    return dummyHead->next;
}

int main(){
    Node *head = NULL;
    handleLinkedListInput(&head);
    printList(head, "Original List");
    Node *modifiedList = deleteNodesThatHaveGreaterNodeOnRight(head);
    printList(modifiedList, "Modified List");
    return 0;
}
/*
Testcases which I used ->
No. List                                        List after Delete Operation
1.  12  15  10  11  5  6  2  3                  15  11  6  3   
2.  1   2   3   4                               4              
3.  5   4   3   2   1                           5   4   3   2   1
*/