#include "intal.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int max(int one, int two){
    return one>two?one:two;
}

static int min(int one, int two){
    return one>two?two:one;
}

static void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b=temp;
}

static void reverse(char *result){
    int indexResult = strlen(result);
    int k = 0;
    while(k < indexResult/2){
        swap(&result[k], &result[indexResult-k-1]);
        ++k;
    }
}

static char* subString(const char *str, int first, int last){
    char* temp = (char*)malloc(sizeof(char)*(last-first+2));
    int k=0;
    for(int i=first; i<=last; ++i){
        temp[k++] = str[i];
    }
    temp[k] = '\0';
    return temp; 
}

static char* powFunc(const char *arr, int n){
    if(n == 1){
        char *temp = (char*)malloc(sizeof(char)*strlen(arr));
        strcpy(temp, arr);
        return temp;
    }
    char *temp =NULL;
    char *temp1 = powFunc(arr, n/2); 
    
    if(n%2){
        char *temp2 = intal_multiply(temp1, temp1);
        temp = intal_multiply(temp2, arr);
        free(temp1);
        free(temp2);
    }
    else{
        temp = intal_multiply(temp1, temp1);
        free(temp1);
    }
    return temp;
}

static char* powerFunc2(const char* intal1, int n){
    int arr[n];
    int i=0;
    int k = n;
    while(k!=0){
        arr[i++] = k;
        k/=2;
    }
    char* temp = NULL;
    for(int k=i-1;k>=0;--k){
        if(arr[k] == 1){
            temp = (char*)malloc(sizeof(char)*strlen(intal1)+2);
            strcpy(temp, intal1);
        }
        else if(arr[k]%2){
            char *temp1=intal_multiply(temp, temp);
            char *temp2 = intal_multiply(temp1, intal1);
            free(temp);
            temp = (char*)malloc(sizeof(char)*strlen(temp2)+2);
            strcpy(temp, temp2);
            free(temp1);
            free(temp2);
        }
        else{
            char *temp1=intal_multiply(temp, temp);
            free(temp);
            temp = (char*)malloc(sizeof(char)*strlen(temp1)+2);
            strcpy(temp, temp1);
            free(temp1);
        }
    }
    return temp;
}
//main function




char* intal_add(const char* intal1, const char* intal2){
    int len1 = strlen(intal1)-1;
    int len2 = strlen(intal2)-1;
    char *result = (char*)malloc(sizeof(char)*(max(len1+1, len2+1)+2));
    int indexResult=0;
    int carry = 0;
    int one, two, res;
    
    while(len1 >=0 || len2>=0){
        one = two = 0;
        if(len1>=0){
            one = intal1[len1--] - '0';
        }
        if(len2>=0){
            two= intal2[len2--] - '0';
        }
        
        res = one+two+carry;
        carry = res/10;
        result[indexResult++] = (res%10)+'0';    
    }
    if(carry!=0){
        result[indexResult++] = carry +'0';
    }
    
    result[indexResult] = '\0';
    reverse(result);
    return result; 
}

int intal_compare(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int i1=0, i2=0;
    
    while(i1<len1 && len1!=1 && intal1[i1]=='0') ++i1;
    while(i2<len2 && len2!=1 && intal2[i2]=='0') ++i2;

    if(i1 == len1){
        i1--;
    }
    if(i2 == len2)
        i2--;


    if(len1-i1 > len2-i2)
        return 1;
    else if(len2-i2 > len1-i1) 
        return -1;
    else {
        int i=0;
        while(i<len1-i1 && intal1[i+i1] == intal2[i+i2]){
            ++i;
        }
        if(i == len1-i1)
            return 0;
        else{
            if(intal1[i+i1]-'0' > intal2[i+i2]-'0')
                return 1;
            else
                return -1;
        }
    }
}

char* intal_diff(const char* intal1, const char* intal2){
    int len11 = strlen(intal1);
    int len22 = strlen(intal2);
    char *first, *second;
    int val = intal_compare(intal1, intal2);

    if(val == -1){
        first = (char*)malloc(sizeof(char)*(len22+2 ));
        second = (char*)malloc(sizeof(char)*(len11+2 ));
        strcpy(first, intal2);
        strcpy(second, intal1);
        first[len22] = '\0';
        second[len11] = '\0';
    }
    else if(val == 1){
        first = (char*)malloc(sizeof(char)*(len11+2 ));
        second = (char*)malloc(sizeof(char)*(len22 +2));
        strcpy(first, intal1);
        strcpy(second, intal2);
        first[len11] = '\0';
        second[len22] = '\0';
    }

    else if(val == 0){
        char *result = (char*)malloc(sizeof(char)*2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int len1 = strlen(first)-1;
    int len2 = strlen(second)-1;
    int res;
    char *result = (char*)malloc(sizeof(char)*len1+2);
    int index = 0;
    while(len1>=0){
        res = 0;
        int val1 = first[len1--] - '0';
        int val2 = 0;
        if(len2>=0)
            val2 = second[len2--] - '0';
        if(val1 < val2){
            val1+=10;
            int k = len1;
            while(k >=0 && first[k] == '0'){
                first[k] = '9';
                --k;
            }
            int x = first[k]-'0';
            first[k] = (x-1) +'0';
        }
        res = val1- val2;
        result[index++] = res +'0';
    }
    result[index] = '\0';
    while(index >=0 && result[index-1] == '0'){
        result[index-1] ='\0';
        index--;
    }
    
    reverse(result);
    
    return result;
}

char* intal_multiply(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int carry=0, curNo, res;
    char *arr[len1+1];
    
    for(int i=len1-1;i>=0; --i){
        arr[len1-1-i] = (char*)malloc(sizeof(char)*(len2+1+(len1-1-i)+2));
        int curIndex=0;
        carry = 0;
        curNo = intal1[i] - '0';
        int k = len1-1-i;
        while(k!=0){
            arr[len1-1-i][curIndex++] = '0';
            --k;
        }

        for(int j=len2-1;j>=0;--j){
            res = (curNo *(intal2[j]-'0'))+carry;
            arr[len1-1-i][curIndex++] = res%10 + '0';
            carry = res/10;
        }
        if(carry!=0)
            arr[len1-1-i][curIndex++] = carry + '0';
        arr[len1-i-1][curIndex] = '\0';
    }
    reverse(arr[0]);
    char *temp = arr[0];
    char *freeIt;
    for(int i=1;i<len1; ++i){
        reverse(arr[i]);
        freeIt = temp;
        temp = intal_add(freeIt, arr[i]);
        free(freeIt);
    }
    return temp;
}

char* intal_mod(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    char* inside = (char*)malloc((sizeof(char)*len1)+2);
    char* rem = (char*)malloc(sizeof(char)*len2 - 1);
    //below need to be optimized with space and time
    char* temp = subString(intal1, 0, len2-1);
    int index = len2-1;
    while(intal_compare(intal2, temp) == 1){
        free(temp);
        temp = subString(intal1, 0, ++index);
    }

    strcpy(inside, temp);
    free(temp);
    while(index <= len1-1 ){
        int mul = 1;
        int res = intal_compare(inside, intal2);

        while(res == 1){
            ++mul;
            char valInString = mul+'0';
            char a[3]={valInString,'\0'};
            char *temp1 = intal_multiply(intal2, a);
            res = intal_compare(inside, temp1);
            free(temp1);
        }
        if(res == 0){
            free(inside);
            inside = (char*)malloc((sizeof(char)*len2)+2);
            if(index == len1-1){
                char *a=(char*)malloc(sizeof(char)*2);
                a[0] = '0';
                a[1] = '\0';
                return a;
            }
            char* temp = subString(intal1, index+1, index+len2);
            index+=len2;
            strcpy(inside, temp);
            free(temp);
            int k = strlen(inside);
            while(index < len1 && intal_compare(intal2, inside) == 1){
                char *A = subString(intal1, index+1, index+1);
                strcat(inside, A);
                ++index;
                // inside[k++] = intal1[++index];
            }
        }
        else if(res == -1){
            char valInString = (mul-1)+'0';
            char a[3]={valInString,'\0'};
            char *temp1 = intal_multiply(intal2, a);
            char *diff = intal_diff(inside, temp1);
            //printf("diff = %s\n",diff);
            free(temp1);
            free(inside);
            inside = (char*)malloc(sizeof(char)*len1);
            strcpy(inside, diff);
            //printf("befor e = %s\n", inside);
            int n = strlen(inside);
            if(index+1 <len1){
                char *A = subString(intal1, index+1,index+1);
                strcat(inside,A);
                free(A);
                index++;
            }
                
            

            if(index != len1-1 && strlen(diff)< len2){
                char* temp = subString(intal1, index+1, index+len2-strlen(diff));
                index+=len2-strlen(diff);
                strcat(inside, temp);
                free(temp);
            }
            
            free(diff);
            int temp = strlen(inside);
            while(index <= len1-1 && intal_compare(inside, intal2) == -1){
                //printf("%s %d\n", inside, index);
                inside[temp] = intal1[index+1];
                index++;
                ++temp;
            }

            temp = intal_compare(inside, intal2);
            if(temp == -1){
                return  inside;
            }
            
        }  
    }

    return inside;

}

char* intal_pow(const char* intal1, unsigned int n){
    if(!strcmp(intal1, "0")){
        char* temp = (char*)malloc(sizeof(char)*2);
        temp[0]='0';
        temp[1]='\0';
        return temp;
    }
    if(n == 0){
        char* temp = (char*)malloc(sizeof(char)*2);
        temp[0] = '1';
        temp[1]= '\0';
        return temp;
    }
    char *temp = powerFunc2(intal1, n);
    char *temp1 = (char*)malloc(sizeof(char)*strlen(temp)+2);
    strcpy(temp1, temp);
    free(temp);
    return temp1;
}

char* intal_gcd(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    char* copy1 = (char*)malloc(sizeof(char)*len1+2);
    char* copy2 = (char*)malloc(sizeof(char)*len2+2);
    strcpy(copy1, intal1);
    strcpy(copy2, intal2);
    int res = strcmp(copy2, "0");
    while(res!=0){
        char *mod = intal_mod(copy1 , copy2);
        free(copy1);
        copy1 = (char*)malloc(sizeof(char)*strlen(copy2)+2);
        strcpy(copy1, copy2);
        free(copy2);
        copy2 = (char*)malloc(sizeof(char)*strlen(mod)+2);
        strcpy(copy2, mod);
        free(mod);
        res = strcmp(copy2, "0");
    }
    free(copy2);
    return copy1;
}

char* intal_fibonacci(unsigned int n){
    char* prev = (char*)malloc(sizeof(char)*2);
    prev[0]='0';
    prev[1]='\0';
    char* cur = (char*)malloc(sizeof(char)*2);
    cur[0]='1';
    cur[1]='\0';
    for(int i=2;i<=n;++i){
        char* temp = intal_add(prev, cur);
        free(prev);
        prev = (char*)malloc(sizeof(char)*(strlen(cur)+2));
        strcpy(prev, cur);
        free(cur);
        cur = (char*)malloc(sizeof(char)*(strlen(temp)+2));
        strcpy(cur, temp);
        free(temp);
    }
    return cur;
}

char* intal_factorial(unsigned int n){
    char* cur = (char*)malloc(sizeof(char)*2);
    cur[0] = '1';
    cur[1] = '\0';
    char *temp;
    for(int i = 2;i<=n;++i){
        int k = i;
        int index = 0;
        while(k){
            index++;
            k /= 10;
        }
        char* temp = (char*)malloc(sizeof(char)*index+2);
        k=i;
        temp[index] = '\0';
        while(k){
            temp[--index] =(k%10)+'0';
            k/=10;
        }

        char *result = intal_multiply(cur, temp);
        free(cur);
        free(temp);
        cur = (char*)malloc(sizeof(char)*strlen(result)+2);
        strcpy(cur, result);
        cur[strlen(cur)] = '\0';
        free(result);
    }
    return cur;
}