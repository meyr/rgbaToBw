#include "bmp.h"

void generateRGBTable()
{
	int i;
	for (i = 0; i <= 0xff; i++) {
		table_R[i] = i * 0.299;
		table_G[i] = i * 0.587;
		table_B[i] = i * 0.114;
	}
}

void before()
{
	generateRGBTable();
}

void rgbaToBw(uint32_t *data, int width, int height, long stride)
{
	int row, col;
	uint32_t pixel, r, g, b, a, bw;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			pixel = data[col + row * stride / 4];
			a = (pixel >> 24) & 0xff;
			r = (pixel >> 16) & 0xff;
			g = (pixel >> 8) & 0xff;
			b = pixel & 0xff;
			bw = (uint32_t)(table_R[r] + table_G[g] + table_B[b]);
			data[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
		}
	}
}

char *getOutputImageFile()
{
	return "./pictures/01_version1.bmp";
}

void after()
{

}
