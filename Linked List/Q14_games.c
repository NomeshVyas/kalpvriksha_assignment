#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_ID_LEN 15
#define MAX 1000

typedef struct node {
    char *id;
    struct node *next;
} Node;

int stringLength(char *string){
    int length = 0;
    while(*string && *string != '"' && *string != ','){
        length++;
        string++;
    }
    return length;
}

char *createStringCopy(char *string){
    int length = stringLength(string);
    char *copyString = (char *) malloc((length + 1) * sizeof(char));
    int i = 0;
    while(*string && *string != '"' &&*string != ','){
        copyString[i++] = *string;
        string++;
    }
    copyString[i] = '\0';
    return copyString;
}

Node *createNode(char *id){
    Node *node = (Node *) malloc(sizeof(Node));
    node->id = createStringCopy(id);
    node->next = NULL;
    return node;
}

bool isExist(char *nodeId, char *id){
    while(*nodeId && *id){
        if(*nodeId != *id) return false;
        nodeId++;
        id++;
    }
    return *nodeId == '\0' && *id == '\0';
}

void insertAtEnd(Node **head, char *id){
    Node *node = createNode(id);
    if(*head == NULL){
        *head = node;
        return;
    }
    Node *tail = *head;
    while(tail->next && !isExist(tail->id, node->id))
        tail = tail->next;
    if(isExist(tail->id, node->id))
        free(node);
    else
        tail->next = node;
}

char *handleStringInput(char *prompt){
    printf("\n%s : \n", prompt);
    char *string = (char *) malloc(MAX * sizeof(char));
    scanf("%[^\n]%*c", string);
    return string;
}


bool skip(char character){
    return character == '"' || character == ',' || character == ' ';
}

bool isNumber(char character){
    return character >= '0' && character <= '9';
}

bool isValid(char *string){
    if(string[0] != 'I' || string[1] != 'T' || string[2] != 'T' || string[3] != '/' || !isNumber(string[4])) return false;
    string += 4;
    while(*string && *string != '"' && *string != ','){
        if(!isNumber(*string)) return false;
        string++;
    }
    return true;
}

Node *createList(char *string){
    Node *head = NULL;
    while(*string){
        while(skip(*string)) string++;
        if(isValid(string))
            insertAtEnd(&head, string);
        while(*string && *string != '"' && *string != ',') string++;
    }
    return head;
}

void printList(Node *head, char *string){
    printf("\n%s ->\n", string);
    bool first = true;
    while (head){
        printf(first ? "\"%s\"" : ", \"%s\"", head->id);
        first = false;
        head = head->next;
    }
}

Node *getMiddle(Node *head){
    Node *slow = head;
    Node *fast = head->next;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int convertInNumber(char *string){
    int number = 0;
    while(*string == 'T' || *string == 'I' || *string == '/') string++;
    while(isNumber(*string)){
        number = number * 10 + *string - '0';
        string++;
    }
    return number;
}

Node *merge(Node *left, Node *right){
    Node *dummyHead = createNode("\0");
    Node *tail = dummyHead;
    while(left && right){
        int leftNumber = convertInNumber(left->id);
        int rightNumber = convertInNumber(right->id);
        if(leftNumber <= rightNumber){
            tail->next = left;
            tail = left;
            left = left->next;
        } else {
            tail->next = right;
            tail = right;
            right = right->next;
        }
    }
    tail->next = left ? left : right;
    return dummyHead->next;
}

Node *mergeSort(Node *head){
    if(head == NULL || head->next == NULL) return head;
    Node *middle = getMiddle(head);
    Node *secondHead = middle->next;
    middle->next = NULL;
    head = mergeSort(head);
    secondHead = mergeSort(secondHead);
    return merge(head, secondHead);
}

Node *findIntersactionList(Node *foosball, Node *tennis){
    Node *dummyHead = createNode("\0");
    Node *tail = dummyHead;
    while(foosball && tennis){
        int foosballId = convertInNumber(foosball->id);
        int tennisId = convertInNumber(tennis->id);
        if(foosballId == tennisId){
            Node *node = createNode(foosball->id);
            tail->next = node;
            tail = node;
            foosball = foosball->next;
            tennis = tennis->next;
        } else if(foosballId > tennisId){
            tennis = tennis->next;
        } else {
            foosball = foosball->next;
        }
    }
    return dummyHead->next;
}

Node *findUniqueIDs(Node *foosball, Node *tennis){
    Node *dummyHead = createNode("\0");
    Node *tail = dummyHead;
    while(foosball && tennis){
        int foosballId = convertInNumber(foosball->id);
        int tennisId = convertInNumber(tennis->id);
        if(foosballId == tennisId){
            Node *node = createNode(foosball->id);
            tail->next = node;
            tail = node;
            foosball = foosball->next;
            tennis = tennis->next;
        } else if(foosballId < tennisId){
            Node *node = createNode(foosball->id);
            tail->next = node;
            tail = node;
            foosball = foosball->next;
        } else {
            Node *node = createNode(tennis->id);
            tail->next = node;
            tail = node;
            tennis = tennis->next;
        }
    }
    while(tennis){
        Node *node = createNode(tennis->id);
        tail->next = node;
        tail = node;
        tennis = tennis->next;
    }
    while(foosball){
        Node *node = createNode(foosball->id);
        tail->next = node;
        tail = node;
        foosball = foosball->next;
    }
    return dummyHead->next;
}

int main(){
    char *foosballStringInput = handleStringInput("Enter Foosball player's IDs");
    char *tennisStringInput = handleStringInput("Enter Tennis player's IDs");
    Node *foosball = createList(foosballStringInput);
    Node *tennis = createList(tennisStringInput);
    foosball = mergeSort(foosball);
    tennis = mergeSort(tennis);
    printList(foosball, "Foosball Players");
    printList(tennis, "Tennis Players");
    Node *intercationList = findIntersactionList(foosball, tennis);
    printList(intercationList, "Players who are participating in both games");
    Node *uniqueIDs = findUniqueIDs(foosball, tennis);
    printList(uniqueIDs, "Unique IDs");
    return 0;
}