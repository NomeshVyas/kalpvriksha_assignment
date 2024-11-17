#include<stdio.h>
#include<string.h>

#define MAX 100

int calculate(char exp[]){

    return 0;
}

int main(){
    char expression[MAX];
    char * ptr = expression;

    // taking the expression as input
    fgets(expression, MAX, stdin);
    
    // removing whitespace
    int k = 0;
    while(*ptr != '\0'){
        if(*ptr != ' ')
            expression[k++] = *ptr;
        ptr++;
    }
    expression[k] = '\0';

    return 0;
}