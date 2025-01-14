#include <stdio.h>
#include <stdlib.h>
#define MAX 200
#define ASCI_RANGE 256

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter a string to remove duplicates : ");
    scanf("%[^\n]s", string);
    return string;
}

char * generateNonDuplicateString(char *string){
    int *mark = (int *) calloc(ASCI_RANGE, sizeof(int));
    char *resultString = (char *) malloc(MAX * sizeof(char));
    char *resultPtr = resultString;
    while(*string != '\0'){
        if(!*(mark + *string - 1)){
            *resultPtr = *string;
            resultPtr++;
            *(mark + *string - 1) = 1;
        }
        string++;
    }
    *resultPtr = '\0';
    free(mark);
    return resultString;
}

void hanldeOutput(char *string){
    printf("\nResult String : %s", string);
}

void hanldeRemoveDuplicateCharacters(){
    char *string = handleInput();
    char *stringWithoutDuplicates = generateNonDuplicateString(string);
    hanldeOutput(stringWithoutDuplicates);
    free(string);
}

int main(){
    hanldeRemoveDuplicateCharacters();

    return 0;
}
/*
Testcases which I used ->
1.  programming         ->      progamin
2.  banana              ->      ban
3.  abacabad            ->      abcd
*/