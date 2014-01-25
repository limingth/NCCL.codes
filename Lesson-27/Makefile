
SRC = sed.c

CMD = sed 

all:
	gcc main.c $(SRC) -o $(CMD)

t test: 
	gcc main.c $(SRC) -o $(CMD)
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux/g
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux/3

d debug: 
	gcc main.c $(SRC) -o $(CMD) -DDEBUG
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux/g
	echo "unix is great os. unix is opensource. unix is free os." | ./$(CMD) s/unix/linux/3

clean:
	-rm $(CMD)
