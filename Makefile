CC = gcc -Wall
CFLAGS = `gmt-config --cflags` `gdal-config --cflags`
plugindir = /opt/GMT-5.2.1/lib64/gmt/plugins

all: pssac.so

pssac.so: pssac.o sacio.o
	$(CC) -shared $^ -o $@

pssac.o: pssac.c
	$(CC) -c $^ $(CFLAGS) -fPIC

sacio.o: sacio.c
	$(CC) $^ -c -o $@ -fPIC

install: pssac.so
	install pssac.so $(plugindir)

clean:
	rm *.o pssac.so
