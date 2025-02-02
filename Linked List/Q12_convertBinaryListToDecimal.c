#include "linkedList.c"

unsigned findPowerForTwo(unsigned power){
    unsigned answer = 1;
    for(int i = 1; i <= power; i++)
        answer *= 2;
    return answer;
}

int binaryListToDecimal(Node *head, int *index){
    if(head == NULL) return 0;
    int answer = binaryListToDecimal(head->next, index);
    if(head->data)
        answer += findPowerForTwo(*index);
    *index += 1;
    return answer;
}

void handleOutput(int number){
    printf("Number Representation : %d", number);
}

int main(){
    Node *binaryNumberAsList = createLinkedList();
    handleLinkedListInput(&binaryNumberAsList);
    int index = 0;
    printList(binaryNumberAsList, "Binary Number");
    int number = binaryListToDecimal(binaryNumberAsList, &index);
    handleOutput(number);
    return 0;
}
/*
Testcases which I used ->
No. Binary Number                   Decimal Number
1.  1  0  1  1                      11
2.  
*/