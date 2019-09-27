#include <stdio.h>
#include <stdlib.h>

int is_prime(int num);

int main(){
    int x, y;
    printf("Input two numbers: ");
    scanf("%d %d",&x,&y);
    printf("%d %d\n",x,y);
    //print_semiprimes(x,y);
    printf("%d\n",is_prime(x)); //debugg test for is_prime
    return 0;
}

// int print_semiprimes(int a, int b){
//     for (int n=a; n<=b; n++)
//     {
//         for (int k = 2; n <= n-1; k++)
//         {
            

//         }

//     }
// }


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