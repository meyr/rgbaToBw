#include "bmp.h"

void generateRGBTable(){
    int i;
    for(i = 0; i <= 0xff; i++){
        table_R[i] = i * 0.299;
        table_G[i] = i * 0.587;
        table_B[i] = i * 0.114;
    }
}

void before()
{
	generateRGBTable();
}

void rgbaToBw(uint32_t *pixel, int width, int height, long stride)
{
    int row, col;
    BYTE *r, *g, *b, bw;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            r = (BYTE *) pixel + 2;
            g = (BYTE *) pixel + 1;
            b = (BYTE *) pixel;
            bw = table_R[*r] + table_G[*g] + table_B[*b];
            *r = *g = *b = bw;
            pixel++;
        }
    }


}

char *getOutputImageFile()
{
	return "./pictures/01_version3.bmp";
}

void after()
{

}
