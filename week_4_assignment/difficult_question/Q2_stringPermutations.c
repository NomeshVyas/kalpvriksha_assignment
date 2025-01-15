#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int getStringLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

int findFactorial(int number){
    int factorial = 1;
    for(int i = 1; i <= number; i++)
        factorial *= i;
    return factorial;
}

void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter String : ");
    scanf("%[^\n]%*c", string);
    return string;
}

char *stringCopy(char *string, int length){
    char *copy = (char *) malloc((length + 1) * sizeof(char));
    char *copyPtr = copy;
    while(*string){
        *copyPtr = *string;
        string++;
        copyPtr++;
    }
    *copyPtr = '\0';
    return copy;
}

void backtrack(char **permutations, int *permutationsIndex, int idx, char *string, int stringLength){
    if(idx == stringLength){
        char *permutation = stringCopy(string, stringLength);
        *(permutations + *permutationsIndex) = permutation;
        *permutationsIndex += 1;
        return;
    }

    for(int i = idx; i < stringLength; i++){
        swap(string + idx, string + i);
        backtrack(permutations, permutationsIndex, idx + 1, string, stringLength);
        swap(string + idx, string + i);
    }
}

char **generateAllPermutations(char *string, int len, int numberOfPermutations){
    char **permutations = (char **) malloc(numberOfPermutations * sizeof(char *));
    int *permutationsIndex = (int *) malloc(sizeof(int));
    *permutationsIndex = 0;
    backtrack(permutations, permutationsIndex, 0, string, len);
    return permutations;
}

void handleOutput(char **permutations, int numberOfPermutations){
    printf("All Possible Prmutations ->\n[");
    int first = 1;
    for(int i = 0; i < numberOfPermutations; i++){
        printf(first ? "[\"%s\"]" : ",[\"%s\"]", *(permutations + i));
        first = 0;
    }
    printf("]");
}

int main(){
    char *string = handleInput();
    int length = getStringLength(string);
    int numberOfPermutations = findFactorial(length);
    char **permutations = generateAllPermutations(string, length, numberOfPermutations);
    handleOutput(permutations, numberOfPermutations);
    
    for(int i = 0; i < numberOfPermutations; i++)
        free(*(permutations + i));
    free(permutations);
    free(string);
    return 0;
}
/*
Testcases which I used ->
No. String                  Permutations
1.  abc                     [["abc"],["acb"],["bac"],["bca"],["cba"],["cab"]]
2.  ab                      [["ab"],["ba"]]
3.  a                       [["a"]]
4.  1234                    [["1234"],["1243"],["1324"],["1342"],["1432"],["1423"],["2134"],["2143"],["2314"],["2341"],["2431"],["2413"],["3214"],["3241"],["3124"],["3142"],["3412"],["3421"],["4231"],["4213"],["4321"],["4312"],["4132"],["4123"]] 
*/