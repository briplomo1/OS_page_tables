CC = gcc

CFLAGS = -Wall -Wextra -g

# Targets
all: part1 part2

part1: part1.c translate.c
	$(CC) $(CFLAGS) -o part1 part1.c translate.c

part2: part2.c translate.c pagetable.c phypages.c
	$(CC) $(CFLAGS) -o part2 part2.c translate.c pagetable.c phypages.c

clean:
	rm -f part1 part2 *.o part1-output part2-output

.PHONY: all clean