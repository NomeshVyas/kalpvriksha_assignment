#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int coffiecient;
    int power;
    struct node *next;
} Node;

Node *createNode(int coffiecient, int power){
    Node *node = (Node *) malloc(sizeof(Node));
    node->coffiecient = coffiecient;
    node->power = power;
    node->next = NULL;
    return node;
}

Node *createLinkedList(){
    Node *head = (Node *) malloc(sizeof(Node));
    head = NULL;
    return head;
}

void insertAtBeginning(Node **head, int coffiecient, int power){
    Node *node = createNode(coffiecient, power);
    if(*head == NULL){
        *head = node;
        return;
    }
    node->next = *head;
    *head = node;
}

void insertAtEnd(Node **head, int coffiecient, int power){
    if(*head == NULL){
        insertAtBeginning(head, coffiecient, power);
        return;
    }
    Node *traversedNode = *head;
    while(traversedNode->next){
        if(traversedNode->power == power){
            traversedNode->coffiecient += coffiecient;
            return;
        }
        traversedNode = traversedNode->next;
    }
    if(traversedNode->power == power){
        traversedNode->coffiecient += coffiecient;
        return;
    }
    Node *node = createNode(coffiecient, power);
    traversedNode->next = node;
}

void handleLinkedListInput(Node **head){
    int size, coffiecient, power;
    printf("Enter size : ");
    scanf("%d", &size);
    if(size < 1){
        printf("Invalid Size");
        return;
    }
    for(int i = 0; i < size; i++){
        printf("Enter %d-node values ->\nCoffiecient : ", i + 1);
        scanf("%d", &coffiecient);
        printf("Power of X : ");
        scanf("%d", &power);
        insertAtEnd(head, coffiecient, power);
    }
}

Node *addTwoPolynomials(Node *first, Node *second){
    Node *firstTraversed = first;
    Node *sum = createNode(0, 0);
    Node *tail = sum;
    while(firstTraversed){
        Node *secondTraversed = second;
        int coffiecient = firstTraversed->coffiecient;
        while(secondTraversed){
            if(secondTraversed->power == firstTraversed->power){
                coffiecient += secondTraversed->coffiecient;
                break;
            }
            secondTraversed = secondTraversed->next;
        }
        Node *node = createNode(coffiecient, firstTraversed->power);
        tail->next = node;
        tail = node;
        firstTraversed = firstTraversed->next;
    }
    return sum->next;
}

void handleOutput(Node *node){
    bool first = true;
    while(node){
        printf(first ? " " : " + ");
        first = false;
        printf("%d", node->coffiecient);
        if(node->power)
            printf("x^%d", node->power);
        node = node->next;
    }
}

int main(){
    Node *first = createLinkedList();
    handleLinkedListInput(&first);
    Node *second = createLinkedList();
    handleLinkedListInput(&second);
    Node *sum = addTwoPolynomials(first, second);
    handleOutput(sum);
}
/*
Testcases which I used ->
No. First Polynomial                Second Polynomial               Sum
1.  5x^3 + 4x^2 + 2                 3x^3 + x^2 + 7                  8x^3 + 5x^2 + 9
*/
