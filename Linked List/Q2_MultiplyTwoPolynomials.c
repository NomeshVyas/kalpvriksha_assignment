#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int coefficient;
    int power;
    struct node *next;
} Node;

Node *createNode(int coefficient, int power){
    Node *node = (Node *) malloc(sizeof(Node));
    node->coefficient = coefficient;
    node->power = power;
    node->next = NULL;
    return node;
}

void insertAtEnd(Node **head, int coefficient, int power){
    if(*head == NULL || coefficient == 0){
        Node *node = createNode(coefficient, power);
        *head = node;
        return;
    }
    Node *traversedNode = *head;
    while(traversedNode->next && traversedNode->power != power)
        traversedNode = traversedNode->next;
    if(power == traversedNode->power){
        traversedNode->coefficient += coefficient;
    } else {
        Node *node = createNode(coefficient, power);
        traversedNode->next = node;
    }
}

int handleIntInput(char *prompt){
    int n;
    printf("\n%s : ", prompt);
    scanf("%d", &n);
    return n;
}

void handleLinkedListInput(Node **head){
    int size = handleIntInput("Enter Size for Polynomial");
    if(size < 1){
        printf("\nInvalid Size...");
        exit(0);
    }
    for(int i = 0; i < size; i++){
        int coefficient = handleIntInput("Coefficient");
        int power = handleIntInput("power");
        insertAtEnd(head, coefficient, power);
    }
}

Node *multiplyTwoPolynomials(Node *polynomial1, Node *polynomial2){
    if(polynomial1 == NULL || polynomial2 == NULL){
        printf("\nInvalid Polynomial");
        exit(0);
    }
    Node *multipliedPolynomial = NULL;
    Node *current1 = polynomial1;

    while(current1){
        Node *current2 = polynomial2;
        while(current2){
            int coefficient = current1->coefficient * current2->coefficient;
            int power = current1->power + current2->power;
            insertAtEnd(&multipliedPolynomial, coefficient, power);
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return multipliedPolynomial;
}

int abs(int number){
    if(number >= 0) return number;
    return number * -1;
}

void printPolyomial(Node *polynomial, char *string){
    printf("\n%s : ", string);
    bool first = true;
    while(polynomial){
        printf(!first && polynomial->coefficient >= 0 ? " + " : "");
        printf(polynomial->coefficient < 0 ? " - " : "");
        if(polynomial->power == 1){
            printf("x", abs(polynomial->coefficient));
        } else if(polynomial->power > 1){
            printf("%dx^%d", abs(polynomial->coefficient), polynomial->power);
        } else {
            printf("%d", abs(polynomial->coefficient));
        }
        first = false;
        polynomial = polynomial->next;
    }
}

int main(){
    Node *polynomial1 = NULL, *polynomial2 = NULL;
    handleLinkedListInput(&polynomial1);
    handleLinkedListInput(&polynomial2);
    printPolyomial(polynomial1, "First Polynomial");
    printPolyomial(polynomial2, "Second Polynomial");
    Node *multipliedPolynomial = multiplyTwoPolynomials(polynomial1, polynomial2);
    printPolyomial(multipliedPolynomial, "Multiplication of Polynomials");
    return 0;
}