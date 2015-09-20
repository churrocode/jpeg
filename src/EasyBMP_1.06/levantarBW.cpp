#ifndef BMP2BW
#define BMP2BW

#include "EasyBMP.h"
#include <stdlib.h>


extern "C" unsigned char* levantarBW(const char* filename);

unsigned char* levantarBW(const char* filename) {
	BMP img;
	img.ReadFromFile(filename);
	int ancho = img.TellWidth(); int alto = img.TellHeight();
	unsigned char * bitmap_matrix = (unsigned char *) malloc(ancho*alto);
	int i, j;
	for (i = 0; i < ancho; ++i) {
		for (j = 0; j < alto; ++j) {
			// RGBAPixel px = img.GetPixel(i,j);
			*(bitmap_matrix + ancho * i + j) = (unsigned char) (img.GetPixel(i,j).Red * 0.2989 + img.GetPixel(i,j).Green * 0.5870 + img.GetPixel(i,j).Blue * 0.1140);
		}
	}
	return bitmap_matrix;
}


#endif
