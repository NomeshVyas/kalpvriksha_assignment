#include "linkedList.c"

Node *addTwoNums(Node* firstNumber, Node* secondNumber, int carry){
    if(!firstNumber && !secondNumber )
        return carry ? createNode(carry) : NULL;
    int value = carry;
    if(firstNumber) value += firstNumber->data;
    if(secondNumber) value += secondNumber->data;
    carry = value / 10;
    value = value % 10;
    Node *node = createNode(value);
    if(firstNumber && !secondNumber)
        node->next = addTwoNums(firstNumber->next, secondNumber, carry);
    else if(!firstNumber && secondNumber)
        node->next = addTwoNums(firstNumber, secondNumber->next, carry);
    else
        node->next = addTwoNums(firstNumber->next, secondNumber->next, carry);
    return node;
}

int main(){
    Node *firstNumber = createLinkedList();
    handleLinkedListInput(&firstNumber);
    checkInvalidSize(firstNumber);
    Node *secondNumber = createLinkedList();
    handleLinkedListInput(&secondNumber);
    checkInvalidSize(secondNumber);
    Node *sum = addTwoNums(firstNumber, secondNumber, 0);
    printList(firstNumber, "First Number");
    printList(secondNumber, "Second Number");
    printList(sum, "Sum");
    return 0;
}

/*
Testcases which I used ->
No. First number                        Second number                           Sum
1.  2  4  3                             5  6  4                                 7  0  8
2.  0                                   0                                       0
3.  9  9  9  9  9  9  9                 9  9  9  9                              8  9  9  9  0  0  0  1
*/