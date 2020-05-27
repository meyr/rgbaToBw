#include "bmp.h"

void before()
{
}

void rgbaToBw(uint32_t *data, int width, int height, long stride)
{
	int row, col;
	BYTE *r, *g, *b, bw;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r = (BYTE *) data + 2;
			g = (BYTE *) data + 1;
			b = (BYTE *) data;
			bw = (*r * 0.299) + (*g * 0.587) + (*b * 0.114);
			*r = *g = *b = bw;
			data++;
		}
	}

}

char *getOutputImageFile()
{
	return "./pictures/01_version2.bmp";
}

void after()
{

}
