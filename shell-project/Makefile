CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = main.c shell.c
OBJ = $(SRC:.c=.o)

shell: $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f shell $(OBJ)
	
