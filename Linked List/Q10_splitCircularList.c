#include "circularLinkedList.c"

void splitCircularListInTwoHalves(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast != head && fast->next != head){
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *middle = slow->next;
    fast = slow->next;
    slow->next = head;
    while(fast->next != head)
        fast = fast->next;
    fast->next = middle;
    printList(head, "First List");
    printList(middle, "Second List");
}

int main(){
    Node *list = createCircularLinkedList();
    handleLinkedListInput(&list);
    checkInvalidSize(list);
    printList(list, "Original List");
    splitCircularListInTwoHalves(list);
    return 0;
}