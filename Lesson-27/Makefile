
SRC = sed.c

CMD = sed 

all:
	gcc main.c $(SRC) -o $(CMD)

t test: all
	./$(CMD) s/unix/linux

clean:
	-rm $(CMD)
