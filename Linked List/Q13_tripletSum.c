#include "linkedList.c"
#define ASCENDING true
#define DESCENDING false

Node *findMiddle(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node *merge(Node *left, Node *right, bool order){
    Node *dummyHead = createNode(0);
    Node *tail = dummyHead;
    while(left && right){
        if(order){
            if(left->data < right->data){
                tail->next = left;
                tail = left;
                left = left->next;
            } else {
                tail->next = right;
                tail = right;
                right = right->next;
            }
        } else {
            if(left->data > right->data){
                tail->next = left;
                tail = left;
                left = left->next;
            } else {
                tail->next = right;
                tail = right;
                right = right->next;
            }
        }
    }
    tail->next = left ? left : right;
    return dummyHead->next;
}

Node *mergeSort(Node *head, bool order){
    if(head == NULL || head->next == NULL) return head;
    Node *middle = findMiddle(head);
    Node *secondHead = middle->next;
    middle->next = NULL;
    head = mergeSort(head, order);
    secondHead = mergeSort(secondHead, order);
    return merge(head, secondHead, order);
}

Node *createTripletNodes(int firstNumber, int secondNumber, int thirdNumber){
    Node *head = createNode(firstNumber);
    head->next = createNode(secondNumber);
    head->next->next = createNode(thirdNumber);
    return head;
}

Node *findTriplets(Node *first, Node *second, Node *third, int x){
    while(first){
        Node *secondTraversedNode = second;
        Node *thirdTraversedNode = third;
        int sum = 0;
        while(secondTraversedNode && thirdTraversedNode){
            sum = first->data + secondTraversedNode->data + thirdTraversedNode->data;
            if(sum == x) break;
            else if(sum < x) secondTraversedNode = secondTraversedNode->next;
            else thirdTraversedNode = thirdTraversedNode->next;
        }
        if(sum == x)
            return createTripletNodes(first->data, secondTraversedNode->data, thirdTraversedNode->data);
        first = first->next;
    }
    return NULL;
}

void handleOutput(Node *triplets, int x){
    if(triplets)
        printList(triplets, "Triplets");
    else
        printf("Triplets for %d : Not Found", x);
}

int main(){
    Node *first = createLinkedList();
    Node *second = createLinkedList();
    Node *third = createLinkedList();
    handleLinkedListInput(&first);
    checkInvalidSize(first);
    handleLinkedListInput(&second);
    checkInvalidSize(second);
    handleLinkedListInput(&third);
    checkInvalidSize(third);
    int x = handleIntegerInput("Enter the Sum which triplets you want");
    second = mergeSort(second, ASCENDING);
    third = mergeSort(third, DESCENDING);
    Node *triplets = findTriplets(first, second, third, x);
    handleOutput(triplets, x);
    return 0;
}
/*
Testcases which I used ->
No. First                   Second                      Third               x           Triplets
1.  1  2  3                 4  5  6                     7  8  9             15          1  5  9
2.  3  8  1  5              6  2  8                     11 4  12            22          3  8  11
3.  3  8  1  5              6  2  8                     11 4  2             14          8  2  4
*/