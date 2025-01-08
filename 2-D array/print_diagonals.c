#include<stdio.h>
#include<stdlib.h>

void printMatrix(int **matrix, int size){
    printf("\nMatrix : \n");
    
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++)
            printf("%d\t", *(*(matrix + row) + col));
        printf("\n");
    }
}

void handleInput(int **matrix, int size){
    for(int i = 0; i < size; i++)
        *(matrix + i) = (int *) malloc(size * sizeof(int));

    printf("\nEnter values in matrix : ");
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            printf("\nEnter value for : row-%d, cod-%d : ", row, col);
            scanf("%d", (*(matrix + row) + col));
            fflush(stdin);
        }
    }
}

void printDiagonalsLeftToRight(int **matrix, int size){
    printf("\nLeft to Right Digonal values :\n");
    for(int i = 0; i < size; i++){
        for(int space = 0; space < i; space++)
            printf("\t");
        printf("%d\n", *(*(matrix + i) + i));
    }
}

void printDiagonalsRightToLeft(int **matrix, int size){
    printf("\nRight to Left Digonal values :\n");
    for(int i = 0; i < size; i++){
        for(int space = size - 1; space > i; space--)
            printf("\t");
        printf("%d\n", *(*(matrix + i) + (size - 1 - i)));
    }
}

void handleDiagonalMatrix(){
    int size;
    int **matrix = (int **) malloc(size * sizeof(int *));
    
    printf("Enter size for square matrix : ");
    scanf("%d", &size);

    handleInput(matrix, size);
    printMatrix(matrix, size);
    printDiagonalsLeftToRight(matrix, size);
    printDiagonalsRightToLeft(matrix, size);
}

int main(){
    handleDiagonalMatrix();
    return 0;
}

// for pull request