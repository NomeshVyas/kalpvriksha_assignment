#include<stdio.h>
#include<stdlib.h>

void handleRowColumnSize(int *rowSize1, int *columnSize1, int *rowSize2, int *columnSize2){
    printf("Enter sizes for Matrix 1 -> \nrow size : ");
    scanf("%d", rowSize1);
    printf("column size : ");
    scanf("%d", columnSize1);
    printf("Enter sizes for Matrix 2 -> \nrow size : ");
    scanf("%d", rowSize2);
    printf("column size : ");
    scanf("%d", columnSize2);
    
    if(*columnSize1 != *rowSize2){
        printf("Invalid Matrix size for multiplication...");
        exit(1);
    }
}

void handleInputMatrix(int **matrix, int rowSize, int columnSize, int matrixNumber){
    printf("\nEnter Elements for matrix-%d -> ", matrixNumber);
    for(int row = 0; row < rowSize; row++)
        for(int column = 0; column < columnSize; column++){
            printf("\nValue for row-%d, column-%d : ", row, column);
            scanf("%d", *(matrix + row) + column);
        }
}

int **multiplyMatrix(int **matrix1, int **matrix2, int m, int n, int matrix1Columns){
    int **answer = (int **) malloc(m * sizeof(int *));
    for(int row = 0; row < m; row++)
        *(answer + row) = (int *) malloc(n * sizeof(int));

    for(int row = 0; row < m; row++)
        for(int column = 0; column < n; column++){
            *(*(answer + row) + column) = 0;
            for(int k = 0; k < matrix1Columns; k++)
                *(*(answer + row) + column) += *(*(matrix1 + row) + k) * *(*(matrix2 + k) + column);
        }

    return answer;
}

void printMatrix(int **matrix, int rowSize, int columnSize){
    printf("Multiplication of matrix1 and matrix2 : \n");
    for(int row = 0; row < rowSize; row++){
        for(int column = 0; column < columnSize; column++)
            printf("%d\t", *(*(matrix + row) + column));
        printf("\n");
    }
}

void handleMatrixMultiplication(){
    int rowSize1, columnSize1, rowSize2, columnSize2;
    handleRowColumnSize(&rowSize1, &columnSize1, &rowSize2, &columnSize2);

    int **matrix1 = (int **) malloc(rowSize1 * sizeof(int *));
    int **matrix2 = (int **) malloc(rowSize2 * sizeof(int *));
    
    for(int row = 0; row < rowSize1; row++)
        *(matrix1 + row) = (int *) malloc(columnSize1 * sizeof(int));
    for(int row = 0; row < rowSize2; row++)
        *(matrix2 + row) = (int *) malloc(columnSize2 * sizeof(int));

    handleInputMatrix(matrix1, rowSize1, columnSize1, 1);
    handleInputMatrix(matrix2, rowSize2, columnSize2, 2);    

    int **answer = multiplyMatrix(matrix1, matrix2, rowSize1, columnSize2, columnSize1);
    printMatrix(answer, rowSize1, columnSize2);
}

int main(){
    handleMatrixMultiplication();
    return 0;
}

/*
Used testcase ->
Matrix1 ->
1   2   3
4   5   6

Matrix2 ->
10  11
20  21
30  31

Answer ->
140     146
320     335
*/