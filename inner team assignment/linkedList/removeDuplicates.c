#include "linkedList.c"

void removeDuplicates(linkedList **list){
    Node *traversalNode = (*list)->head;
    while(traversalNode){
        while(traversalNode->next && traversalNode->data == traversalNode->next->data){
            traversalNode->next = traversalNode->next->next;
            (*list)->nodeCount -= 1;
        }
        traversalNode = traversalNode->next;
    }
}

int main(){
    linkedList *list = createLinkedList();
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 4);
    displayWithDetails(list);
    removeDuplicates(&list);
    displayWithDetails(list);
    free(list);
    return 0;
}