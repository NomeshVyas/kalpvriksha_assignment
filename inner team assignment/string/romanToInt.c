// Leetcode 13
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Roman Number : ");
    scanf("%s", string);
    return string;
}

int precedence(char c){
    switch(c){
        case 'I': return 1;
        case 'V': return 2;
        case 'X': return 3;
        case 'L': return 4;
        case 'C': return 5;
        case 'D': return 6;
        case 'M': return 7;
        default : return 0;
    }
}

int charToNumber(char c){
    switch(c){
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default : return 0;
    }
}

int RomanToInteger(char *roman){
    int number = 0, temp;
    while(*roman){
        if(precedence(*roman) < precedence(*(roman + 1)))
            temp = - charToNumber(*roman);
        else
            temp = charToNumber(*roman);
        number += temp;
        roman++;
    }
    return number;
}

void handleOutput(int number){
    printf("Decimal Representation : %d", number);
}

int main(){
    char *roman = handleInput();
    int number = RomanToInteger(roman);
    handleOutput(number);
    return 0;
}
/*
Used Testcase ->
1. LVIII            58
2. MCMXCIV          1994
3. III              3
*/