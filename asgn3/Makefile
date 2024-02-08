#Makefile
#Author : Debi Majumdar
#compiling programs

CC	= clang
CFLAGS	= -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS	= -lm
EXEC	= xd
OBJS	= xd.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(EXEC) $(OBJS)
format:
	clang-format -i -style=file *[ch]

.PHONY: all clean format
	# bash runner.sh
