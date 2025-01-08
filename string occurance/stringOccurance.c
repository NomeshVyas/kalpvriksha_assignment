#include <stdio.h> 
#include <stdlib.h> 
#define MAX 100 
#define NUMBER_OF_ALPHABETS 26

void handleInput(char *string){
    printf("Enter string : "); 
    scanf("%100[^\n]s", string); 
    fflush(stdin); 
}

int alphaToIndex(char c){ 
    return c - 'a'; 
}

char indexToChar(int index){ 
    return 'a' + index; 
}

void findFreq(int *freq, char *string){ 
    while(*string != '\0'){ 
        *(freq + alphaToIndex(*string)) += 1; 
        string++; 
    }
}

void printOccurence(int *freq){ 
    printf("\nOccurances : ");
    for(int i = 0; i < NUMBER_OF_ALPHABETS; i++) 
        if(*(freq + i) > 0) 
            printf("%c%d", indexToChar(i), *(freq + i)); 
}

void handleCountFreqForString(){ 
    char *string = (char *) malloc(MAX * sizeof(char)); 
    int *freq = (int *)calloc(NUMBER_OF_ALPHABETS, sizeof(int)); 
    handleInput(string); 
    findFreq(freq, string); 
    printOccurence(freq); 
}

int main() { 
    handleCountFreqForString(); 
    return 0; 
}
