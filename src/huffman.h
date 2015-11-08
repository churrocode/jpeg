#ifndef JPEG_HUFFMAN
#define JPEG_HUFFMAN

#include "typedefs.h"


// Y_DC_LENGTHS[i-1] = # codigos de long i (BITS en el apunte) (para el DC de Y)
const unsigned char Y_DC_LENGTHS[16];
// Y_DC_HUFFVALS[i-1] -> los valores ordenados segun la longitud del codigo que les toco (para el DC de Y)
const unsigned char Y_DC_HUFFVALS_SIZE;
const unsigned char Y_DC_HUFFVALS[12];


// analogo para AC
const unsigned char Y_AC_LENGTHS[16];
const unsigned char Y_AC_HUFFVALS_SIZE;
const unsigned char Y_AC_HUFFVALS[160];

void initialize_tables_bw();
int initialized = 0;

#endif
