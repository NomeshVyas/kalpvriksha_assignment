#include <stdio.h>
#include <stdlib.h>
#define MAX 500

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter a sentence to find longest word in it : ");
    scanf("%[^\n]s", string);
    return string;
}

int findMaxLengthForWord(char *string){
    int max = 0, tempMax = 0;
    while(*string == ' ') string++;

    while(*string != '\0'){
        while(*string != ' ' && *string != '\0'){
            tempMax++;
            string++;
        }
        max = tempMax > max ? tempMax : max;
        tempMax = 0;
        while(*string == ' ') string++;
    }
    return max;
}

int findWordLength(char *word){
    int len = 0;
    while(*word != ' ' && *word != '\0'){
        len++;
        word++;
    }
    return len;
}

void stringCopy(char *source, char *target){
    while(*source != ' ' && *source != '\0'){
        *target = *source;
        target++;
        source++;
    }
    *target = '\0';
}

char *findLongestWord(char *string){
    int maxLength = findMaxLengthForWord(string);
    char *longest = (char *) malloc(maxLength * sizeof(char));
    int i = 0;

    while(*(string + i) != '\0'){
        while(*(string + i) == ' ') i++;
        int len = findWordLength(string + i);
        if(len == maxLength){
            stringCopy(string + i, longest);
            return longest;
        }
        
        while(*(string + i) != ' ' && *(string + i) != '\0') i++;
    }
}

void handleOutput(char *longestWord){
    printf("Longest word : %s", longestWord);
}

int main(){
    char *string = handleInput();
    char *longestWord = findLongestWord(string);
    handleOutput(longestWord);
    free(longestWord);
    free(string);
    return 0;
}

/*
Testcases which I used ->
1. hello world                              ->      hello
2. Nomesh Aayush Pulkit                     ->      Nomesh
3. NomeshVyas AayushGarg PulkitAhuja        ->      PulkitAhuja
4. 98765 4321 012345                        ->      012345
5. a abc abcd                               ->      abcd
6. The quick brown fox jumps                ->      quick
*/