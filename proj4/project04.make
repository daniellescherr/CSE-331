prog:	main.o
	g++ main.o -o prog

main.o:	main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -rf main.o
