#include "huffman.h"


int huffman_initialized = 0;

//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡
//¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡HAY QUE TESTEAR ESTO!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



// A partir de _LENGTHS y HUFFVALS construye _HUFFCODE y _HUFFLENGTH
// _HUFFCODE[v] = código que le tocó al valor v.
// _HUFFLENGTH[v] = longitud del código que le tocó al valor v.
void build_huff_code_table ( const byte* lengths, const byte lengths_size, const byte* huffvals,
							dByte* huffcode, byte* hufflength ) {
	int cnt  = 0;
	dByte baseForLength, lastCode = 0;
	int lastLength = 0;
	int i, l;
	for (i = 0;  i < lengths_size; ++i) {
		byte cuantosByLength = lengths[i];
		if (cuantosByLength > 0) {
			int currentLength = i+1;
			baseForLength = (lastCode+1) << (currentLength - lastLength) ;
			for (l = 0; l < cuantosByLength; ++l) {
				byte val = huffvals[cnt];
				cnt++;
				hufflength[val] = currentLength;
				lastCode = baseForLength + l;
				huffcode[val] = lastCode;
			}
			lastLength = currentLength;
		}
	}
}


void initialize_tables_bw(){
	if (! huffman_initialized) {
		build_huff_code_table(Y_AC_LENGTHS, 16, Y_AC_HUFFVALS, Y_AC_HUFFCODE, Y_AC_HUFFLENGTH);
		build_huff_code_table(Y_DC_LENGTHS, 16, Y_DC_HUFFVALS, Y_DC_HUFFCODE, Y_DC_HUFFLENGTH);
		huffman_initialized = 1;
	}
}














