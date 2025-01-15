#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void handleInput(char *string, char *subString){
    printf("Enter string : ");
    scanf("%[^\n]s", string);
    getchar();
    printf("Enter substring : ");
    scanf("%[^\n]s", subString);
    getchar();
}

int findLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

int checkOccurence(char*string, char *subString, int i){
    while(*(string + i) != '\0' && *subString != '\0'){
        if(*(string + i) != *subString) return -1;
        subString++;
        i++;
    }
    return (*subString == '\0') ? 1 : -1;
}

int findIndexOfsubstring(char *string, char *subString){
    int index = -1;
    int len = findLength(string);
    
    for(int i = 0; i < len; i++){
        if(checkOccurence(string, subString, i) != -1) index = i;
        if(index != -1) break;
    }
    return index;
}

void printOutput(int index){
    if(index == -1)
        printf("-1 (Not found)");
    else
        printf("first occurence at : %d", index);
}

void findSubstringInString(){
    char *string = (char *) malloc(MAX * sizeof(char));
    char *subString = (char *) malloc(MAX * sizeof(char));
    handleInput(string, subString);
    int index = findIndexOfsubstring(string, subString);
    printOutput(index);
    free(string);
    free(subString);
}

int main(){
    findSubstringInString();

    return 0;
}
/*
Testcases which I used ->
No. String                  Substring               Index
1.  The quick brown fox     brown                   10
2.  Hello World             World                   6
3.  programming             gram                    3
4.  abcdef                  xyz                     -1
5.  qaz wsx edc rfv tgb      wsx                    3
7.  01 23 45 67 89          7 8                     10
*/