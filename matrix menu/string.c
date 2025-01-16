#include <stdio.h>
#include <stdlib.h>
#define MAX 101
#define LETTERS 26

int stringLength(char *str){
    int len = 0;
    while(*str){
        len++;
        str++;
    }
    return len;
}

char *handleInput(int *shift){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter string : ");
    scanf("%100[^\n]%*c", string);
    printf("Enter shift key : ");
    scanf("%d", shift);
    if(*shift < 0){
        printf("invalid shift value.");
        exit(0);
    }
    *shift %= LETTERS;
    return string;
}

int isLowercase(char c){
    return c >= 'a' && c <= 'z';
}

int isPrime(int n){
    if(n < 2) return 0;
    if(n == 2) return 1;
    for(int i = n - 1; i >= 2; i--)
        if(n % i == 0) return 0;
    return 1;
}

char addValue(char c, int shift){
    if(c + shift <= 'z'){
        return c + shift;
    } else {
        char temp = (c + shift) % 'z' - 1;
        return 'a' + temp;
    }
}

void encrypt(char *string, int len, int shift){
    for(int i = 0; i < len; i++)
        if(isLowercase(*(string + i)) && isPrime(i))
            *(string + i) = addValue(*(string + i), shift);
}

int main(){
    int shift;
    char *string = handleInput(&shift);
    int len = stringLength(string);
    encrypt(string, len, shift);
    printf("%s", string);
    return 0;
}