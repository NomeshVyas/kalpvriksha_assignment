#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define ASCII_LEN 256 

int getStringLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

int *generateAndSetMapValues(char *characters){
    int *map = (int *) calloc(ASCII_LEN, sizeof(int));
    while(*characters){
        *(map + *characters) += 1;
        characters++;
    }
    return map;
}

char *createSubstring(char *source, int start, int length){
    char *subString = (char *) malloc((length + 1) * sizeof(char));
    for(int i = 0; i < length; i++)
        *(subString + i) = *(source + start + i);
    *(subString + length) = '\0';
    return subString;
}

char *handleInput(char *prompt){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter %s string : ", prompt);
    scanf("%[^\n]%*C", string);
    return string;
}

char *findSmallestWindowSubstring(char *string, char *characters){
    int length = getStringLength(string);
    if(length < getStringLength(characters)) return "\0";
    int *map = generateAndSetMapValues(characters);
    int numberOfCharacters = getStringLength(characters);
    int left = 0, right = 0, count = 0;
    int start = -1, minLength = MAX;

    while(*(string + right)){
        if(*(map + *(string + right)) > 0) count++;
        *(map + *(string + right)) -= 1;
        while(count == numberOfCharacters){
            if(right - left + 1 < minLength){
                minLength = right - left + 1;
                start = left;
            }
            *(map + *(string + left)) += 1;
            if(*(map + *(string + left)) > 0) count--; 
            left++;
        }
        right++;
    }
    free(map);
    if(minLength == length) return string;
    if(start == -1) return "\0";
    char *substirng = createSubstring(string, start, minLength);
    return substirng;
}

void handleOutput(char *string){
    printf("Substring : %s", string);
}

int main(){
    char *string = handleInput("Main");
    char *characters = handleInput("Character");
    char *substring = findSmallestWindowSubstring(string, characters);
    handleOutput(substring);
    free(substring);
    free(characters);
    free(string);
    return 0;
}
/*
Testcases which I used ->
No. String                      Characters          Substring
1.  ADOBECODEBANC               ABC                 BANC
2.  this is a test string       tist                t stri
3.  ADOBECODEBANC               ABCA                ADOBECODEBA
4.  geeksforgeeks               ork                 ksfor
5.  a                           b                   "\0"
6.  Nomesh                      NomeshVyas          "\0"
*/