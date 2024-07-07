

CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer
CXXFLAGS = -DLOOPBACK 

main: main.o 1553.o brmMaster.o
	$(CC) $(CFLAGS) $(CXXFLAGS) -o main main.o 1553.o brmMaster.o
	echo "Linking the compiled files"
main.o: main.c
	$(CC) $(CFLAGS) $(CXXFLAGS)  -c main.c

1553.o: 1553.c
	$(CC) $(CFLAGS) $(CXXFLAGS)  -c 1553.c

brmMaster.o: brmMaster.c
	$(CC) $(CFLAGS) $(CXXFLAGS)  -c brmMaster.c


clean:
	rm main.o 1553.o brmMaster.o 
