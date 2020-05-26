#include "bmp.h"

void before()
{
}

void rgbaToBw(uint32_t *data, int width, int height, long stride)
{
    int32_t row, col;
    uint8_t *r, *g, *b, q_err, q_error_right, *q_error_array, *q_error;
    uint32_t bw, q_bw, pixel_index;

    q_error_array = calloc(1, width + 2);
    q_error = q_error_array + 1;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            r = (uint8_t *) data + 2;
            g = (uint8_t *) data + 1;
            b = (uint8_t *) data;
            bw = (*r * 0.299) + (*g * 0.587) + (*b * 0.114);
            bw += q_error[col];
	    q_bw = bw & 0x80 ? 0xff : 0x00;
	    //q_bw = bw & 0xf0;
	    q_err = bw - q_bw;
	    q_error[col - 1] = (q_err * 3) >> 4;
	    if(col == 0)
		    q_error[col] = (q_err * 8) >> 4;
	    else
		    q_error[col] = (q_err * 5) >> 4;
	    q_error[col + 1] = q_err * 8 >> 4;

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
