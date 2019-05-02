out : main.o encryption.o matrix.o str.o
	gcc main.o encryption.o matrix.o str.o -o out

main.o : main.c
	gcc -c main.c 

encryption.o : encryption.c encryption.h
	gcc -c encryption.c

matrix.o : matrix.c matrix.h
	gcc -c matrix.c

str.o : str.c str.h
	gcc -c str.c

clean :
	rm *.o

clean_txt :
	rm *.txt 
	rm *.o

cleanall :
	rm *.o out