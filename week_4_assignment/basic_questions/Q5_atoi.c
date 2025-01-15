#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 25

int stirngLength(char *string){
    int len = 0; 
    while (*string != '\0'){
        string++;
        len++;
    }
    return len;
}

int isNegetive(char c){
    return c == '-';
}

int isDigit(char c){
    return c >= '0' && c <= '9';
}

int charToInt(char num){
    return num - '0';
}

int checkOverflow(unsigned int num, int add){
    return num > (INT_MAX - add) / 10;
}

int checkUnderflow(unsigned int num, int add){
    return -num < (INT_MIN + add) / 10;
}

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter string number : ");
    scanf("%[^\n]s", string);
    return string;
}

int myAtoi(char *stringNumber){
    unsigned int number = 0;
    int negetive = 0;
    while(*stringNumber == ' ') stringNumber++;

    if(isNegetive(*stringNumber)){
        negetive = 1;
        stringNumber++;
    }
    while(*stringNumber != '\0'){
        if(!isDigit(*stringNumber)) break;
        int digit = charToInt(*stringNumber);
        if(negetive && checkUnderflow(number, digit) && checkOverflow(number, digit))
            return INT_MIN;
        if(!negetive && checkOverflow(number, digit))
            return INT_MAX;
        number = number * 10 + digit;
        stringNumber++;
    }
    number = negetive ? -1 * number : number;
    return number;
}

void printOutput(int number){
    printf("Number in integer format : %d", number);
}

int main(){
    char *stringNumber = handleInput();
    int number = myAtoi(stringNumber);
    printOutput(number);
    free(stringNumber);
    return 0;
}

/*
Testcases which I used ->
1.  String          ->          Number
2.  1234            ->          1234
3.  -567            ->          -567
4.  abc123          ->          0
5.  00000-42a1234   ->          0
6.  004500          ->          4500
7.  -2147483648     ->          -2147483648
8.  2147483648      ->          2147483647 (INT_MAX)  // in case of overflow
9.  -2147483700     ->          -2147483648 (INT_MIN) // in case of underflow
10. 1234cgfd543     ->          1234
*/