"""
Python 2.X
Basic Usage:
python testing.py <code.c> <input.json>
Defaults:
code.c
test.json
"""

import os,sys
import json
from ctypes import *
import math
arglen = len(sys.argv)
if arglen <= 1:
    code = "code.c"
    inp_json = "test.json"
elif arglen == 2:
    code = sys.argv[1]
    inp_json = "test.json"
elif arglen == 3:
    code = sys.argv[1]
    inp_json = sys.argv[2]
os.system("cc -fPIC -shared -o code.so {}".format(code))
path = os.path.join(sys.path[0], "code.so")
print(path)
fun = CDLL(path)
def prRed(skk): print("\033[91m {}\033[00m" .format(skk)) 
def prGreen(skk): print("\033[92m {}\033[00m" .format(skk))
def computeGCD(x, y):
    while(y): 
        x, y = y, x % y 
    return x
def fibonacci(n):
    if(n<1):return n
    a =0;b=1
    for i in range(n-1): 
        t = a+b; a=b; b=t 
    return b
def factorial(n):
    return math.factorial(n)
def binom(n, k):
    if not 0<=k<=n: return 0
    return math.factorial(n) // math.factorial(k) // math.factorial(n-k)
def coin_row(arr):
    n = len(arr)
    if n<=0:return 0
    a = 0
    b=arr[0]
    for i in range(1,n):
        temp = arr[i]+a
        a = b
        b = max(temp,b)
    return b

#1
fun.intal_add.argtypes = [c_char_p, c_char_p]
fun.intal_add.restype = c_char_p
print("add passed")
#2
fun.intal_compare.argtypes = [c_char_p,c_char_p]
fun.intal_compare.restype = c_int
print("comapre passed")
#3
fun.intal_diff.argtypes = [c_char_p,c_char_p]
fun.intal_diff.restype = c_char_p
print("diff passed")
#4
fun.intal_multiply.argtypes = [c_char_p,c_char_p]
fun.intal_multiply.restype = c_char_p
print("multipley passed")
#5
fun.intal_mod.argtypes = [c_char_p, c_char_p]
fun.intal_mod.restype = c_char_p
#6
fun.intal_pow.argtypes = [c_char_p, c_uint]
fun.intal_pow.restype = c_char_p
#7
fun.intal_gcd.argtypes = [c_char_p, c_char_p]
fun.intal_gcd.restype = c_char_p
#8
fun.intal_fibonacci.argtypes = [c_uint]
fun.intal_fibonacci.restype = c_char_p
#9
fun.intal_factorial.argtypes = [c_uint]
fun.intal_factorial.restype = c_char_p
#10
fun.intal_bincoeff.argtypes = [c_uint, c_uint]
fun.intal_bincoeff.restype = c_char_p
print("function passed")
#11
fun.intal_max.argtypes = [POINTER(c_char_p), c_int]
fun.intal_max.restype = c_int
#12
fun.intal_min.argtypes = [POINTER(c_char_p), c_int]
fun.intal_min.restype = c_int
#13
fun.intal_search.argtypes = [POINTER(c_char_p), c_int, c_char_p]
fun.intal_search.restype = c_int
#14
fun.intal_binsearch.argtypes = [POINTER(c_char_p), c_int, c_char_p]
fun.intal_binsearch.restype = c_int
#15
fun.intal_sort.argtypes = [POINTER(c_char_p), c_int]
#16
fun.coin_row_problem.argtypes = [POINTER(c_char_p), c_int]
fun.coin_row_problem.restype = c_char_p
print("done")
class Test:
    def add(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            x = str(a+b)
            y = fun.intal_add(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_add PASSED")
        else:prRed("\tTest intal_add FAILED")

    def compare(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            if a>b:x=1
            elif a<b:x=-1
            else:x=0
            y = fun.intal_compare(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_compare PASSED")
        else:prRed("\tTest intal_compare FAILED")

    def diff(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            x = str(abs(a-b))
            y = fun.intal_diff(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_diff PASSED")
        else:prRed("\tTest intal_diff FAILED")
    
    def multiply(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            x = str(a*b)
            y = fun.intal_multiply(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_multiply PASSED")
        else:prRed("\tTest intal_multiply FAILED")
    
    def mod(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            x = str(a%b)
            y = fun.intal_mod(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_mod PASSED")
        else:prRed("\tTest intal_mod FAILED")
    
    def pow(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            x = str(pow(a,b))
            if(a==0 and b==0):
                x="0"
            y = fun.intal_pow(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_pow PASSED")
        else:prRed("\tTest intal_pow FAILED")
    
    def gcd(info,arr):
        flag = True
        for row in arr:
            a=int(row[1]);b=int(row[2])
            if(a==0 and b==0):
                x="0"
            else:    
                x = str(computeGCD(a,b))
            y = fun.intal_gcd(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_gcd PASSED")
        else:prRed("\tTest intal_gcd FAILED")
    def fibonacci(info,arr):
        flag = True
        for row in arr:
            x = str(fibonacci(row[1]))
            y = fun.intal_fibonacci(row[1])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_fibonacci PASSED")
        else:prRed("\tTest intal_fibonacci FAILED")
    def factorial(info,arr):
        flag = True
        for row in arr:
            x = str(factorial(row[1]))
            y = fun.intal_factorial(row[1])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_factorial PASSED")
        else:prRed("\tTest intal_factorial FAILED")
    def bincoeff(info,arr):
        flag = True
        for row in arr:
            x = str(binom(row[1],row[2]))
            y = fun.intal_bincoeff(row[1],row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_bincoeff PASSED")
        else:prRed("\tTest intal_bincoeff FAILED")
    def max(info,arr):
        flag = True
        for row in arr:
            tmp = [int(i) for i in row[1]]
            x = tmp.index(max(tmp))
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            y = fun.intal_max(arr,l)
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_max PASSED")
        else:prRed("\tTest intal_max FAILED")
    def min(info,arr):
        flag = True
        for row in arr:
            tmp = [int(i) for i in row[1]]
            x = tmp.index(min(tmp))
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            y = fun.intal_min(arr,l)
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_min PASSED")
        else:prRed("\tTest intal_min FAILED")
    def search(info,arr):
        flag = True
        for row in arr:
            if row[2] not in row[1]: x=-1
            else: x=row[1].index(row[2])
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            y = fun.intal_search(arr,l,row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_search PASSED")
        else:prRed("\tTest intal_search FAILED")
    def binsearch(info,arr):
        flag = True
        for row in arr:
            if row[2] not in row[1]: x=-1
            else: x=row[1].index(row[2])
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            y = fun.intal_binsearch(arr,l,row[2])
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_binsearch PASSED")
        else:prRed("\tTest intal_binsearch FAILED")
    def sort(info,arr):
        print("info arr")
        print(info)
        print(arr)
        flag = True
        for row in arr:
            x = sorted(row[1],key=lambda x:int(x))
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            fun.intal_sort(arr,l)
            #flag2=True
            y = list()
            for i in range(l):
                y.append(int(arr[i]))
            x=[int(i) for i in x]
                
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest intal_sort PASSED")
        else:prRed("\tTest intal_sort FAILED")
    def coin_row_problem(info,arr):
        flag = True
        for row in arr:
            tmp=[int(i) for i in row[1]]
            x = str(coin_row(tmp))
            l = len(row[1])
            arr = (c_char_p * l)()
            arr[:] = row[1]
            y = fun.coin_row_problem(arr,l)
            if x!=y:
                flag = False
                print("Expected {} but got {} : {}".format(x,y,row[0]))
        if flag:prGreen("\tTest coin_row_problem PASSED")
        else:prRed("\tTest coin_row_problem FAILED")
    


if __name__== "__main__":
    f = open(inp_json)
    data = json.load(f)
    test = Test()
    for i in data:
        print(i)
        if len(data[i])>0:
            getattr(test,i)(data[i])

