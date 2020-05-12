CC = gcc
ARMGCC = arm-linux-gnueabihf-gcc 
CFLAGS = -g -ggdb -O2 -Wall -lm -ftree-vectorize  
LDFLAGS = -lm
NEON_CFLAGS = -mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
EXECUTABLE = $(shell find ./ -maxdepth 1 -executable -type f)
OBJS = main.c bmp.c

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

dither: $(OBJS) dither.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE) *.o perf.* ./pictures/01_*.bmp

