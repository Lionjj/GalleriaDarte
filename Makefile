CC=gcc
CFLAGS=-Wall -std=c99
CFILES=main.c $(wildcard lib/*.c dataType/*/*.c)
OBJFILES=$(CFILES:.c=.o)
OUT=output

$(OUT): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT) $(OUT).exe