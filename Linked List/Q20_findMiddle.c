#include "linkedList.c"

Node *findMiddleNode(Node *head){
    Node *slow = head;
    Node *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void handleOutput(Node *node){
    printf("Middle Node : %d", node->data);
}

int main(){
    Node *head = createLinkedList();
    handleLinkedListInput(&head);
    printList(head, "Original List");
    Node *middle = findMiddleNode(head);
    handleOutput(middle);
}
/*
Testcases which I used ->
No. List                            Middle
1.  1  2  3  4  5                   3
2.  1  2  3  4                      3                  
*/