CC = gcc -Wall
CFLAGS = `gmt-config --cflags` `gdal-config --cflags`

pssac.so: pssac.c sacio.o
	$(CC) -c pssac.c -fPIC $(CFLAGS)
	$(CC) -shared -o pssac.so pssac.o sacio.o
sacio.o: sacio.c
	$(CC) sacio.c -c -o sacio.o -fPIC

clean:
	rm *.o
