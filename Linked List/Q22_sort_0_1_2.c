#include "linkedList.c"

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
        if(left->data <= right->data){
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

int main(){
    Node *head = createLinkedList();
    handleLinkedListInput(&head);
    printList(head, "Original List");
    Node *sortedList = mergeSort(head);
    printList(sortedList, "Sorted List");
    return 0;
}
/*
Testcases which I used ->
No. List                            Sorted List
1.  1  2  0  1  2  0                0  0  1  1  2  2
2.  2  2  1  1  0  0                0  0  1  1  2  2
*/