parser_test: parser.o main.o
	gcc -o parser_test parser.o main.o

parser.o : parser.c parser.h
	gcc -c -o parser.o parser.c

main.o : main.c parser.h
	gcc -c -o main.o main.c


clean:
	rm -f *.o
	rm -f parser_test

