
# http://wiki.ubuntu.org.cn/%E8%B7%9F%E6%88%91%E4%B8%80%E8%B5%B7%E5%86%99Makefile:%E4%BD%BF%E7%94%A8%E5%87%BD%E6%95%B0

SRC = $(wildcard cmd_*.c)

# patter substitute cmd_math.c to math
CMD = $(patsubst cmd_%.c,%,$(SRC))

all:
	@echo making $(SRC) to $(CMD)
	gcc main.c $(SRC) -o $(CMD)

t test: all
	./$(CMD) sqrt 49
	./$(CMD) sin 1

clean:
	-rm $(CMD)
