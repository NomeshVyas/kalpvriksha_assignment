#include "linkedList.c"

Node *getIntersectionNode(Node *headA, Node *headB) {
    int len1 = findLinkedListLength(headA);
    int len2 = findLinkedListLength(headB);
    if(len1 > len2){
        int len = len1 - len2;
        while(len){
            headA = headA->next;
            len--;
        }
    } else {
        int len = len2 - len1;
        while(len){
            headB = headB->next;
            len--;
        }
    }
    while(headA && headB && headA != headB){
        headA = headA->next;
        headB = headB->next;
    }
    return headA;
}

int main(){
    Node *firstList = createLinkedList();
    handleLinkedListInput(&firstList);
    Node *secondList = createLinkedList();
    handleLinkedListInput(&secondList);
    printList(firstList, "First List");
    printList(secondList, "Second List");
    Node *intersactionPoint = getIntersectionNode(firstList, secondList);
    if(intersactionPoint)
        printf("Intersaction Point : %d", intersactionPoint->data);
    return 0;
}