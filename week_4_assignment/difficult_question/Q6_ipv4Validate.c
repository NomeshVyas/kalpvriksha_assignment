#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int isDigit(char c){
    return c >= '0' && c <= '9';
}

int isDot(char c){
    return c == '.';
}

int inRange(int num){
    return num <= 255;
}

int charToDigit(char c){
    return c - '0';
}

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter string : ");
    scanf("%[^\n]s", string);
    return string;
}

int validatedIPv4(char *string){
    if(!isDigit(*string)) return 0;
    int dotCount = 0, num = 0;

    if(isDigit(*(string + 1)) && *string == '0') return 0;
    num = charToDigit(*string);
    string++;

    while(*string){
        if(isDigit(*string)){
            num = num * 10 + charToDigit(*string);
            if(*string == '0' && isDot(*(string - 1)) && *(string + 1) != '\0' && !isDot(*(string + 1))) return 0;
            if(!inRange(num)) return 0;
        } else if(isDot(*string)){
            if(!isDigit(*(string + 1))) return 0;
            num = 0;
            dotCount++;
            if(dotCount > 3) return 0;
        } else {
            return 0;
        }
        string++;
    }
    return dotCount == 3;
}

void handleOutput(int isValid){
    if(isValid) printf("true");
    else printf("false");
}

int main(){
    char *string = handleInput();
    int isValid = validatedIPv4(string);
    handleOutput(isValid);
    free(string);
    return 0;
}
/*
Testcases which I used ->
No. IPv4                isValidate
1.  255.254.10.256      false
2.  126.136.22*12       false
3.  .12.12.12           false
4.  12.12.12.12.12      false
5.  00.0.0.0            false
6.  0.0..0              false
7.  0.0.0.0             true
8.  255.255.255.255     true
9.  256.257.258.259     false
10. 12. 44. 32. 43      false
*/