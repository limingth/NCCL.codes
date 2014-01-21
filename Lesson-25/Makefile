
SRC = mycp.c

CMD = mycp

all:
	gcc main.c $(SRC) -o $(CMD)

t test:
	./$(CMD) a b
	cat a
	cat b

clean:
	-rm a b
	-rm $(CMD)
