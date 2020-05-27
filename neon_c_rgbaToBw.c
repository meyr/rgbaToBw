#include "bmp.h"
#include "arm_neon.h"

void before()
{

}

void after()
{

}

char *getOutputImageFile()
{
	return "./pictures/01_version_neon_c.bmp";
}

void rgbaToBw(uint32_t *pixel, int width, int height, long stride)
{
	int i, j, n;
	uint8_t *dest;
	uint8_t *src = pixel;
	uint8x8_t rfac = vdup_n_u8(77);	// eight packed u8
	uint8x8_t gfac = vdup_n_u8(151);	// Duplicate vector element to vector or scalar
	uint8x8_t bfac = vdup_n_u8(28);
	uint8x8_t bw_mask = vdup_n_u8(0x80);
	uint8x8_t bw;
	n = width * height / 8;
	dest = calloc(1, sizeof(char) * 8);

	for (i = 0; i < n; i++) {
		uint16x8_t  temp;			//  eight packed u16
		uint8x8x4_t rgb  = vld4_u8(src);	//
		uint8x8_t result;

		temp = vmull_u8(rgb.val[0],      rfac);
		temp = vmlal_u8(temp, rgb.val[1], gfac);
		temp = vmlal_u8(temp, rgb.val[2], bfac);

		result = vshrn_n_u16(temp, 8);
		bw = vtst_u8(result, bw_mask);
		vst1_u8(dest, bw);

		for (j = 0; j < 8; j++)
			src[4 * j] = src[ 4 * j + 1] = src[ 4 * j + 2] = dest[j];
		src  += 8 * 4;
	}
}

