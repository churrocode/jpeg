#include "bitsUtils.h"
#include <stdio.h>
#include "typedefs.h"

byte printBitsInByte(byte byte) {
	//unsigned unsigned char masks[8] = {128,64,32,16,8,4,2,1};
	for (int i = 7; i >= 0; --i) {
		//unsigned char uno = 1;
		printf("%d ", (byte & ((unsigned char) 1 << i))>> i );
		if (i == 4)printf(". ");
	}
	printf("  ");
	return byte;
}

dByte printBitsInDByte(dByte db) {
	printBitsInByte(*((unsigned char*) &db));
	printf("\t");
	printBitsInByte(*(((unsigned char*) &db)+1));
	return db;
}
