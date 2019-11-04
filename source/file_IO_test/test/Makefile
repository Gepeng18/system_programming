src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

all:$(obj)

CFLAGES=-Wall -g

$(obj):%:%.c
	gcc $< -o $@ $(CFLAGES)

clean:
	-rm -rf $(obj)

.PHONY:clean all
