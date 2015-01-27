CC = gcc
CFLAGS = -I. -lwiringPi
DEPS = 
OBJ = dht11.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dht11: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
