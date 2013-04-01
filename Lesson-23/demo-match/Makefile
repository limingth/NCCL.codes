#TIME = `date +%x`
TIME = $(shell date '+%H-%M')

all:
	gcc fivechess.c -o demo
	gcc log1.c -o log1
	gcc log2.c -o log2
	gcc replay.c -o replay

fifo:
	mkfifo p1 p2

rmlog:
	-rm *.log
	-rm *.log.html

t1:
	echo $(TIME)
	-rm m.log m.log.html
	ln -s $(TIME).log m.log	
	ln -s $(TIME).log.html m.log.html	
	-rm p1 p2
	mkfifo p1 p2
	cat p2 | ./demo machine | ./log1 $(TIME).log > p1

t2:
	cat p1 | ./demo man | ./log2 $(TIME).log > p2
	cat match0.html m.log.html match1.html > match-record.html

re:
	./replay m.log

test:
	make t1 &
	sleep 1
	make t2

http:
	python -m SimpleHTTPServer
