#include <stdio.h>
#include "typedefs.h"

extern void initialize_tables_bw(); extern dByte Y_DC_HUFFCODE[]; extern byte Y_DC_HUFFLENGTH[]; extern int length(unsigned short);

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
	length_test();
	return 0;
}