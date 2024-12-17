#include<stdio.h>
#include<string.h>

#define MAX 200

// utility functions
int precendence(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char op){
    return op == '+' || op == '-' || op == '*' || op == '/';
}

int isNum(char n){
    return '0' <= n && '9' >= n;
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

void removeSpaces(char* exp){
    char* ptr = exp;
    while(*exp != '\0' && *exp != '\n'){
        if(*exp != ' '){
            *ptr = *exp;
            ptr++;
        }
        exp++;
    }
    *ptr = '\0';
}

// calculator's helping functions
char* handleNum(char* exp, int values[], int* top1){
    int val = 0;
    
    while(isNum(*exp)){
        val = val * 10 + (*exp - '0');
        exp++;
    }

    values[++*top1] = val;
    return exp;
}

char* handleOperator(char* exp, char operations[], int values[], int* top1, int* top2, int* errCode){
    if(*(exp + 1) == '\0' || *(exp + 1) == '\n' || isOperator(*(exp + 1))){   // if 2 operators come 1 by 1 then we will send errCode 2
        *errCode = 2;
        return exp;
    }

    while(*top2 >= 0 && precendence(operations[*top2]) >= precendence(*exp)){
        char op = operations[(*top2)--];
        int b = values[(*top1)--];
        int a = values[*top1];
        int val = oprationVal(op, a, b, errCode);
        if(*errCode) return exp;
        values[*top1] = val;
    }

    operations[++(*top2)] = *exp;
    exp++;
    return exp;
}

char* handleStartMinus(char* exp, int values[], int* top1, int* errCode){
    if(isOperator(*exp)){
        if(*exp == '-' && isNum(*(exp + 1))){           // if the first value is a minus value
            int val = 0;
            exp++;

            while(isNum(*exp)){
                val = val * 10 + (*exp - '0');
                exp++;
            }

            values[++*top1] = -val;
        } else {            // other operators will make our expression invalid
            *errCode = 2;
        }
    }
    return exp;
}

// calculator main function
int calculate(char* exp, int* errCode){
    int values[MAX];
    char operations[MAX];
    int top1 = -1, top2 = -1;       // here top1 is for values, and top2 is for operations

    exp = handleStartMinus(exp, values, &top1, errCode);
    if(*exp == '\0' || *exp == '\n' || *errCode){       // in case of blank expression
        *errCode = 2;
        return 0;
    }

    while(*exp != '\0'){
        if(isNum(*exp)){        // for number
            exp = handleNum(exp, values, &top1);
        } else if(isOperator(*exp)){    // for operator
            exp = handleOperator(exp, operations, values, &top1, &top2, errCode);
            if(*errCode) return 0;
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

void expressionPromt(char * exp){
    printf("Your Expression Calculator is here now...\n");
    printf("Enter a valid expression for compute : \n");
    fgets(exp, MAX, stdin);         // taking the exp as input
}

void printResult(int ans, int errCode){
    if(errCode == 1)
        printf("Error: Division by zero.");
    else if(errCode == 2)
        printf("Error: Invalid expression.");
    else
        printf("%d", ans);    
}

int main(){
    char exp[MAX];

    while(1)
    {
    int errCode = 0, ans = 0;    // here we will use errCode 1 for divided by 0, and errCode 2 for invalid expression
    expressionPromt(exp);
    removeSpaces(exp);
    ans = calculate(exp, &errCode);
    printResult(ans, errCode);
    }
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