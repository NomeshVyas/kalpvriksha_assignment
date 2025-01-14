#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int stringLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

void stringCopy(char *sourceStart, char *sourceEnd, char *target){
    while(sourceStart < sourceEnd){
        *target = *sourceStart;
        target++;
        sourceStart++;
    }
    *target = '\0';
}

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter String : ");
    scanf("%[^\n]s", string);
    return string;
}

void checkForPalindrome(char *string, int low, int high, int len, int *longestPalindromeLen, int *palindromeStart){
    while(*(string + low) == *(string + high)){
        low--;
        high++;
        if(low == -1 || high == len) break;
    }
    if(high - (low + 1) > *longestPalindromeLen){
        *palindromeStart = low + 1;
        *longestPalindromeLen = high - (low + 1);
    }
}

char *findLongestPalindromicSubstring(char *string){
    int len = stringLength(string);
    char *longestPalindrome = (char *) malloc((len + 1) * sizeof(char));
    int palindromeLen = 0, palindromeStart = 0;

    for(int i = 0; i < len; i++){
        checkForPalindrome(string, i, i, len, &palindromeLen, &palindromeStart);    // for odd length palindrome
        checkForPalindrome(string, i - 1, i, len, &palindromeLen, &palindromeStart);    // for even string
    }
    stringCopy(string + palindromeStart, string + palindromeStart + palindromeLen, longestPalindrome);
    return longestPalindrome;
}

void handleOutput(char *string){
    printf("Longest Substring : %s", string);
}

int main(){
    char *string = handleInput();
    char *longestPalindrome = findLongestPalindromicSubstring(string);
    handleOutput(longestPalindrome);
    free(longestPalindrome);
    free(string);
    return 0;
}

/*
Testcases which I used ->
No. String                      Longest Palindrome
1.  babad                       bab
2.  cbbd                        bb
3.  a                           a
4.  forgeeksskeegfor            geeksskeeg
5.  aacabdkacaa                 aca
*/