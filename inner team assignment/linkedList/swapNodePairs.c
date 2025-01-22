// Leetcode 24. Swap Nodes in Pairs
#include "linkedList.c"

Node *swap(Node *node){
    if(node == NULL || node->next == NULL) return node;
    Node *temp = swap(node->next->next);
    Node *t1 = node;
    Node *t2 = node->next;
    t2->next = t1;
    t1->next = temp;
    return t2;
}

int main(){
    linkedList *list = createLinkedList();
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 5);
    display(list);
    list->head = swap(list->head);
    display(list);
    return 0;
}
/*
Testcases which I used ->
1  2  3  4  5           ->          2  1  4  3  5
1  2  3                 ->          2  1  3
*/