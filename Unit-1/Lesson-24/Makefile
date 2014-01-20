URL = www.lumit.org
KEY = lumit

all:
	gcc parser.c -o parser
	gcc getkey.c -o getkey
	gcc gettext.c -o gettext

debug:
	gcc parser.c -o parser -DDEBUG
	gcc getkey.c -o getkey -DDEBUG
	gcc gettext.c -o gettext -DDEBUG

t1:
	curl "http://www.lumit.org/LASO"	
	
t2:
	curl "http://weibo.com/limingth" | ./parser p

t3:
	curl $@ | ./parser a | ./getkey href 2> tmp

t4:
	curl $(URL) | ./parser p | ./gettext $(KEY) 2> tmp

