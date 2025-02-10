#include "linkedList.c"

Node *findMiddleNode(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node *reverseList(Node *head){
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    while(current){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

Node *reorderList(Node *head){
    Node *middle = findMiddleNode(head);
    Node *reversedMiddleListhead = reverseList(middle->next);
    middle->next = NULL;
    Node *tail = head;
    Node *current = head->next;
    while(current && reversedMiddleListhead){
        tail->next = reversedMiddleListhead;
        reversedMiddleListhead = reversedMiddleListhead->next;
        tail->next->next = current;
        tail = current;
        current = current->next;
    }
    tail->next = current ? current : reversedMiddleListhead;
    return head;
}


int main(){
    Node *head = createLinkedList();
    handleLinkedListInput(&head);
    checkInvalidSize(head);
    printList(head, "Original List");
    Node *reorderedList = reorderList(head);
    printList(reorderedList, "Reordered List");
    return 0;
}
/*
Testcases which I used ->
No. List                            Reordered List
1.  1  2  3  4  5  6                1  6  2  5  3  4
2.  1  2  3  4  5                   1  5  2  4  3
*/