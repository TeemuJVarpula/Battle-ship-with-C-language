CC = gcc # Compiler.
CFLAGS = -pedantic -Wall -std=c99
# LDFLAGS = -lm # Linker flags.
DEPS = main.h field.h shoot.c# Dependencies (includes).
OBJS = main.o field.o shoot.o # Object files.
EXE = laivanupotus # Executable.

EXE: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXE)