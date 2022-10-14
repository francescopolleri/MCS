CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) -c Vector.cpp      $(CFLAGSROOT)
Main: Main.cpp Vector.o 
	$(CC) $(CFLAGS) -o Main Main.cpp Vector.o $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o
