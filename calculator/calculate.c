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

void removeSpaces(char exp[]){
    int k = 0, i = 0;
    while(exp[i] != '\0' && exp[i] != '\n'){
        if(exp[i] != ' ')
            exp[k++] = exp[i];
        i++;
    }
    exp[k] = '\0';
}

// calculator main function
int calculate(char exp[], int* errCode){
    int values[MAX];
    char operations[MAX];
    // here top1 is for values, and top2 is for operations
    int top1 = -1, top2 = -1;
    
    int i = 0;
    while(exp[i] != '\0'){
        if('0' <= exp[i] && exp[i] <= '9'){  // for number
            int val = exp[i++] - '0';
            
            while('0' <= exp[i] && exp[i] <= '9')
                val = val * 10 + (exp[i++] - '0');

            values[++top1] = val;
        } else if(isOp(exp[i])){    // for operator
            if(exp[i + 1] == '\0' || exp[i + 1] == '\n' || isOp(exp[i + 1])){   // if 2 operators come 1 by 1 then we will send errCode 2
                *errCode = 2;
                return 0;
            }
            if(i == 0 && exp[i] == '-' && exp[i + 1] >= '0' && exp[i + 1] <= '9'){  // if the first value is a minus value
                i++;
                int val = exp[i++] - '0';

                while('0' <= exp[i] && exp[i] <= '9')
                    val = val * 10 + (exp[i++] - '0');
                
                values[++top1] = -val;
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

    removeSpaces(exp);
    int ans = calculate(exp, &errCode);

    if(errCode == 1)
        printf("Error: Division by zero.");
    else if(errCode == 2)
        printf("Error: Invalid expression.");
    else
        printf("%d", ans);

    return 0;
}

/* 
Testcases which I used are ->

1. 10 - 15                          = -5
2. 12345 + 67890 - 54321            = 25914
3.    7    +  3    *    2           = 13
4. 5 + x - 2                        = Error: Invalid expression.
5. 10 / 0 + 5                       = Error: Division by zero.
6. 25 / 5 + 5 * 2 * 2 - 4 / 2 - 10  = 13
7. 10 + 2 * 3                       = 16
8. 5 ++ 6 * 2                       = Error: Invalid expression
9. - 10 + 5                         = -5
10. -20 + 5 * 10 / 5                = -10
*/