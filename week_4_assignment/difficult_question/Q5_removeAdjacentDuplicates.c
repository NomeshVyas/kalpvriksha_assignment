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

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter String : ");
    scanf("%[^\n]s", string);
    return string;
}

void removeAdjacentDuplicates(char *string){
    int len = stringLength(string);
    char *stack = (char *) malloc(len * sizeof(char));
    int top = -1;
    char *stringPtr = string;
    while(*stringPtr){
        *(stack + ++top) = *stringPtr;
        while(top > 0 && *(stack + top) == *(stack + top - 1)) top -= 2;
        stringPtr++;
    }
    *(string + top + 1) = '\0';
    while(top >= 0){
        *(string + top) = *(stack + top);
        top--;
    }
    free(stack);
}

void handleOutput(char *string){
    printf("After removing adjacent characters : %s", string);
}

int main(){
    char *string = handleInput();
    removeAdjacentDuplicates(string);
    handleOutput(string);
    free(string);
    return 0;
}

/*
Testcases which I used ->
No. String                  After removing adjacent duplicates
1.  aaabccddd               abd
2.  abbaca                  ca
3.  aabbcc                  (blank)
4.  azxxzy                  ay
5.  abbbabaaa               ababa
*/