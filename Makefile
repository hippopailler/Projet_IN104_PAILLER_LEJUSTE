CC = gcc
CFLAGS = -Wall -Werror

SOURCES = affichage.c position_bobai.c position_pion.c victoire.c main.c
OBJS = $(SOURCES:.c=.o)

EXECUTABLE = main.x

.PHONY: all clean realclean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXECUTABLE)