#include<stdio.h>
#include<stdlib.h>
#define MAX_STR_LEN 50

int isVowel(char c){
    switch (c){
        case 'a' :
        case 'A' :
        case 'e' :
        case 'E' :
        case 'i' :
        case 'I' :
        case 'o' :
        case 'O' :
        case 'u' :
        case 'U' :
            return 1;
        default :
            return 0;
    }
}

int strLength(char *str){
    int len = 0;
    while(*str != '\0'){
        len++;
        str++;
    }

    return len;
}

void handleRowColumnInput(int *rowSize, int *columnSize){
    printf("Enter row size for matrix: ");
    scanf("%d", rowSize);
    printf("\nEnter column size for matrix: ");
    scanf("%d", columnSize);
    fflush(stdin);
}

void handleInput(char ***matrix, int rowSize, int columnSize){
    for(int row = 0; row < rowSize; row++)
        for(int column = 0; column < columnSize; column++){
            printf("Name at (%d,%d) : ", row, column);
            scanf("%20[^\n]s", *(*(matrix + row) + column));
            getchar();
        }
}

void printStringMatrix(char ***matrix, int rowSize, int columnSize){
    printf("\nThe 2D array of names is : \n");
    for(int row = 0 ; row < rowSize; row++){
        for(int column = 0; column < columnSize; column++)
            printf("%-20s", *(*(matrix + row) + column));
        printf("\n");
    }
}

void findNumberOfVowelNames(char ***matrix, int rowSize, int columnSize){
    int numberOfVowelNames = 0;
    for(int row = 0; row < rowSize; row++)
        for(int column = 0; column < columnSize; column++)
            if(isVowel(**(*(matrix + row) + column)))
                numberOfVowelNames++;
    
    printf("\nNumber of names starting with vowels : %d\n", numberOfVowelNames);
}

int findMaxLength(char ***matrix, int rowSize, int columnSize){
    int maxLength = 0, tempLength;
    for(int row = 0; row < rowSize; row++){    
        for(int column = 0; column < columnSize; column++){
            tempLength = strLength(*(*(matrix + row) + column));
            if(maxLength < tempLength)
                maxLength = tempLength;
        }
    }

    printf("\nMax Length : %d", maxLength);
    return maxLength;
}

void findAndPrintLongestName(char ***matrix, int rowSize, int columnSize){
    int maxLength = findMaxLength(matrix, rowSize, columnSize);

    printf("\nThe Longest first Name in Matrix : ");
    for(int row = 0; row < rowSize; row++)
        for(int column = 0; column < columnSize; column++)
            if(maxLength == strLength(*(*(matrix + row) + column))){
                printf("%s", *(*(matrix + row) + column));
                return;
            }
}

void handle2DArrayString(){
    int rowSize, columnSize;
    handleRowColumnInput(&rowSize, &columnSize);
    char ***matrix = (char ***) malloc(rowSize * sizeof(char **));
    for(int row = 0; row < rowSize; row++){
        *(matrix + row) = (char **) malloc(columnSize * sizeof(char *)); 
        for(int col = 0; col < columnSize; col++)
            *(*(matrix + row) + col) = (char *) malloc(MAX_STR_LEN * sizeof(char));
    }

    handleInput(matrix, rowSize, columnSize);
    printStringMatrix(matrix, rowSize, columnSize);
    findNumberOfVowelNames(matrix, rowSize, columnSize);
    findAndPrintLongestName(matrix, rowSize, columnSize);
}

int main(){
    handle2DArrayString();

    return 0;
}