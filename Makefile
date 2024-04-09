CC = gcc
CFLAGS = -Wall -Werror

SOURCES = affichage.c deplacement_bobai.c main.c
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