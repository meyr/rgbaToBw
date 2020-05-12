CC = gcc
ARMGCC = arm-linux-gnueabihf-gcc 
CFLAGS = -g -ggdb -O2 -Wall -lm -ftree-vectorize  
LDFLAGS = -lm
NEON_CFLAGS = -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
EXECUTABLE = main main_v1 main_v2 main_v3 main_v4 main_v5 neon_c
OBJS = main_.c bmp_.c

main: $(OBJS) rgbaToBw.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main_v1: $(OBJS) rgbaToBw1.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main_v2: $(OBJS) rgbaToBw2.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main_v3: $(OBJS) rgbaToBw3.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main_v4: $(OBJS) rgbaToBw4.c
	$(ARMGCC) $(CFLAGS) $(NEON_CFLAGS) $^ -o $@ $(LDFLAGS)

main_v5: $(OBJS) rgbaToBw5.c
	$(ARMGCC) $(CFLAGS) $(NEON_CFLAGS) $^ -o $@ $(LDFLAGS)

neon_c: $(OBJS) neon_c_rgbaToBw.c
	$(ARMGCC) $(CFLAGS) $(NEON_CFLAGS) $^ -o $@ $(LDFLAGS)

default:
	make clean
	make main
	make main_v1
	make main_v2
	make main_v3
	make main_v4
	make main_v5
	make neon_c

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

