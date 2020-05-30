#include "bmp.h"

void before()
{
}

void rgbaToBw(uint32_t *data, int width, int height, long stride)
{
	int32_t row, col;
	uint8_t *r, *g, *b, i;
	uint32_t q_bw, pixel_index;
	int32_t bw;
	int8_t q_err, q_error_right, *q_error_array[3], *q_error_p, *q_error_c, *q_error_n, *err_coor[3];

	for (i = 0; i < 3; i++)
		q_error_array[i] = calloc(1, width + 2);
	q_error_p = q_error_array[0];
	q_error_c = q_error_array[1] + 1;
	q_error_n = q_error_array[2] + 2;
	err_coor[0] = q_error_array[0] + 1;
	err_coor[1] = q_error_array[1] + 1;
	err_coor[2] = q_error_array[2] + 1;


	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r = (uint8_t *) data + 2;
			g = (uint8_t *) data + 1;
			b = (uint8_t *) data;
			bw = ((*r * 153) + (*g * 301) + (*b * 58)) >> 9;
			if (row != 0) {
				bw += err_coor[0][col] + err_coor[1][col] + err_coor[2][col];
			}
			if(bw >= 0xf0) {
			    q_bw = 0xf0;
			    q_err = 0;
			} else if(bw <= 0x10) {
			    q_bw = 0x0;
			    q_err = 0;
			} else {
			      q_bw = bw & 0x80 ? 0xf0 : 0x00;
			      q_err = bw - q_bw;
			}

			q_error_p[col] = q_err >> 2;		// 4
			q_error_c[col] = q_err >> 2;		// 4
			q_error_n[col] = q_err >> 1;		// 8

			*r = *g = *b = q_bw;

			data++;
		}
	}

}

char *getOutputImageFile()
{
	return "./pictures/01_version_dither3.bmp";
}

void after()
{

}
