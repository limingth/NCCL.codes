all:
	gcc pipe.c -o pipe
	gcc match.c -o match
	rm log.txt

t1:
	rm log.txt
	./match pc | ./pipe

t2:
	rm log.txt
	./match pc | ./pipe | ./match people | ./pipe 

p:
	mkfifo p1 p2

t3:
	cat p2 | ./match pc > p1

t4:
	cat p1 | ./match people > p2

t5:
	-rm log.txt
	cat p2 | ./match pc | ./pipe > p1

t6:
	cat p1 | ./match people | ./pipe > p2

