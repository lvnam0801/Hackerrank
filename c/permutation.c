// program to generate permutation of n
#include <stdio.h>

// function prototype
void permutationOfN(int n, int Arr[]);
int factorial(int n);

// main program
int main(){
    int Arr[5] = {1, 2, 3, 4, 5};
    permutationOfN(5, Arr);
    return 0;
}

// function definition
void permutationOfN(int n, int Arr[]){
    // number permutation of the array that has n elements
    int numPermOfArr = factorial(n), m, k, temp;
    for (size_t i = 0; i < numPermOfArr; i++){
        // print current configuaration
        for (size_t j = 0; j < n; j++)
            printf("%d ", Arr[j]);
        printf("\n");
        // generate the next configuaration
        m = n - 1;
        // find index of element smallest that bigger previous element in array
        while (m > 0 && (Arr[m] < Arr[m - 1])) m--;
        // printf("m - 1 = %d \n", m - 1);
        // stop condition for generate next configuaration
        if(m == 0) break;
        // swap key-element and the smallest element that is larger than the current element
        k = n - 1;
        while (k > m - 1 && (Arr[k] < Arr[m - 1])) k --;
        temp = Arr[m - 1];
        Arr[m - 1] = Arr[k];
        Arr[k] = temp;
        // reserve the desending array part
        for (size_t j = 0; j < (n - m)/2; j++){
            temp = Arr[m + j];
            Arr[m + j] =  Arr[n - 1 - j];
            Arr[n - 1 - j] = temp;
        }
    }
}

// calculate factorial of n
int factorial(int n){
    if(n <= 1) return 1;
    return n*factorial(n - 1);
}