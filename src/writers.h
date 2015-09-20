#ifndef JPEG_WRITERS
#define JPEG_WRITERS

#include <stdlib.h>
#include <stdio.h>
#include "typedefs.h"

#include "huffman.h"
#include "dct.h"

#define Y_identifier 0
#define DC_Selector 0
#define AC_Selector 1

void write_sof_bw(FILE* f, int height, int width);
void write_dht_bw(FILE* f, const unsigned char DC_ACSelector, const unsigned char Y_UVSelector, 
					const unsigned char* lengths, 
					const unsigned char* vals, const unsigned char vals_size);
void write_dqt_bw(FILE* f, const quant_matrix* qMatrix);
void write_sos_bw(FILE* f);
void write_file_bw(FILE* f, int height, int width, const quant_matrix* qMatrix);

#endif