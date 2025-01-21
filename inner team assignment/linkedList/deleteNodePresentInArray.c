#include "linkedList.c"
#include <stdbool.h>
#define MAX 10000
// Delete Nodes From Linked List Present in Array

void modifiedList(int* nums, int numsSize, linkedList **list) {
    bool freq[MAX] = {false};
    for(int i = 0; i < numsSize; i++)
        *(freq + *(nums + i)) = true;
    
    Node *prev = NULL;
    Node *current = (*list)->head;

    while(current){
        if(*(freq + current->data)){
            Node *nodeToDelete = current;
            if(prev)
                prev->next = current->next;
            else
                (*list)->head = current->next;
            current = current->next;
            free(nodeToDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main(){
    int arraySize = 4;
    int *array = (int *) malloc(arraySize * sizeof(int));
    for(int i = 1; i <= arraySize; i++)
        *(array + i - 1) = i * 2;
    linkedList *list = createLinkedList();
    insertAtEnd(&list, 1);
    insertAtEnd(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);
    insertAtEnd(&list, 5);
    insertAtEnd(&list, 6);
    insertAtEnd(&list, 7);
    insertAtEnd(&list, 8);
    insertAtEnd(&list, 9);
    display(list);
    modifiedList(array, arraySize, &list);
    display(list);   
}

/*
Testcases which I used ->
No. List                                Array                   Result
1.  1->2->3->4->5->6->7->8->9           [2, 4, 5, 6, 8]         1->3->5->7->9
2.  1->2->1->2->1->2                    [1]                     2->2->2
*/