#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_LEN 500
#define ASCI_LENGTH 256

int stringLength(char *string){
    int len = 0;
    while(*string != '\0'){
        len++;
        string++;
    }
    return len;
}

void handleInput(char *string1, char *string2){
    printf("Enter first String : ");
    scanf("%[^\n]s", string1);
    getchar();
    printf("Enter second String : ");
    scanf("%[^\n]s", string2);
    getchar();
}

int checkAnagram(char *string1, char *string2){
    int *freq = (int *) calloc(ASCI_LENGTH, sizeof(int));
    int len = stringLength(string1);
    if(len != stringLength(string2)) return 0;

    for(int i = 0; i < len; i++)
        *(freq + *(string1 + i)) += 1;
    for(int i = 0; i < len; i++)
        *(freq + *(string2 + i)) -= 1;
    
    for(int i = 0; i < ASCI_LENGTH; i++)
        if(*(freq + i) != 0) return 0;
    return 1; 
}

void handleOutput(int number){
    if(number)
        printf("true");
    else
        printf("false");
}

int main(){
    char *string1 = (char *)malloc(MAX_STR_LEN * sizeof(char));
    char *string2 = (char *)malloc(MAX_STR_LEN * sizeof(char));
    handleInput(string1, string2);
    int isAnagram = checkAnagram(string1, string2);
    handleOutput(isAnagram);
    free(string1);
    free(string2);
}

/*
Testcases which I used
No.     String1         String2         Output
1.      listen          silent          true
2.      triange         integral        true
3.      apple           pale            false
4.      Nomesh123       No1me2sh3       true
5.      123456789       987654321       true
6.      Nomesh          nomesh          false
7.      InTimeTec       TecInTime       true
*/