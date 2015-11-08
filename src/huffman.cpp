#include "huffman.h"



// Y_DC_LENGTHS[i-1] = # codigos de long i (BITS en el apunte) (para el DC de Y)
const byte Y_DC_LENGTHS[16] = {0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0};

// Y_DC_HUFFVALS -> los valores ordenados segun la longitud del codigo que les toco (para el DC de Y)
#define Y_DC_HUFFVALS_SIZE 12;
const byte Y_DC_HUFFVALS[Y_DC_HUFFVALS_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

/*const*/ dByte Y_DC_HUFFCODE[Y_DC_HUFFVALS_SIZE];
/*const*/ byte Y_DC_HUFFLENGTH[Y_DC_HUFFVALS_SIZE];

// analogo para AC
#define Y_AC_HUFFVALS_SIZE 160;
const byte Y_AC_LENGTHS[16] = {0,2,1,3,3,2,4,3,5,5,4,4,0,0,1,125};
const byte Y_AC_HUFFVALS[Y_AC_HUFFVALS_SIZE] =  {
									12,3,0,4,17,5,18,33,49,65,6,
									19,81,97,7,34,113,20,50,129,145,
									161,8,35,66,177,193,21,82,209,
									36,51,98,114,130,9,10,22,23,24,
									25,26,37,38,39,40,41,42,52,53,
									54,55,56,57,58,67,68,69,70,71,
									72,73,74,83,84,85,86,87,88,89,
									90,99,100,101,102,103,104,105,106,115,
									116,117,118,119,120,121,122,131,132,133,
									134,135,136,137,138,146,147,148,149,150,
									151,152,153,154,162,163,164,165,166,167,
									168,169,170,178,179,180,181,182,183,184,
									185,186,194,195,196,197,198,199,200,201,
									202,210,211,212,213,214,215,216,217,218,
									225,226,227,228,229,230,231,232,233,234,
									241,242,243,244,245,246,247,248,249,250};
/*const*/ dByte Y_AC_HUFFCODE[256];
/*const*/ byte Y_AC_HUFFLENGTH[256];


//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡HAY QUE TESTEAR ESTO!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



// A partir de _LENGTHS y HUFFVALS construye _HUFFCODE y _HUFFLENGTH
// _HUFFCODE[v] = código que le tocó al valor v.
// _HUFFLENGTH[v] = longitud del código que le tocó al valor v.
void build_huff_code_table ( const byte* lengths, const byte lengths_size, const byte* huffvals,
							dByte* huffocde, byte* hufflength ) {
	int cnt  = 0;
	dByte baseForLength, lastCode = 0;
	int lastLength = 0;
	for (int i = 0;  i < lengths_size; ++i) {
		byte currentLength = lengths[i];
		if (currentLength > 0) {
			baseForLength = lastCode << (currentLength - lastLength);
			for (int l = 0; l < currentLength; ++l) {
				byte val = huffvals[cnt];
				cnt++;
				hufflength[val] = currentLength;
				lastCode = baseForLength + l;
				huffvals[val] = lastCode;
			}
			lastLength = currentLength;
		}
	}
}


void initialize_tables_bw(){
	if (!initialized) {
		build_huff_code_table(Y_AC_LENGTHS, 16, Y_AC_HUFFVALS, Y_AC_HUFFCODE, Y_AC_HUFFLENGTH);
		build_huff_code_table(Y_DC_LENGTHS, 16, Y_DC_HUFFVALS, Y_DC_HUFFCODE, Y_DC_HUFFLENGTH);
		initialized = 1;
	}
}
