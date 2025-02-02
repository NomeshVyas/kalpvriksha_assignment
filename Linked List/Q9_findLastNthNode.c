#include "linkedList.c"

Node* removeNthFromEnd(Node** head, int n) {
    int count = findLinkedListLength(*head) - n;
    Node *traversedNode = *head;
    if(count < 0){
        printf("Invalid Operation\n");
        exit(0);
    }
    if(count == 0){
        *head = (*head)->next;
        free(traversedNode);
        return *head;
    }
    while(count > 1){
        traversedNode = traversedNode->next;
        count--;
    }
    Node *deleteNode = traversedNode->next;
    traversedNode->next = traversedNode->next->next;
    free(deleteNode);
    return *head;
}

Node *findNthNode(Node* head, int n){
    int count = findLinkedListLength(head) - n;
    Node *traversedNode = head;
    if(count < 0){
        printf("Invalid Operation\n");
        exit(0);
    }
    while(count > 0){
        traversedNode = traversedNode->next;
        count--;
    }
    return traversedNode;
}

void handleOutput(Node *node, int n){
    printf("%dth Node : %d", n, node->data);
}

int main(){
    Node *head = createLinkedList();
    handleLinkedListInput(&head);
    checkInvalidSize(head);
    int n = handleIntegerInput("Enter value for N");
    printList(head, "Original List");
    Node *lastNthNode = findNthNode(head, n);
    handleOutput(lastNthNode, n);
    return 0;
}

/*
Testcases which I used ->
No. List                            K           List after delete operation
1.  1  2  3  4  5                   2           1  2  3  5
2.  1  2  3  4  5                   3           1  2  4  5
3.  1  2  3  4  5                   5           2  3  4  5
4.  1  3  5  7  9                   1           1  3  5  7
*/