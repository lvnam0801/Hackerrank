#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char str[1000];
    scanf("%s", str);
    // create frequency of digits with initialize value = zeros
    int *freqOfDigits = (int*)calloc(10, sizeof(int));
    // find frequency of digits in the string entered by user
    for (int i = 0; i < strlen(str); i++){
        switch (str[i]) {
            case '0' :
                freqOfDigits[0] += 1;
                break;
            case '1' :
                freqOfDigits[1] += 1;
                break;
            case '2' :
                freqOfDigits[2] += 1;
                break;
            case '3' :
                freqOfDigits[3] += 1;
                break;
            case '4' :
                freqOfDigits[4] += 1;
                break;
            case '5' :
                freqOfDigits[5] += 1;
                break;
            case '6' :
                freqOfDigits[6] += 1;
                break;
            case '7' :
                freqOfDigits[7] += 1;
                break;
            case '8' :
                freqOfDigits[8] += 1;
                break;
            case '9' :
                freqOfDigits[9] += 1;
                break;
            default:
                break; 
        }
    }
    for (int i = 0; i < 10; i++){
        printf("%d ", *(freqOfDigits + i));
    }
    return 0;
}
