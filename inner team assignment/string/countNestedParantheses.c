// Leetcode 1614
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter String : ");
    scanf("%[^\n]%*c", string);
    return string;
}

int maxDepth(char* s) {
    int count = 0, max = 0;
    while(*s){
        if(*s == '('){
            count++;
            max = max > count ? max : count;
        } else if(*s == ')'){
            count--;
        }
        s++;
    }
    return max;
}

void handleOutput(int number){
    printf("Count of nested parantheses : %d", number);
}

int main(){
    char *string = handleInput();
    int count = maxDepth(string);
    return 0;
}