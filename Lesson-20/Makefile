SRC = expif.c

all:
	@./delcomment < $(SRC) 2>/dev/null | ./delspace | ./expdefine 2>/dev/null  | ./expif 2>/dev/null 
