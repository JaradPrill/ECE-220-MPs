#include <stdio.h>
#include <stdlib.h>

int is_prime(int num);
int print_semiprimes(int a, int b);

int main(){
    int a, b;
    printf("Input two numbers: ");
    scanf("%d %d", &a, &b);
    if( a <= 0 || b <= 0 ){
        printf("Inputs should be positive integers\n");
        return 1;
    }
    
    if( a > b ){
        printf("The first number should be smaller than or equal to the second number\n");
        return 1;
    }

    // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
    print_semiprimes(a,b);
    //printf("%d\n",is_prime(x)); //debugg test for is_prime
    return 0;
}

/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
 int print_semiprimes(int a, int b){
     for (int i=a; i<=b; i++)
     {
         for (int j = 2; j <= i-1; j++)
         {
            int j_prime = is_prime(j); //check if j is a prime number
            int ij_prime = 0; //
            if (i % j==0) //check if j is a factor of i
            {
                int ij = (i/j);
                ij_prime = is_prime(ij);
            }
            
            if (j_prime==1 && ij_prime==1) //checks if i and j and i/j are primes
            {
                printf("%d ", i); //print i if both j and i/j are primes
                break;
            }
         }

     }
     return 0;
 }


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int num){
    int bool=0;
    for (int i = 2; i <= num-1; i++)
    {
        if (num % i == 0) //if no remainder then num has a factor other than 1 and itself
        {
            bool = 1;
            break;
        }
    }
    if (bool == 1)
        return 0;
    return 1;
}
