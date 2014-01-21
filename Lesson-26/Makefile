
SRC = readelf.c

CMD = readelf 

all:
	gcc main.c $(SRC) -o $(CMD)

t test: all
	./$(CMD) $(CMD)

clean:
	-rm $(CMD)
