#include <stdio.h>
#include <stdlib.h>

int *handleInput(int *length)
{
    printf("Enter Size : ");
    scanf("%d", length);
    if (*length < 1)
    {
        printf("\nInvalid Size");
        exit(0);
    }
    int *array = (int *)malloc(*length * sizeof(int));

    int value;
    for (int i = 0; i < *length; i++)
    {
        printf("Enter value for %d-index : ", i);
        scanf("%d", &value);
        array[i] = value;
    }

    return array;
}

void printArray(int *array, int length)
{
    printf("\nArray : ");
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
}

int handleSearchInput()
{
    printf("\nEnter value to be searched : ");
    int element;
    scanf("%d", &element);
    return element;
}

int binarySearch(int *array, int left, int right, int value)
{
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (array[mid] == value)
        return mid;
    if (array[mid] < value)
        return binarySearch(array, mid + 1, right, value);
    else
        return binarySearch(array, left, mid - 1, value);
}

void handleOutput(int element, int index)
{
    if (index != -1)
        printf("Element %d found at index : %d", element, index);
    else
        printf("Element not found...");
}

int main()
{
    int length;
    int *array = handleInput(&length);
    printArray(array, length);
    int valueToBeSearched = handleSearchInput();
    int index = binarySearch(array, 0, length - 1, valueToBeSearched);
    // printf("...%d", index);
    handleOutput(valueToBeSearched, index);
}