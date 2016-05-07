CC = g++
CFLAGS  = -std=c++11 -g -Wall

project5: project5.o 
	$(CC) $(CFLAGS) project5.o -o project5

project5.o: project5.cpp
	$(CC) $(CFLAGS) -c project5.cpp

clean:
	rm -f *.o
	rm -f project5
