gcc intal_sampletest.c PES1201700959.c -g 
valgrind --leak-check=full --log-file="logfile.out" --track-origins=yes  -v ./a.out  
