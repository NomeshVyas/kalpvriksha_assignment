#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define ASCI 256

char **handleInput(int *n){
    printf("Enter n : ");
    scanf("%d", n);
    char **group = (char **)malloc((*n) * sizeof(char *));
    for(int i = 0; i < *n; i++)
        group[i] = (char *)malloc(MAX * sizeof(char));
    getchar();
    for(int i = 0; i < *n; i++)
        scanf("%[^\n]%*c", group[i]);

    return group;
}

int *freqArr(char *string){
    int *freq = (int *) calloc(ASCI, sizeof(int));
    while(*string){
        *(freq + *string) += 1;
        string++;
    }
    return freq;
}

int matchFreq(int *freq1, int*freq2){
    for(int i = 0; i < ASCI; i++)
        if(*(freq1 + i) != *(freq2 + i)) return 0;
    return 1;
}

int allZero(int *freq){
    for(int i = 0; i < ASCI; i++)
        if(*(freq + i)) return 0;
    return 1;
}

void setAllZero(int *freq){
    for(int i = 0; i <ASCI; i++)
        *(freq + i) = 0;
}

void groupAnagram(char **group, int size){
    int **freq = (int **) malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++)
        *(freq + i) = freqArr(*(group + i));

    prinf("[");
    for(int i = 0; i < size; i++){
        if(allZero(*(freq + i))) continue;
        printf("[%s", *(group + i));
        for(int j = i + 1; j < size; j++){
            if(matchFreq(*(freq + i), *(freq + j))){
                printf(" ,%s", *(group + j));
                setAllZero(*(freq + j));
            }
        }
        printf("]");
    }
    printf("]");
}

int main(){
    int size;
    char **group = handleInput(&size);
    groupAnagram(group, size);

    return 0;
}