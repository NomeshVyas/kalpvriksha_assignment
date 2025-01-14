#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

char *handleInput(){
    printf("Enter string to count words : ");
    char *string = (char *) malloc(MAX * sizeof(char));
    scanf("%[^\n]s", string);
    return string;
}

int stringLength(char *string){
    int len = 0; 
    while(*string != '\0'){
        len++;
        string++;
    }
    
    return len;
}

int countWords(char *string){
    int count = 0;
    while(*string == ' ') string++;
    int len = stringLength(string);
    while(len > 0 && *(string + len - 1) == ' '){
        *(string + len - 1) = '\0';
        len--;
    }
    
    while(*string != '\0'){
        while(*string != '\0' && *string != ' ') string++;
        count++;
        while(*string == ' ') string++;
    }
    
    return count;
}

void printOutput(int count){
    printf("word count : %d", count);
}

void countNumberOfWords(){
    char *string = handleInput();
    int count = countWords(string);
    printOutput(count);
    free(string);
}

int main(){
    countNumberOfWords();
    return 0;
}
/*
Testcases which I used ->
No. Sentence                                Word Count
1.  Hello World                             2
2.  The quick brown fox                     4
3.  This is a test                          4
*/
