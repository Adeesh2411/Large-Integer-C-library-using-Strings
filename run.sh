gcc test.c PES1201700959.c -g 
valgrind --leak-check=full --log-file="logfile1.out"   -v ./a.out  
