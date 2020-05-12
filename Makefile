CC = gcc
CFLAGS = -g -ggdb -O2 -Wall -lm -ftree-vectorize  -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
EXECUTABLE = main main_v1 main_v2 main_v3 main_v4 main_v5 main_v6
OBJS = main.c bmp.c

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN

main_v1: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION1

main_v2: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION2

main_v3: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION3

main_v4: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION4

main_v5: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION5

main_v6: $(OBJS) neon_dither.c
	$(CC) $(CFLAGS) $^ -o $@ -DORIGIN -DVERSION6

default:
	make clean
	make main
	make main_v1
	make main_v2
	make main_v3
	make main_v4
	make main_v5
	make main_v6

run:
	./main
	./main_v1
	./main_v2
	./main_v3
	./main_v4
	./main_v5
	./main_v6

clean:
	rm -f $(EXECUTABLE) *.o perf.* ./pictures/01_*.bmp

