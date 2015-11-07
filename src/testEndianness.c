#include <stdio.h>
#include "bitsUtils.h"

void basicEndianness_test() {
	printf("un short mide %d bytes.\n", (int) sizeof(unsigned short));
	dByte i =0xFF00;
	printBitsInDByte(i);
	printf("\n");
	printf("Array Test\n");
	dByte A[3] = {0xFF00, 0xEE11, 0xDD22};
	int offs = 0;
	for (; offs < 3*sizeof(unsigned short); ++offs) {
		printBitsInByte(*(((unsigned char*) A) + offs));
		printf("\n");
	}
	printf("Test shift\n");
	i = 1;
	int j = 0;
	for (; j <= 16; j++) {
		printf("%d: \t", j);
		printBitsInDByte(i << j);
		printf("\n");
	}
}

// output: 
// un short mide 2 bytes.
// 0 0 0 0 . 0 0 0 0   	1 1 1 1 . 1 1 1 1   
// Array Test
// 0 0 0 0 . 0 0 0 0   
// 1 1 1 1 . 1 1 1 1   
// 0 0 0 1 . 0 0 0 1   
// 1 1 1 0 . 1 1 1 0   
// 0 0 1 0 . 0 0 1 0   
// 1 1 0 1 . 1 1 0 1   
// Test shift
// 0: 	0 0 0 0 . 0 0 0 1   	0 0 0 0 . 0 0 0 0   
// 1: 	0 0 0 0 . 0 0 1 0   	0 0 0 0 . 0 0 0 0   
// 2: 	0 0 0 0 . 0 1 0 0   	0 0 0 0 . 0 0 0 0   
// 3: 	0 0 0 0 . 1 0 0 0   	0 0 0 0 . 0 0 0 0   
// 4: 	0 0 0 1 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
// 5: 	0 0 1 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
// 6: 	0 1 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
// 7: 	1 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
// 8: 	0 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 1   
// 9: 	0 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 1 0   
// 10: 	0 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 1 0 0   
// 11: 	0 0 0 0 . 0 0 0 0   	0 0 0 0 . 1 0 0 0   
// 12: 	0 0 0 0 . 0 0 0 0   	0 0 0 1 . 0 0 0 0   
// 13: 	0 0 0 0 . 0 0 0 0   	0 0 1 0 . 0 0 0 0   
// 14: 	0 0 0 0 . 0 0 0 0   	0 1 0 0 . 0 0 0 0   
// 15: 	0 0 0 0 . 0 0 0 0   	1 0 0 0 . 0 0 0 0   
// 16: 	0 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0 



void write_with_length_test_ones() {
	int length = 1;
	int n = 2;
	while (n <= 0x10000) {
		printf("%4x \t", n-1); printBitsInDByte(write_with_length(n-1, length)); printf("\n");
		n *= 2; length++;
	}
}

void write_with_length_test_general() {
	// 1101.0010 001X.XXXX 
	printf("\n1 1 0 1 . 0 0 1 0\t0 0 1 X . X X X X\n"); printBitsInDByte(write_with_length(0x691, 11)); printf("\n");
	// 1100.1110 0011.11XX 
	printf("\n1 1 0 0 . 1 1 1 0\t0 0 1 1 . 1 1 X X\n"); printBitsInDByte(write_with_length(0x338F, 14)); printf("\n");
}


//  output esperado: 
//    1 	1 0 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
//    3 	1 1 0 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
//    7 	1 1 1 0 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
//    f 	1 1 1 1 . 0 0 0 0   	0 0 0 0 . 0 0 0 0   
//   1f 	1 1 1 1 . 1 0 0 0   	0 0 0 0 . 0 0 0 0   
//   3f 	1 1 1 1 . 1 1 0 0   	0 0 0 0 . 0 0 0 0   
//   7f 	1 1 1 1 . 1 1 1 0   	0 0 0 0 . 0 0 0 0   
//   ff 	1 1 1 1 . 1 1 1 1   	0 0 0 0 . 0 0 0 0   
//  1ff 	1 1 1 1 . 1 1 1 1   	1 0 0 0 . 0 0 0 0   
//  3ff 	1 1 1 1 . 1 1 1 1   	1 1 0 0 . 0 0 0 0   
//  7ff 	1 1 1 1 . 1 1 1 1   	1 1 1 0 . 0 0 0 0   
//  fff 	1 1 1 1 . 1 1 1 1   	1 1 1 1 . 0 0 0 0   
// 1fff 	1 1 1 1 . 1 1 1 1   	1 1 1 1 . 1 0 0 0   
// 3fff 	1 1 1 1 . 1 1 1 1   	1 1 1 1 . 1 1 0 0   
// 7fff 	1 1 1 1 . 1 1 1 1   	1 1 1 1 . 1 1 1 0   
// ffff 	1 1 1 1 . 1 1 1 1   	1 1 1 1 . 1 1 1 1 


int main() {
	//basicEndianness_test();
	// write_with_length_test_ones();
	write_with_length_test_general();
	return 0;
}





