#include<stdio.h>
#include<string.h>

#define MAX 200

// utility functions
void printArr(int val[], int top){
    while(top > - 1)
        printf(" %d ", val[top--]);
}

int precendence(char op){
    if(op == '+' || op == '-') return 0;
    if(op == '*' || op == '/') return 1;
}

int oprationVal(char op, int a, int b, int* errCode){
    switch (op){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if(b == 0){
                *errCode = 1;
                return 0;
            }
            return a / b;
    }
}

// calculator main function
int calculate(char exp[], int* errCode){
    int values[MAX];
    char operations[MAX];
    // here top1 is for val, and top2 is for op
    int top1 = -1, top2 = -1;
    
    int i = 0;
    while(exp[i] != '\0'){
        if('0' <= exp[i] && exp[i] <= '9'){
            int num = exp[i++] - '0';
            
            while('0' <= exp[i] && exp[i] <= '9')
                num = num * 10 + (exp[i++] - '0');

            values[++top1] = num;
        } else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'){
            while(top2 >= 0 && precendence(operations[top2]) >= precendence(exp[i])){
                char op = operations[top2--];
                int a = values[top1--];
                int b = values[top1];

                int num = oprationVal(op, a, b, errCode);
                values[top1] = num;
            }
            operations[++top2] = exp[i];
            i++;
        } else {
            *errCode = 2;
            return 0;
        }
    }

    while(top2 >= 0){
        char op = operations[top2--];
        int b = values[top1--];
        int a = values[top1];

        int num = oprationVal(op, b, a, errCode);
        values[top1] = num;
    }

    return values[top1];
}

int main(){
    char exp[] = "15+5*2-14/2";
    char * ptr = exp;
    int errCode = 0;

    // taking the exp as input
    // fgets(exp, MAX, stdin);
    
    // removing whitespace
    int k = 0;
    while(*ptr != '\0'){
        if(*ptr != ' ')
            exp[k++] = *ptr;
        ptr++;
    }
    exp[k] = '\0';
    printf("%s", exp);
    int ans = calculate(exp, &errCode);
    printf("%d\n", errCode);

    if(errCode == 1)
        printf("Error: Division by zero.");
    else if(errCode == 2)
        printf("Error: Invalid expression.");
    else
        printf("%d", ans);

    return 0;
}