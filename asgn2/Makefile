CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = hangman
HEADERS = hangman_helpers.h

all: $(EXEC)

$(EXEC): $(EXEC).o hangman_helpers.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
tests: test_functionality test_helpers

test_functionality: test_functionality.sh
              ./test_functionality.sh
test_helpers: test_helpers.c hangman_helpers.o
           $(CC) $(CFLAGS) $< hangman_helpers.o -o test_helpers
          ./test_helpers
