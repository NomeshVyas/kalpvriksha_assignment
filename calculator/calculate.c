#include<stdio.h>
#include<string.h>

#define MAX 200

// utility functions
int precendence(char op){
    if(op == '+' || op == '-') return 0;
    if(op == '*' || op == '/') return 1;
}

int isOp(char op){
    return op == '+' || op == '-' || op == '*' || op == '/';
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
    // here top1 is for values, and top2 is for operations
    int top1 = -1, top2 = -1;
    
    int i = 0;
    while(exp[i] != '\0'){
        if(exp[i] == ' ' || exp[i] == '\n'){  // for space
            i++;
        } else if('0' <= exp[i] && exp[i] <= '9'){  // for number
            int num = exp[i++] - '0';
            
            while('0' <= exp[i] && exp[i] <= '9')
                num = num * 10 + (exp[i++] - '0');

            values[++top1] = num;
        } else if(isOp(exp[i])){    // for operator
            if(exp[i + 1] == '\0' || exp[i + 1] == '\n' || isOp(exp[i + 1] || (isOp(exp[i - 1]) && exp[i - 1] != '-'))){   // if 2 operators come 1 by 1 then we will send errCode 2
                *errCode = 2;
                return 0;
            }
            if(i - 1 < 0 && exp[i] == '-' && exp[i + 1] >= '0' && exp[i + 1] <= '9'){
                values[++top1] = -(exp[i + 1] - '0');
                i += 2;
                continue;
            }

            while(top2 >= 0 && precendence(operations[top2]) >= precendence(exp[i])){
                char op = operations[top2--];
                int b = values[top1--];
                int a = values[top1];
                int val = oprationVal(op, a, b, errCode);
                values[top1] = val;
            }
            operations[++top2] = exp[i++];
        } else {
            *errCode = 2;
            return 0;
        }
    }

    while(top2 >= 0){
        char op = operations[top2--];
        int b = values[top1--];
        int a = values[top1];

        int val = oprationVal(op, a, b, errCode);
        values[top1] = val;
    }

    return values[top1];
}

int main(){
    char exp[MAX];
    char * ptr = exp;
    int errCode = 0;    // here we will use errCode 1 for divided by 0, and errCode 2 for invalid expression

    // taking the exp as input
    printf("Your Expression Calculator is here now...\n");
    printf("Enter a valid expression for compute : \n");
    fgets(exp, MAX, stdin);
    
    if(exp[0] == '\0' || exp[0] == '\n'){   // in case of user didn't gave any input
        printf("Error: Invalid expression.");
        return 0;
    }

    int ans = calculate(exp, &errCode);

    if(errCode == 1)
        printf("Error: Division by zero.");
    else if(errCode == 2)
        printf("Error: Invalid expression.");
    else
        printf("%d", ans);

    return 0;
}