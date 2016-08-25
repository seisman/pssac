CFLAGS = `gmt-config --cflags` `gdal-config --cflags`

all: pssac.so

pssac.so: pssac.o sacio.o
	$(CC) -shared $^ -o $@

pssac.o: pssac.c
	$(CC) -c $^ $(CFLAGS) -fPIC

sacio.o: sacio.c
	$(CC) $^ -c -o $@ -fPIC

clean:
	rm *.o
