// program to sort a array of string in increase order using funcion pointer to evaluate the order
// preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// function prototype
// a >= b : return 1, a < b: return 0
int lexicographic_sort(const char* a, const char* b);
int lexicographic_sort_reverse(const char* a, const char* b);
int sort_by_number_of_distinct_characters(const char* a, const char* b);
int sort_by_length(const char* a, const char* b);
// sort the string with bubble sort
void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b));

// main program
int main() 
{
    int n;
    // read data from file
    FILE *fptr;
    fptr = fopen("./dataString.txt", "r");
    fscanf(fptr, "%d", &n);
    // memory dynamic allocation
    char** arr = (char**)malloc(n * sizeof(char*));

    // memory dynamic allocation for each element of array
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        fscanf(fptr, "%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
    
    // sort with lexicographic
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++) printf("%s\n", arr[i]);
    printf("\n");

    // sort with lexicographic reverse
    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++) printf("%s\n", arr[i]); 
    printf("\n");

    // sort with lengh of string
    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++) printf("%s\n", arr[i]);    
    printf("\n");

    // sort with number of distinct characters
    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++) printf("%s\n", arr[i]); 
    printf("\n");
    
    // close communication between file pointer and file
    fclose(fptr);
    // release the memory allocated by malloc and realloc
    for(int i = 0; i < n; i++) free(*(arr + i));
    free(arr);
    return 0;
}

// function definition
// compare a string and b string with lexicographic order
int lexicographic_sort(const char* a, const char* b) {
    int i = 0;
    // loop to end of 1 of 2 string
    while (a[i] != '\0' && b[i] != '\0'){
        // compare order in the lexicography
        if(a[i] > b[i]) return 1;
        else if (a[i] < b[i]) return 0;
        i++;
    }
    // return 1 if string lengh of a > b
    if(b[i] == '\0') return 1;
    return 0;
}

// a <= b: return 1, a > b: return 0
// compare a string and b string with reverse of lexicographic order
int lexicographic_sort_reverse(const char* a, const char* b) {
    int i = 0;
     // loop to end of 1 of 2 string
    while (a[i] != '\0' && b[i] != '\0'){
        // compare order in the lexicography
        if(a[i] < b[i]) return 1;
        else if (a[i] > b[i]) return 0;
        i++;
    }
    // return 1 if string lengh of a < b
    if(a[i] == '\0') return 1;
    return 0;
}

// a >= b : return 1, a < b: return 0
int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int numOfDistCharInA = 0, numOfDistCharInB = 0;
    // calculate number of distinct character in a string
    int i = 0, flag;
    while (a[i] != '\0'){
        // flag to mark duplicate characters
        flag = 0;
        // retrieve a unevaluated string part
        for (int j = 0; j < i; j++) {
            // if encouter a character that matches the current character
            if(a[i] == a[j]){
                flag = 1;
                break;
            }
        }
        i++;
        if (flag == 1) continue;
        // incraese number of distinct character of a string if not duplicate
        numOfDistCharInA++;
    }
    // calculate number of distinct character in b string
    i = 0;
    while (b[i] != '\0'){
        // flag to mark duplicate characters
        flag = 0;
        // retrieve a unevaluated string part
        for (int j = 0; j < i; j++) {
            // if encouter a character that matches the current character
            if(b[i] == b[j]){
                flag = 1;
                break;
            }
        }
        i++;
        if (flag == 1) continue;
         // incraese number of distinct character of b string if not duplicate
        numOfDistCharInB++;
    }
    // evalue order of 2 strings
    if(numOfDistCharInA > numOfDistCharInB) return 1;
    else if(numOfDistCharInA < numOfDistCharInB) return 0;
    // if 2 string are equal, do lexicagraphic comparison
    return lexicographic_sort(a, b);
}

// a >= b : return 1, a < b: return 0
int sort_by_length(const char* a, const char* b) {
    // compare lengh of 2 strings
    if(strlen(a) > strlen(b)) return 1;
    else if(strlen(a) < strlen(b))return 0;
    // if 2 string are equal, do lexicagraphic comparison
    return lexicographic_sort(a, b);
}

// sort the string with bubble sort
void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    // retrieve sorted part
    char *temp;
    // retrieve unsorted string
    for (int i = 0; i < len - 1; i++) {
        // find smallest element in unsorted string part
        for (int j = len - 1; j > i; j--) {
            // sort with increase of  element in array
            if (cmp_func(arr[j], arr[j - 1])) continue;
            // swap 2 elements if the following element less then the previous element
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}