#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define TABLE_SIZE 10

typedef struct node {
    int key;
    int value;
    struct node *next;
} Node;

Node *createNode(int key, int value){
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

typedef struct hashmap {
    int capacity;
    Node **array;
} Hashmap;

Hashmap *createHashmap(int capacity){
    Hashmap *hashmap = (Hashmap *) malloc(sizeof(Hashmap));
    hashmap->capacity = capacity;
    hashmap->array = (Node **) calloc(hashmap->capacity, sizeof(Node *));
    return hashmap;
}

int hashFunction(Hashmap *hashmap, int key){
    int hash = 0, digitCount = 0;
    while(key){
        hash += (key * 17) % hashmap->capacity;
        key /= 10;
        digitCount++;
    }
    hash = (hash + digitCount) % hashmap->capacity;
    return hash;
}

void putInHashmap(Hashmap *hashmap, int key, int value){
    int hash = hashFunction(hashmap, key);
    if(hashmap->array[hash] == NULL){
        hashmap->array[hash] = createNode(key, value);
        return;
    }
    Node *tail = hashmap->array[hash];
    while(tail->next && tail->key != key)
        tail = tail->next;
    if(tail->key == key)
        tail->value = value;
    else
        tail->next = createNode(key, value);
}

int getHashmap(Hashmap *hashmap, int key){
    int hash = hashFunction(hashmap, key);
    if(hashmap->array[hash] == NULL) return INT_MIN;
    Node *tail = hashmap->array[hash];
    while(tail && tail->key != key)
        tail = tail->next;
    if(tail == NULL) return INT_MIN;
    return tail->value;
}

void removeFromHashmap(Hashmap *hashmap, int key){
    int hash = hashFunction(hashmap, key);
    if(hashmap->array[hash] == NULL) return;
    Node *tail = hashmap->array[hash];
    if(tail->key == key){
        hashmap->array[hash] = tail->next;
        free(tail);
        printf("Key %d deleted.\n", key);
        return;
    }
    Node *prev = NULL;
    while(tail->next && tail->key != key){
        prev = tail;
        tail = tail->next;
    }
    if(tail->key == key){
        prev->next = tail->next;
        free(tail);
        printf("Key %d deleted.\n", key);
    } else {
        printf("Not Found.\n");
    }
}

void display(Hashmap *hashmap){
    printf("\nHashMap : \n");
    bool isEmpty = true;
    for(int i = 0; i < hashmap->capacity; i++){
        if(hashmap->array[i]){
            isEmpty = false;
            Node *traversedNode = hashmap->array[i];
            printf("Index %d : ", i);
            bool first = true;
            while(traversedNode){
                printf(first ? "(%d, %d)" : "-> (%d, %d)", traversedNode->key, traversedNode->value);
                first = false;
                traversedNode = traversedNode->next;
            }
            printf("\n");
        }
    }
    if(isEmpty) printf("Empty\n");
}

int handleIntInput(char *prompt){
    int number;
    printf("%s : ", prompt);
    scanf("%d%*c", &number);
    return number;
}

bool isValid(int number){
    if(number < 0){
        printf("\nNegative keys and values are not acceptable...");
        return false;
    }
    return true;
}

void menu(Hashmap *hashmap){
    int operation, key, value;
    while(1){
        printf("\nAvalilable Options ->\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nSelect from given options : ");
        scanf("%d%*c", &operation);
        switch (operation){
        case 1:
            key = handleIntInput("Enter Key");
            if(!isValid(key)) break;
            value = handleIntInput("Enter value");
            if(!isValid(value)) break;
            putInHashmap(hashmap, key, value);
            break;
        case 2:
            key = handleIntInput("Enter Key");
            if(!isValid(key)) break;
            value = getHashmap(hashmap, key);
            if(value >= 0)
                printf("Value : %d\n", value);
            else
                printf("Not Found\n");
            break;
        case 3:
            key = handleIntInput("Enter Key");
            if(!isValid(key)) break;
            removeFromHashmap(hashmap, key);
            break;
        case 4:
            display(hashmap);
            break;
        case 5:
            return;
        default:
            printf("\nInvalid Input.");
        }
    }
}


int main(){
    Hashmap *hashmap = createHashmap(TABLE_SIZE);
    menu(hashmap);
    return 0;
}