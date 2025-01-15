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

void handleInput(char *string1, char *string2){
    printf("Enter first stirng : ");
    scanf("%[^\n]s", string1);
    getchar();
    printf("Enter second stirng : ");
    scanf("%[^\n]s", string2);
    getchar();
}

char *createRepeatedString(char *string, int len){
    char *repeatedString = (char *) malloc(2 * len * sizeof(char));
    char *repeatedStringPtr = repeatedString;
    for(int iterate = 0; iterate < 2; iterate++){
        int i = 0;
        while(*(string + i) != '\0'){
            *repeatedStringPtr = *(string + i);
            repeatedStringPtr++;
            i++;
        }
    }
    *repeatedStringPtr = '\0';
    return repeatedString;
}

int checkOccurence(char *string, char *substring){
    while(*string != '\0' && *substring != '\0'){
        if(*string != *substring) return -1;
        string++;
        substring++;
    }
    return *substring != '\0' ? -1 : 1; 
}

int checkRotatedOrNot(char *string1, char *string2){
    int len = stringLength(string1);
    if(len != stringLength(string2)) return 0;
    char *repeatedString = createRepeatedString(string1, len);
    int find = -1;
    
    for(int i = 0; i < len; i++){
        find = checkOccurence(repeatedString + i, string2);
        if(find != -1) break;
    }

    return find != -1;
}

void printOutput(int rotation){
    if(rotation == 1)
        printf("true");
    else
        printf("false");
}

int main(){
    char *string1 = (char *) malloc(MAX * sizeof(char));
    char *string2 = (char *) malloc(MAX * sizeof(char));
    handleInput(string1, string2);
    int isRotated = checkRotatedOrNot(string1, string2);
    printOutput(isRotated);
    free(string1);
    free(string2);
    return 0;
}

/*
Used Testcase ->
No.     String1         String2         Output
1.      hello world     rldhello wo     true
2.      abcd            dabc            true
3.      rotation        ationrot        true
4.      hello           world           false
5.      NomeshVyas      VyasNomesh      true   
6.      waterbottle     erbottlewat     true
7.      hello           lohel           true
8.      abc             cab             true
*/