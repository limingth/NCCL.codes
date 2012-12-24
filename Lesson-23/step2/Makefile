all:
	gcc pipe.c -o pipe
	gcc match.c -o match

t1:
	rm log.txt
	./match pc | ./pipe

t2:
	rm log.txt
	./match pc | ./pipe | ./match people | ./pipe 
