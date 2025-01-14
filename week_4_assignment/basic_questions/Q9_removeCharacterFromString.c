#include <stdio.h>
#include <stdlib.h>
#define MAX 500

char *handleInput(char *character){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter stirng : ");
    scanf("%[^\n]s", string);
    getchar();
    printf("Enter the character you want to remove : ");
    scanf("%c", character);
    return string;
}

void removeAllInstanceOfCharacter(char *string, char character){
    int i = 0;
    char *stringPtr = string;
    while(*stringPtr != '\0'){
        if(*stringPtr == character){
            stringPtr++;
            continue;
        }
        *(string + i) = *stringPtr;
        i++;
        stringPtr++;
    }
    *(string + i) = '\0';
}

void printOutput(char *character, char *string){
    printf("String after remove instance of '%c' : %s", *character, string);
}

int main(){
    char character;
    char *string = handleInput(&character);
    removeAllInstanceOfCharacter(string, character);
    printOutput(&character, string);
    free(string);
    return 0;
}

/*
Testcases which I used ->
No. String          Character           After remove character
1.  banana          a                   bnn
2.  hello world     l                   heo word
3.  abcdef          x                   abcdef
*/