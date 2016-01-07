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

// escribe n en los primeros (mas a la izq) length bits de un dByte (de corrido, sin endianness)
dByte write_with_length(unsigned int n, int length) {
	if (length <= 8) {
		return ((dByte) n) << (8 - length);
	} else {
		// llevar para que empieze en el bit más significativo
		dByte todoALaDer = ((dByte) n) << (16-length);
		dByte h, l = 0;

		// dar vuelta el endianness
		h = (todoALaDer & 0xFF00) >> 8;
		l = (todoALaDer & 0x00FF) << 8;
		return h|l;
	}
}

// El test esta en testHuffman.c
int length(dByte num) {
	int len = 16;
	dByte mask;
	for (mask = 0x8000; mask != 0; mask >>= 1) {
		if ((num & mask) != 0) {
			break;
		} else {
			len--;
		}
	}
	return len;
}
