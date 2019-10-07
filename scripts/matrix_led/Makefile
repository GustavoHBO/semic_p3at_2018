# sample makefile
CC = gcc
CFLAGS = -Wall -std=c11
OUTFILE = led-max7219
OBJS = eyes.o
SRCS = eyes.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS) -lbcm2835
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS) $(OUTFILE)

.PHONY : all
all : $(OUTFILE)
