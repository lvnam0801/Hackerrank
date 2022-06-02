#include <stdio.h>
#define MAX_LEN 256

int main(){
    char s[MAX_LEN];
    int i = 0, r = 3;
    for(; i < r; ++i){
        scanf("%[^\n]%*c", s); // có %*c
        // scanf("%[^\n]", s); // không có %*c
        printf("====\nINPUT: %s\n====\n", s);
    }
}