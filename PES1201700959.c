#include "intal.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//to get max of two numbers
static int max(int one, int two){
    return one>two?one:two;
}

//to get min of two numbers
static int min(int one, int two){
    return one>two?two:one;
}

//swaps the two char
static void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b=temp;
}

//reverses the given string
static void reverse(char *result){
    int indexResult = strlen(result);
    int k = 0;
    while(k < indexResult/2){
        swap(&result[k], &result[indexResult-k-1]);
        ++k;
    }
}

//to get the substring from thw given string in the given range
static char* subString(const char *str, int first, int last){
    char* temp = (char*)malloc(sizeof(char)*(1001));
    int k=0;
    for(int i=first; i<=last; ++i){
        temp[k++] = str[i];
    }
    if(k<1000)
        temp[k] = '\0';
    return temp; 
}

//recursive function to calculate the arr ^ n in O(log(n)) time , provided all the other addition and multiplication
//runs in constant time
static char* powFunc(const char *arr, int n){
    if(n == 1){
        char *temp = (char*)malloc(sizeof(char)*1001);
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

//binary Search function
static int binSearch(char** arr, int start, int end, const char* key){
    if(start <= end){
        int mid = (start+end)/2;
        int res = intal_compare(arr[mid], key);
        if(res == -1){
            return binSearch(arr, mid+1, end, key);
        }   
        else if(res == 1){
            return binSearch(arr,start, mid-1, key);
        } 
        else{
            return mid;
        }
    }
    return -1;
}

//partition function for quick sort
static int partition(char **arr, int start, int end){
    int p = start;
    int i = start+1;
    int j = start+1;
    
    while(i<=end && j<=end){
        int res = intal_compare(arr[p], arr[j]);
        if(res == -1){ //arr[j] > pivot
            ++j;
        }
        else{
            //swap
            if(i!=j){
                char* temp = (char*)malloc(sizeof(char)*1001);
                strcpy(temp, arr[i]);
                free(arr[i]);
                arr[i] = (char*)malloc(sizeof(char)*1001);
                strcpy(arr[i], arr[j]);
                free(arr[j]);
                arr[j] = (char*)malloc(sizeof(char)*1001);
                strcpy(arr[j], temp);
                free(temp);
            }
            ++i;
            ++j;
        }
    }
    if(p!=i-1){
        char* temp = (char*)malloc(sizeof(char)*1001);
        strcpy(temp, arr[p]);
        free(arr[p]);
        arr[p] = (char*)malloc(sizeof(char)*1001);
        strcpy(arr[p], arr[i-1]);
        free(arr[i-1]);
        arr[i-1] = (char*)malloc(sizeof(char)*1001);
        strcpy(arr[i-1], temp);
        free(temp);
    }
    return i-1;
}
//performs the quick sort
static void quickSort(char** arr, int start, int end){
    if(start<end){
        int p = partition(arr, start, end);
        quickSort(arr,start,p-1);
        quickSort(arr, p+1, end);
    }
}
/****************************************************************
main function
****************************************************************/

char* intal_add(const char* intal1, const char* intal2){
    int len1 = strlen(intal1)-1;
    int len2 = strlen(intal2)-1;
    char *result = (char*)malloc(sizeof(char)*(1001));
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
        first = (char*)malloc(sizeof(char)*(1001 ));
        second = (char*)malloc(sizeof(char)*(1001 ));
        strcpy(first, intal2);
        strcpy(second, intal1);
        first[len22] = '\0';
        second[len11] = '\0';
    }
    else if(val == 1){
        first = (char*)malloc(sizeof(char)*(1001 ));
        second = (char*)malloc(sizeof(char)*(1001));
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
    char *result = (char*)malloc(sizeof(char)*1001);
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
    free(first);
    free(second);
    return result;
}

char* intal_multiply(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int carry=0, curNo, res;
    char *arr[len1+1];
    
    for(int i=len1-1;i>=0; --i){
        arr[len1-1-i] = (char*)malloc(sizeof(char)*(1001));
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
    char *prev = (char*)malloc(sizeof(char)*1001);
    strcpy(prev, arr[0]);
    free(arr[0]);
    
    for(int i=1;i<len1; ++i){
        reverse(arr[i]);
        char *cur = (char*)malloc(sizeof(char)*1001);
        strcpy(cur, arr[i]);
        free(arr[i]);

        char *temp1 = intal_add(prev, cur);
        free(prev);
        prev = (char*)malloc(sizeof(char)*1001);
        strcpy(prev, temp1);

        free(cur);
        free(temp1);
    }
    int st = 0;
    for(int i=0;i<strlen(prev);i++){
        if(prev[i] == '0')
            ++st;
        else
            break;
    }
    //printf("%s",prev);
    if(st == strlen(prev)){
        char *temp = (char*)malloc(sizeof(char)*2);
        temp[0]='0';
        temp[1] = '\0';
        return temp;
    }
    char *finalresult = subString(prev, st, strlen(prev));
    free(prev);
    return finalresult;
}

char* intal_mod(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    if(intal_compare(intal1, intal2) == -1){
        char* temp = (char*)malloc(sizeof(char)*1001);
        strcpy(temp, intal1);
        return temp;
    }

    char* rem = (char*)malloc(sizeof(char)*1001);
    char* temp = subString(intal1, 0, len2-1);
    char* inside = (char*)malloc((sizeof(char)*1001));
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
            inside = (char*)malloc((sizeof(char)*1001));
            if(index == len1-1){
                char *a=(char*)malloc(sizeof(char)*2);
                a[0] = '0';
                a[1] = '\0';
                free(rem);
                free(inside);
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
            }
        }
        else if(res == -1){
            char valInString = (mul-1)+'0';
            char a[3]={valInString,'\0'};
            char *temp1 = intal_multiply(intal2, a);
            char *diff = intal_diff(inside, temp1);

            free(temp1);
            free(inside);
            inside = (char*)malloc(sizeof(char)*1001);
            strcpy(inside, diff);

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
                inside[temp] = intal1[index+1];
                index++;
                ++temp;
            }

            temp = intal_compare(inside, intal2);
            if(temp == -1){             
                free(rem);
                return  inside;
            }
            
        }  
    }
    free(rem);
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
    char *temp = powFunc(intal1, n);
    char *temp1 = (char*)malloc(sizeof(char)*1001);
    strcpy(temp1, temp);
    free(temp);
    return temp1;
}

char* intal_gcd(const char* intal1, const char* intal2){
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    char* copy1 = (char*)malloc(sizeof(char)*(1001));
    char* copy2 = (char*)malloc(sizeof(char)*1001);
    strcpy(copy1, intal1);
    strcpy(copy2, intal2);
    int res = strcmp(copy2, "0");

    while(res!=0){
        char *mod = intal_mod(copy1 , copy2);
        free(copy1);
        copy1 = (char*)malloc(sizeof(char)*1001);
        strcpy(copy1, copy2);
        free(copy2);
        copy2 = (char*)malloc(sizeof(char)*1001);
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

    if(n == 0){
        free(cur);
        return prev;
    }
    for(int i=2;i<=n;++i){
        char* temp = intal_add(prev, cur);
        free(prev);
        prev = (char*)malloc(sizeof(char)*(1001));
        strcpy(prev, cur);
        free(cur);
        cur = (char*)malloc(sizeof(char)*(1001));
        strcpy(cur, temp);
        free(temp);
    }
    free(prev);
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
        char* temp = (char*)malloc(sizeof(char)*1001);
        k=i;
        temp[index] = '\0';
        while(k){
            temp[--index] =(k%10)+'0';
            k/=10;
        }

        char *result = intal_multiply(cur, temp);
        free(cur);
        free(temp);
        cur = (char*)malloc(sizeof(char)*1001);
        strcpy(cur, result);
        cur[strlen(cur)] = '\0';
        free(result);
    }
    return cur;
}

char* intal_bincoeff(unsigned int n, unsigned int k){
    char **dp = (char**)malloc(sizeof(char*)*(1001));
    for(int i=0;i<=k;++i){
        dp[i] = (char*)malloc(sizeof(char)*2);
        if(i==0)
            dp[i][0] = '1';
        else
            dp[i][0]='0';
        dp[i][1]= '\0';
    }
    char* cur;
    char* prev;
    
    for(int i=1;i<=n;++i){
        
        cur = (char*)malloc(sizeof(char)*1001);
        strcpy(cur, dp[0]);

        for(int j=1;j<=i && j<=k;++j){
        
            prev = (char*)malloc(sizeof(char)*1001);
            strcpy(prev, cur);
            free(cur);
            cur = (char*)malloc(sizeof(char)*1001);
            strcpy(cur, dp[j]);

            char* temp = intal_add(prev, cur);
            
            free(dp[j]);
            
            dp[j] = (char*)malloc(sizeof(char)*(1001));
            strcpy(dp[j], temp);
            free(temp);
            free(prev);
            if(i%2==0 && j+1 == (i/2)){
                char* addMiddle = intal_add(cur, cur);
                free(dp[j+1]);
                dp[j+1] = (char*)malloc(sizeof(char)*1001); 
                strcpy(dp[j+1], addMiddle);
                free(addMiddle);
                break;
            }
            if(i%2==1 && j+1 == (i+1)/2 )
                break;            
             
        }
        free(cur);
    }
    int mid = k+1;
    if(n%2 == 0 && k>(n/2)+1){
        mid = (n/2)+1;
        int t = k - ((n/2)+1);
        mid-=t+1;
    }   
    else if(n%2==1 && k > (n+1)/2){
        mid = (n+1)/2;
        int t= k-(n+1)/2 ;
        mid-=t+1;
    }
    char *result = (char*)malloc(sizeof(char)*1001);
    
    strcpy(result, dp[mid-1]);
    for(int i=0;i<=k;++i){
        free(dp[i]);
    }

    free(dp);
    return result;
}

int intal_max(char **arr, int n){
    int index = 0;
    for(int i=1;i<n;++i){
        int res = intal_compare(arr[index], arr[i]);
        if(res ==-1){
            index = i;
        }
    }
    return index;
}

int intal_min(char **arr, int n){
    int index = 0;
    for(int i=1;i<n;++i){
        int res = intal_compare(arr[index], arr[i]);
        if(res ==1){
            index = i;
        }
    }
    return index;  
}

int intal_search(char **arr, int n, const char* key){
    for(int i=0;i<n;++i){
        if(!strcmp(arr[i], key))
            return i;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key){
    int temp = binSearch(arr, 0, n-1,key);
    while(temp>0){
        if(!strcmp(key, arr[temp-1])){
            temp--;
        }
        else{
            break;
        }
    }
    return temp;
}

void intal_sort(char **arr, int n){
    quickSort(arr,0,n-1);
}

char* coin_row_problem(char **arr, int n){
    char *prev = (char*)malloc(sizeof(char)*4);
    prev[0]='0';
    prev[1]='\0';

    char *cur = (char*)malloc(sizeof(char)*1001);
    strcpy(cur, arr[0]);

    for(int i = 1; i<n; ++i){
        char *temp1 = intal_add(prev, arr[i]);
        int res = intal_compare(temp1, cur);
        if(res == 1){
            //temp = prev; prev = cur; cur = temp+arr[i]
            free(prev);
            prev = (char*)malloc(sizeof(char)*1001);
            strcpy(prev, cur);

            free(cur);
            cur = (char*)malloc(sizeof(char)*1001);
            strcpy(cur, temp1);
        }
        else{//prev = cur
            free(prev);
            prev = (char*)malloc(sizeof(char)*1001);
            strcpy(prev, cur);
        }
        free(temp1);
    }
    free(prev);
    return cur;
}