#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "intal.h"

int main(){

	// char **arr = (char*)malloc(sizeof(char*)*12);
	// for(int i=0;i<12;++i){
	// 	arr[i] = (char*)malloc(sizeof(char)*50);
	// }

    // char *a={"12","344","546456","334","2453452345","435236256","2652463254","33","0","67","435236256"}
    char* result1 = intal_mod("17", "29");
    
    printf("mod = %s\n", result1);
    free(result1);
}

/*

*/
