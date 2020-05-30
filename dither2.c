#include "bmp.h"

void before()
{
}

void rgbaToBw(uint32_t *data, int width, int height, long stride)
{
	int32_t row, col;
	uint8_t *r, *g, *b;
	uint32_t q_bw, pixel_index;
	int32_t bw;
	int8_t q_err, q_error_right, *q_error_array, *q_error;

	q_error_array = calloc(1, width + 2);
	q_error = q_error_array + 1;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r = (uint8_t *) data + 2;
			g = (uint8_t *) data + 1;
			b = (uint8_t *) data;
			bw = ((*r * 153) + (*g * 301) + (*b * 58)) >> 9;
			if (row != 0)
				bw += q_error[col];
			if(bw >= 0xf0) {
			    q_bw = 0xf0;
			    q_err = 0;
			} else if(bw <= 0) {
			    q_bw = 0x0;
			    q_err = 0;
			} else {
				q_bw = bw & 0x80 ? 0xf0 : 0x00;
				q_err = bw - q_bw;
			}

			q_error[col - 1] = q_err >> 2;		// 4
			if (col == 0)
				q_error[col] = q_err >> 1;	// 8
			else
				q_error[col] = q_err >> 2;	// 4
			q_error[col + 1] = q_err >> 1;		// 8

			*r = *g = *b = q_bw;

			data++;
		}
	}

}

char *getOutputImageFile()
{
	return "./pictures/01_version_dither2.bmp";
}

void after()
{

}
