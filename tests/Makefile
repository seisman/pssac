PS = $(patsubst %.sh, %.ps, $(wildcard *.sh))

all: $(PS)

%.ps: %.sh
	sh $<

clean:
	rm $(PS)
