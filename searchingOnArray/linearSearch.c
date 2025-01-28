#include <stdio.h>
#include <stdlib.h>

int *handleInput(int *length){
    printf("Enter Size : ");
    scanf("%d", length);
    if(*length < 1){
        printf("\nInvalid Size");
        exit(0);
    }
    int *array = (int *) malloc(*length * sizeof(int));

    int value;
    for(int i = 0; i < *length; i++){
        printf("Enter value for %d-index : ", i);
        scanf("%d", &value);
        array[i] = value;
    }

    return array;
}

void printArray(int *array, int length){
    printf("\nArray : ");
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
}

int handleSearchInput(){
    printf("\nEnter value to be searched : ");
    int element;
    scanf("%d", &element);
    return element;
}

int linearSearch(int *array, int length, int element){
    int index = -1;
    for(int i = 0; i < length; i++)
        if(array[i] == element){
            index = i;
            break;
        }
    return index;
}

void handleOutput(int element, int index){
    if(index != -1)
        printf("Element %d fount at index : %d", element, index);
    else
        printf("Element not fount...");
}

int main(){
    int length;
    int *array = handleInput(&length);
    printArray(array, length);
    int valueToBeSearched = handleSearchInput();
    int index = linearSearch(array, length, valueToBeSearched);
    handleOutput(valueToBeSearched, index);
}