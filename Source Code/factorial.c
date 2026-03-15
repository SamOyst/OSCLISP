//Created by Sam Oystreck A00478278
#include <stdio.h>

//Is responsible for actually doing the factorial calculation
//Calculation is done itteratively through multiplication
int factorialCalc(int n){
    int result = 1;
    for(int i = 1; i <= n; i++){
        result *= i;
    }
    return(result);
}

//Main method serves only to streamline execution of the program
int main(){
    printf("Please input an integer to take the factorial of:\n");
    int input;

    //Ensures proper input as per guidelines
    if((scanf("%d", &input)) == 1){
        printf("Now calculating %d!\n", input);
        printf("Process complete: %d! = %d\n", input, factorialCalc(input));
    } else {
        printf("Invalid input.\nTerminating...\n");
    }
}