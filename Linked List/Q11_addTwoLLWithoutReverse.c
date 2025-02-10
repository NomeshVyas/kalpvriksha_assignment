#include "linkedList.c"

Node *addTwoNumbers(Node *firstNumber, Node *secondNumber, int *carry){
    if(firstNumber == NULL && secondNumber == NULL) return NULL; 
    int firstDigitCount = findLinkedListLength(firstNumber);
    int secondDigitCount = findLinkedListLength(secondNumber);
    int value = 0;
    Node *head = firstNumber;
    if(firstDigitCount > secondDigitCount){
        head->next = addTwoNumbers(firstNumber->next, secondNumber, carry);
        value = firstNumber->data + *carry;
    } else if(firstDigitCount < secondDigitCount){
        head = secondNumber;
        head->next = addTwoNumbers(firstNumber, secondNumber->next, carry);
        value = secondNumber->data + *carry;
    } else {
        head->next = addTwoNumbers(firstNumber->next, secondNumber->next, carry);
        value = firstNumber->data + secondNumber->data + *carry;
    }
    *carry = value / 10;
    value %= 10;
    head->data = value;
    return head; 
}

Node *checkForRemainingCarry(Node *head, int carry){
    if(carry){
        Node *node = createNode(carry);
        node->next = head;
        return node;
    }
    return head;
}

int main(){
    Node *firstNumber = createLinkedList();
    handleLinkedListInput(&firstNumber);
    checkInvalidSize(firstNumber);
    Node *secondNumber = createLinkedList();
    handleLinkedListInput(&secondNumber);
    checkInvalidSize(secondNumber);
    printList(firstNumber, "First Number");
    printList(secondNumber, "Second Number");
    int carry = 0;
    Node *sum = addTwoNumbers(firstNumber, secondNumber, &carry);
    sum = checkForRemainingCarry(sum, carry);
    printList(sum, "Sum");
}
/*
Testcases which I used ->
No. First Number                    Second Number                   Sum
1.  1  2  3                         1  2  3                         2  4  6
2.  7  2  4  3                      5  6  4                         7  8  0  7
3.  9  9  9                         1                               1  0  0  0
4.  0                               8                               8
5.  9                               9                               1  8
*/