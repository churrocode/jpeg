#include <stdio.h>
#include "typedefs.h"

extern void initialize_tables_bw(); extern dByte Y_DC_HUFFCODE[]; extern byte Y_DC_HUFFLENGTH[];

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

int main(){
	basicDC_test();
	return 0;
}
