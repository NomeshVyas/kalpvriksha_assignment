// Leetcode 205
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 1000
#define ASCI_LEN 256

char *handleInput(){
    char *string = (char *) malloc(MAX * sizeof(char));
    printf("Enter String : ");
    scanf("%[^\n]%*c", string);
    return string;
}

bool find(char *map, char c){
    for(int i = 0; i < ASCI_LEN; i++)
        if(*(map + i) == c)
            return true;
    return false;
}

bool isIsomorphic(char* s, char* t) {
    int len = strlen(s);
    if(len != strlen(t)) return false;
    char *map = (char *) calloc(ASCI_LEN, sizeof(char));

    for(int i = 0; i < len; i++){
        if(*(map + *(s + i)) == '\0'){
            if(find(map, *(t + i))) return false;
            *(map + *(s + i)) = *(t + i);
        } else if(*(map + *(s + i)) == *(t + i)){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

void handleOutput(bool check){
    printf(check ? "(true) Both strings are isomorphic." : "(false) strings are not isomorphic");
}

int main(){
    char *string1 = handleInput();
    char *string2 = handleInput();
    bool check = isIsomorphic(string1, string2);
    handleOutput(check);
    return 0;
}
/*
Testcases which I used ->
1.  s = "egg",      t = "add",      output = true
2.  s = "foo",      t = "bar",      output = false
3.  s = "paper",    t = "title",    output = true
*/