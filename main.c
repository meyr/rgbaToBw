#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
	char openfile[] = "./pictures/01.bmp";

	BMP *bmp = (BMP*) malloc(sizeof(BMP));
	clock_t start = 0;
	clock_t end = 0;
	int loop = 50;
	int i;
	//uint8_t *result;

	/* Load the image and print the infomation */
	bmpLoad(bmp, openfile);
	long stride = bmp->width * 4;
	bmpPrint(bmp);

	/* RGBA to BW */
	before();
	start = clock();
	for (i = 0; i < loop; i++) {
		rgbaToBw(bmp->data, bmp->width, bmp->height, stride);
	}
	end = clock();
	after();

	printf("Execution time of rgbaToBw() : %lf \n", ((double)(end - start)) / CLOCKS_PER_SEC / loop);
	bmpSave(bmp, getOutputImageFile());
	bmpFreeBuf(bmp);
	free(bmp);

	return 0;
}
