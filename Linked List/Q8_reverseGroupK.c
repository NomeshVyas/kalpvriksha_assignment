#include "linkedList.c"

Node *reverse(Node *start, Node *end){
    Node *nodeTBecomeTail = start->next;
    Node *current = start->next;
    Node *previous = end;
    Node *next = NULL;
    while(current != end){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    start->next = previous;
    return nodeTBecomeTail;
}

Node *reverseKGroup(Node *head, int k){
    Node *dummyHead = createNode(0);
    dummyHead->next = head;
    Node *start = dummyHead;
    Node *current = head;
    int count = 0;
    while(current){
        count++;
        if(count == k){
            Node *next = current->next;
            start = reverse(start, current->next);
            count = 0;
            current = next;
        } else {
            current = current->next;
        }
    }
    return dummyHead->next;
}

int main(){
    Node *list = createLinkedList();
    handleLinkedListInput(&list);
    checkInvalidSize(list);
    int k = handleIntegerInput("Enter K value");
    printList(list, "Original List");
    Node *reversedKGroupList = reverseKGroup(list, k);
    printList(reversedKGroupList, "Reverse K Groups List");
    return 0;
}

/*
Testcases which I used ->
No. List                            K           Reverse K Group List
1.  1  2  3  4  5                   2           2  1  4  3  5
2.  1  2  3  4  5                   3           3  2  1  4  5
*/