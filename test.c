#include<stdio.h>
#include"intal.h"
#include<string.h>
#include<stdlib.h>
int main(){
    int s=1;
    char *test = intal_gcd("12", "1000");

    printf("mod = %s\n", test);
    free(test);
}
