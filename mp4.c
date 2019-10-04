/*
in this program we print out all the subprime numbers within a range given by the user input a,b.
This is accomplished using two functions: is_prime and print_semiprimes. is_prime tests if the 
input value is a prime number. This function is called exclusively in the print_semiprime function
print_semiprimes uses two iterative loops to loop through all numbers in the range [a,b] and 
check if that number is a semiprime. The function prints out all semi prime numbers inclusive to 
a range [a, b].

partners: jaradjp2, bozhaoj2, kamatar2
*/

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
     for (int i=a; i<=b; i++) //test all values in [a,b]
     {
         for (int j = 2; j <= i-1; j++)
         {
            int j_prime = is_prime(j); //check if j is a prime number
            int ij_prime = 0; //
            if (i % j==0) //check if j is a factor of i then check if i/j is a prime
            {
                int ij = (i/j);
                ij_prime = is_prime(ij); //checks if i/j is a prime
            }
            
            if (j_prime==1 && ij_prime==1) //checks if i and j and i/j are primes
            {
                printf("%d ", i); //print i if both j and i/j are primes
                break; //if i is found to be a semiprime, move on to next i to avoid double printing
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
    int bool=0; //initialize a boolean to tell if the number is a prime#
    for (int i = 2; i <= num-1; i++)
    {
        if (num % i == 0) // check for remainder value
        {
            bool = 1; // num has a factor other than 1 and itself if the remainder is 0
                      // set bool to 1
            break; // break out when a factor has been found
        }
    }
    if (bool == 1)
        return 0; // bool = 1 -> not a prime number
    return 1;
}
