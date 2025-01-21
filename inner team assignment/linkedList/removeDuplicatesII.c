#include "linkedList.c"

void removeDuplicates(linkedList **list){
    Node *prev = NULL;
    Node *traversalNode = (*list)->head;
    while (traversalNode){
        if(traversalNode->next && traversalNode->data == traversalNode->next->data){
            int value = traversalNode->data;
            while(traversalNode && value == traversalNode->data){
                traversalNode = traversalNode->next;
                (*list)->nodeCount -= 1;
            }
            if(prev)
                prev->next = traversalNode;
            else
                (*list)->head = traversalNode;
        } else {
            prev = traversalNode;
            traversalNode = traversalNode->next;
        }
    }
    (*list)->tail = prev;
}

int main(){
    linkedList *list = createLinkedList();
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 5);
    displayWithDetails(list);
    removeDuplicates(&list);
    displayWithDetails(list);
    return 0;
}