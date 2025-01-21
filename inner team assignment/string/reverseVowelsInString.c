// Leetcode 345
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("String : ");
    scanf("%s", string);
    return string;
}

int isVowel(char c){
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

char* reverseVowels(char* s) {
    int len = strlen(s);
    int left = 0, right = len - 1;

    while(left < right){
        while(left < right && !isVowel(*(s + left))) left++;
        while(left < right && !isVowel(*(s + right))) right--;
        if(left >= right) break;
        swap(s + left, s + right);
        left++;
        right--;
    }
    return s;
}

void handleOutput(char *string){
    printf("Modified String : %s", string);
}

int main(){
    char *string = handleInput();
    char *result = reverseVowels(string);
    handleOutput(result);
    free(string);
    free(result);
    return 0;
}
/*
Used Testcase ->
1.  IceCreAm        ->      AceCreIm
2.  leetcode        ->      leotcede
*/