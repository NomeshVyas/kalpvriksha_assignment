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
    int checkAgain = 0;
    char *left = string;
    char *right = string;
    while(*right != '\0'){
        if(*(right + 1) != '\0' && *right == *(right + 1)){
            checkAgain = 1;
            right += 2;
            continue;
        }
        *left = *right;
        right++;
        left++;
    }
    *left = '\0';
    if(checkAgain) removeDuplicates(string);
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
