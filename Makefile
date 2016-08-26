CFLAGS = -fPIC `gmt-config --cflags` `gdal-config --cflags`
LDFLAGS = -shared `gmt-config --libs` -lpostscriptlight

all: pssac.so

pssac.so: pssac.o sacio.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm *.o
