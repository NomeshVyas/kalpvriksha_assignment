#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_LEN 500
#define A_TO_Z 26

int findLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

char *handleInput(){
    char *string = (char *) malloc(MAX_STR_LEN * sizeof(char));
    printf("Enter string : ");
    scanf("%[^\n]s", string);
    return string;
}

int charToIndex(char c){
    return c - 'a';
}

void reverse(char *start, char *end){
    while(start < end){
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char * addFrequenceInCompressedString(char *compressedString, int number){
    char *start = compressedString;
    while(number){
        int mod = number % 10;
        *start = mod + '0';
        start++;
        number /= 10;
    }
    reverse(compressedString, start - 1);
    return start;
}



char *generateCompressedString(char *string){
    char *compressed = (char *) malloc(MAX_STR_LEN * sizeof(char));
    int *freq = (int *) calloc(A_TO_Z, sizeof(int));
    int len = findLength(string);
    for(int i = 0; i < len; i++)
        *(freq + charToIndex(*(string + i))) += 1;

    char *compressedStringPtr = compressed;
    for(int i = 0; i < A_TO_Z; i++){
        if(*(freq + i) > 0){
            *compressedStringPtr = 'a' + i;
            compressedStringPtr = addFrequenceInCompressedString(compressedStringPtr + 1, *(freq + i));
        }
    }
    *compressedStringPtr = '\0';
    free(freq);
    return len >= findLength(compressed) ? compressed : string;
}

void printOutput(char *string){
    printf("Compressed String : %s", string);
}

int main(){
    char *string = handleInput();
    char *compressedString = generateCompressedString(string);
    printOutput(compressedString);
    free(string);
    free(compressedString);
    return 0;
}

/*
Testcases which I used ->
No.     String                      Compressed
1.      aaabbc                      a3b2c1
2.      abcd                        abcd
3.      aabbcc                      a2b2c2
4.      abcabcabc                   a3b3c3
5.      a                           a
6.      aaaaaaaaaaaaabbbbbaaaaa     a18b5
*/