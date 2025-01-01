#include<stdio.h>

int validate(long number){
    return number > 0;
}

void takeInput(long *base, long *exponent, long *modulus){
    printf("Enter 3 positive numbers to evaluate given expression :  B^N %% M\n");
    printf("(Note : here ^ denotes Power sign and %% is for Modulo Operator)\n");
    int firsttime = 1;          // It will used to show warning for invalid input

    do {
        if(!firsttime) printf("\nEnter a valid value for Base greater than 0"); 
        printf("\nBase number (B) : ");
        scanf("%ld", base);
        firsttime = 0;
    } while (!validate(*base));

    firsttime = 1;
    do {
        if(!firsttime) printf("\nEnter a valid value for Exponent greater or equal than 0"); 
        printf("\nExponent number (N) : ");
        scanf("%ld", exponent);
        firsttime = 0;
    } while (!validate(*exponent) && *exponent != 0);
    
    firsttime = 1;
    do {
        if(!firsttime) printf("\nEnter a valid value for Modulus greater than 0"); 
        printf("\nModulus number (M) : ");
        scanf("%ld", modulus);
        firsttime = 0;
    } while (!validate(*modulus));
    
}

void printOutput(long base, long exponent, long modulus, long result){
    printf("\nResult of expression :\n");
    printf("%ld ^ %ld %% %ld = %ld", base, exponent, modulus, result);
}

long computeModulo(long base, long exponent, long modulus){
    long result = 1;
    while(exponent > 0){
        if(exponent & 1)
            result = (result % modulus * base % modulus) % modulus;
        
        base = (base % modulus * base % modulus) % modulus;
        exponent /= 2;
    }

    return result;
}

void handleModuloExpression(){
    long base, exponent, modulus, result;
    takeInput(&base, &exponent, &modulus);
    result = computeModulo(base, exponent, modulus);
    printOutput(base, exponent, modulus, result);
}

int main(){
    handleModuloExpression();

    return 0;
}

// Used TestCase :-
// 1.   7 ^ 4 % 9 = 7
// 2.   3 ^ 50 % 13 = 9
// 3.   12 ^ 6 % 4 = 0
// 4.   2 ^ 300 % 9 = 1
// 5.   5 ^ 20 % 2 = 1
// 6.   987654 ^ 12345 % 6789 = 1389
// 7.   3 ^ 10 % 100 = 49
// 8.   98765 ^ 4321 % 123 = 119
// 9.   1000 ^ 1000 % 100 = 0
// 10.  25 ^ 0 % 7 = 1