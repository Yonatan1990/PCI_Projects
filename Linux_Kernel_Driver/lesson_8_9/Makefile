
CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer
#CXXFLAGS = -DLOOPBACK 

main: SITALpci.o 
	$(CC) $(CFLAGS) $(CXXFLAGS) -o main SITALpci.o 
	echo "Linking the compiled files"
SITALpci.o: SITALpci.c
	$(CC) $(CFLAGS) $(CXXFLAGS)  -c SITALpci.c

clean:
	rm SITALpci.o main
