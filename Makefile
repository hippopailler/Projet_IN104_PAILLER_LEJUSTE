CC = gcc
CFLAGS = 

SOURCES = affichage.c position_bobai.c position_pion.c victoire.c ordi_alea.c IA_bobail_up.c main.c
OBJS = $(SOURCES:.c=.o)

EXECUTABLE = main.x

.PHONY: all clean realclean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXECUTABLE)