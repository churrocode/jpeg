#include <stdio.h>
#include "typedefs.h"
#include "bitBuffer.h"

extern void initialize_tables_bw(); extern dByte Y_DC_HUFFCODE[]; extern byte Y_DC_HUFFLENGTH[]; extern int length(unsigned short);

extern void encode_8x8DC(double8x8* coefs, double prevDC, dByte* huffcode, byte* hufflength, bitBuffer* buffer);



void basicDC_test() {
	// Y_DC_LENGTHS[16] = {0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0}
	// Y_DC_HUFFVALS[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	// 0 -> 00 		 		0 	2

	// 1 -> 010			 	2	3
	// 2 -> 011				3	3
	// 3 -> 100				4	3
	// 4 -> 101 			5	3
	// 5 -> 110 			6	3

	// 6 -> 1110 			14	4
	// 7 -> 11110 			30	5
	// 8 -> 111110 			62	6
	// 9 -> 1111110 		126	7
	//10 -> 11111110 		254 8
	//11 -> 111111110       510	9
	initialize_tables_bw();
	int i = 0;
	for (; i < 12; ++i) {
		printf("%d \t %d \t %d\n", i, Y_DC_HUFFCODE[i], Y_DC_HUFFLENGTH[i]);
	}
}

void DCEncode_test() {
	initialize_tables_bw();
	bitBuffer  buff = bB_new(5);
	double8x8 mDC = {
		{509, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};
	// tiene que encodear el 0.
	// O sea: 0, X. O sea: 00(00.00 ....)
	encode_8x8DC(&mDC, 509, Y_DC_HUFFCODE, Y_DC_HUFFLENGTH, &buff);
	// Ponemos unos 1s para que se note, O sea: 00(11.1111 ...)
	bB_write_short(0xFFFF, 6, &buff);
	printBuffer(&buff);
	bB_free(&buff);

	buff = bB_new(5);
	// tiene que encodear 9, 509. O sea: 1111110 111111101
	// O sea: 1111.1101 1111.1101 (......)
	encode_8x8DC(&mDC, 0, Y_DC_HUFFCODE, Y_DC_HUFFLENGTH, &buff);
	printBuffer(&buff);
	bB_free(&buff);

	double8x8 mDCNeg = {
		{-509, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};
	// tiene que encodear 9, -509. O sea: 1111110 000000010
	// O sea: 1111.1100 0000.0010 (......)
	buff = bB_new(5);
	encode_8x8DC(&mDCNeg, 0, Y_DC_HUFFCODE, Y_DC_HUFFLENGTH, &buff);
	printBuffer(&buff);
	bB_free(&buff);
}

void length_test() {
	unsigned short n = 0;
	printf("%d, %d\n", length(n), 0);
	n = 1;
	printf("%d, %d\n", length(n), 1);
	n = 2;
	printf("%d, %d\n", length(n), 2);
	n = 4;
	printf("%d, %d\n", length(n), 3);
	n = 8;
	printf("%d, %d\n", length(n), 4);
	n = 10;
	printf("%d, %d\n", length(n), 4);
	n = 15;
	printf("%d, %d\n", length(n), 4);
	n = 16;
	printf("%d, %d\n", length(n), 5);
	n = 22;
	printf("%d, %d\n", length(n), 5);
	n = 32;
	printf("%d, %d\n", length(n), 6);
	n = 68;
	printf("%d, %d\n", length(n), 7);
	n = 128;
	printf("%d, %d\n", length(n), 8);
	n = 255;
	printf("%d, %d\n", length(n), 8);
	n = 256;
	printf("%d, %d\n", length(n), 9);
	n = 300;
	printf("%d, %d\n", length(n), 9);
	n = 512;
	printf("%d, %d\n", length(n), 10);
	n = 800;
	printf("%d, %d\n", length(n), 10);
	n = 2048;
	printf("%d, %d\n", length(n), 12);
	n = 3000;
	printf("%d, %d\n", length(n), 12);
	n = 4095;
	printf("%d, %d\n", length(n), 12);
	n = 4096;
	printf("%d, %d\n", length(n), 13);
	n = 10000;
	printf("%d, %d\n", length(n), 14);
	n = 0x7AAA;
	printf("%d, %d\n", length(n), 15);
	n = 0x8000;
	printf("%d, %d\n", length(n), 16);
	n = 0xFFFF;
	printf("%d, %d\n", length(n), 16);
}


int main(){
	// basicDC_test();
	// length_test();
	DCEncode_test();
	return 0;
}
