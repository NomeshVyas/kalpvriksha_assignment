#include "linkedList.c"

Node* mergeTwoLists(Node* list1, Node* list2) {
    Node *dummyHead = createNode(0);
    Node *tail = dummyHead;

    while(list1 && list2){
        if(list1->data < list2->data){
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = list1 ? list1 : list2;
    return dummyHead->next;
}

int main(){
    Node *firstList = createLinkedList();
    handleLinkedListInput(&firstList);
    checkInvalidSize(firstList);
    Node *secondList = createLinkedList();
    handleLinkedListInput(&secondList);
    checkInvalidSize(secondList);
    printList(firstList, "First Sorted List");
    Node *mergedList = mergeTwoLists(firstList, secondList);
    printList(mergedList, "Merged Sorted List");
    return 0;
}

/*
Testcases which I used ->
No. First List                  Second List                     Sorted List
1.  1  2  4                     1  3  4                         1  1  2  3  4  4
*/