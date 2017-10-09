# generation flags
CC = gcc -ansi -pedantic
CFLAGS = -Wall

all: generacion.o ejemplo1_generacion ejemplo2_generacion ejemplo3_generacion

clean:
	rm *.o ejemplo1_generacion ejemplo2_generacion ejemplo3_generacion

ejemplo1_generacion: ejemplo1_generacion.o generacion.o generacion.h
	$(CC) $(CFLAGS) -o $@ $@.o generacion.o

ejemplo2_generacion: ejemplo2_generacion.o generacion.o generacion.h
	$(CC) $(CFLAGS) -o $@ $@.o generacion.o

ejemplo3_generacion: ejemplo3_generacion.o generacion.o generacion.h
	$(CC) $(CFLAGS) -o $@ $@.o generacion.o

ejemplo1_generacion.o: ejemplo1_generacion.c
	$(CC) -c ejemplo1_generacion.c

ejemplo2_generacion.o: ejemplo2_generacion.c
	$(CC) -c ejemplo2_generacion.c

ejemplo3_generacion.o: ejemplo3_generacion.c
	$(CC) -c ejemplo3_generacion.c

generacion.o: generacion.c
	$(CC) -c generacion.c