#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char ch;
    // create frequency of digits with initialize zeros
    int *freqOfDigits = (int*)calloc(10, sizeof(int));
    // find frequency of digits in the input string
    do{
        scanf("%c", &ch);
        if(ch >= '0' && ch <= '9')
            *(freqOfDigits + ch - 48) += 1;
    } while (ch != '\n');
    // print frequency of digits in the input string
    for (size_t i = 0; i < 10; i++){
        printf("%d ", *(freqOfDigits + i));
    }
    printf("\n");
    return 0;
}
