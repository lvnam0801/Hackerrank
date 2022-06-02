// program to print pattern
// preprocessor
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// main program
int main() 
{
    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.
    // print first half pattern
    for (int i = 0; i < n; i++) {
        int temp = n;
        // print descending part number
        for (int j = 0; j < i; j++) {
            printf("%d ", temp--);
        }
        // print part number does not change
        for (int j = 0; j < (2*n - 1) - 2*i; j++) {
            printf("%d ", temp);
        }
        // print ascending part number
        for (int j = 0; j < i; j++) {
            printf("%d ", ++temp);
        }
        printf("\n");
    }
    // print  second half pattern
    for (int i = n - 2; i >= 0; i--) {
        int temp = n;
        // print descending part number
        for (int j = 0; j < i; j++) {
            printf("%d ", temp--);
        }
        // print part number does not change
        for (int j = 0; j < (2*n - 1) - 2*i; j++) {
            printf("%d ", temp);
        }
        // print ascending part number
        for (int j = 0; j < i; j++) {
            printf("%d ", ++temp);
        }
        printf("\n");
    }
    return 0;
}