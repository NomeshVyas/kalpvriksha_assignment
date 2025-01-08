#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#define MAX 50
#define FALSE 0
#define TRUE 1

int isNum(char num){
    return num >= '0' && num <= '9';
}

int charToInt(char c){
    return c - '0';
}

int check_overflow(int num1, int num2, int minus){
    int flag1 = num1 > (INT_MAX - num2) / 10;
    if(!minus) return flag1;

    int flag2 = - num1 < (INT_MIN + num2) / 10;   
    return flag1 && flag2;    
}

int myAtoi(char* s) {
    int minus = FALSE;
    int sign = FALSE;
    int num = 0;
    int temp;

    while(*s == ' ') s++;

    switch(*s){
        case '-':
            minus = TRUE;
        case '+':
            sign = TRUE;
            s++;
    }
    
    while(*s != '\0'){
        if (isNum(*s)) {
            temp = charToInt(*s);
            if(check_overflow(num, temp, minus))
                return minus ? INT_MIN : INT_MAX;
            num = 10 * num + temp;
            s++;
        } else {
            break;
        }
    }

    if(minus) num *= -1;

    return num;
}

void handleInput(char *string){
    printf("Enter a number string : ");
    scanf("%[^\n]s", string);
    fflush(stdin);
}

void handleOutput(int num){
    printf("\nInteger of given string : %d", num);
}

void asciToInteger(){
    char *string = (char *)malloc(MAX * sizeof(char));
    handleInput(string);
    int number = myAtoi(string);
    handleOutput(number);
}

int main(){
    asciToInteger();
    return 0;
}

// for pull req