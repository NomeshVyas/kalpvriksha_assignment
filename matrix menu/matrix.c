#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int **handleInput(int *n, int *m){
    printf("\nsize and number of operations : ");
    scanf("%d %d", m, n);
    if(*n < 1 || *n > 100 || *m < 1 || *m > 100){
        printf("invalid");
        exit(0);
    }
    int **img = (int **) malloc(*n * sizeof(int *));
    for(int i = 0; i < *n; i++)
        *(img + i) = (int *) calloc(*n, sizeof(int));
    return img;
}

void invertIndexInImage(int **img, int n){
    int i, j;
    printf("row and column (1 based) : ");
    scanf("%d %d", &i, &j);
    if(i < 1 || j < 1 || i > n || j > n){
        printf("\ninvalid");
        return;
    }
    if(*(*(img + i - 1) + j - 1))
        *(*(img + i - 1) + j - 1) = 0;
    else
        *(*(img + i - 1) + j - 1) = 1;
}

void flipImageHorizontally(int **img, int n){
    int mid = n / 2;
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= mid; j++)
            swap(*(img + i) + j, *(img + i) + n - 1 - j);
}

void transpose(int **img, int n){
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            swap(*(img + i) + j, *(img + j) + i);
}

void rotate90(int **img, int n){
    transpose(img, n);
    int mid = n / 2;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < mid; j++)
            swap(*(img + i) + j, *(img + n - 1 - i) + j);
}

void printMatrix(int **img, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", *(*(img + i) + j));
        printf("\n");
    }
}

void menu(int **img, int n, int m){
    while(m > 0){
        int operation;
        scanf("%d", &operation);
        switch(operation){
            case 1:
                invertIndexInImage(img, n);
                break;
            case 2:
                flipImageHorizontally(img, n);
                break;
            case 3:
                rotate90(img, n);
                break;
            default:
                printf("invalid");
        }
        m--;
    }
}

int main(){
    int n, m;
    int **img = handleInput(&n, &m);
    menu(img, n, m);
    printMatrix(img, n);

    for(int i = 0; i < n; i++)
        free(*(img + i));
    free(img);
    return 0;
}