#include "bitBuffer.h"
#include <stdlib.h>
#include <stdio.h>


// typedef struct {
// 	int size;
// 	int takenBits;
// 	int byteToWriteInto;
// 	unsigned char* buff;
// } bitBuffer;

bitBuffer bB_new(int size) {
	bitBuffer bB = {size, 0, 0, (unsigned char*) calloc(1, size)}; 
	return bB;
}

void bB_free(bitBuffer* bb) {
	free(bb->buff);
}

// size dice cuantos BITS tengo que copiar al buffer
// start apunta al byte donde empiezan (desde el bit7) los bits que hay que copiar 
void bB_write(unsigned char* start, int writeSize, bitBuffer* buffer) {
	int remainingBits = writeSize;
	int takenBitsInLastByte = buffer->takenBits;
	// cuantos bytes DE START[] copie
	int writtenBytes = 0;

	// voy a copiar bytes enteros de START
	if (takenBitsInLastByte > 0) {
		// a cada byte de start[] lo tengo que partir en dos:
		// la primera parte (desde la izq) debe completar el ultimo byte del buffer
		// la segunda va a la primera parte del siguiente byte del buffer
		while (remainingBits > 8) {
			unsigned char byteToWrite = start[writtenBytes];
			// XXX0.0000 => 1010.1010 >> 3 => 0001.0101 (010) 
			buffer->buff[buffer->byteToWriteInto] |= (byteToWrite >> takenBitsInLastByte);
			buffer->byteToWriteInto++;
			// (1010.1)010 => 1010.1010 << 5 => 010 0.0000 => XXX0.0000  
			buffer->buff[buffer->byteToWriteInto] |= (byteToWrite << (8 - takenBitsInLastByte));
			writtenBytes++; 
			remainingBits -= 8;
		}
	} else {
		// el caso lindo, copio byte a byte (no es lo mejor, pero BUEH)
		while (remainingBits > 8) {
			buffer->buff[buffer->byteToWriteInto] = start[writtenBytes];
			buffer->byteToWriteInto++;
			writtenBytes++;
			remainingBits -= 8;
		}
	}

	//me quedo por lo menos un bit
	if (remainingBits > 0) {
		// el ultimo byte
		unsigned char byteToWrite = start[writtenBytes];
		// printf("Byte to write Bfr: "); printBitsInByte(byteToWrite); printf("\n");
		byteToWrite >>= 8 - remainingBits;
		byteToWrite <<= 8 - remainingBits;
		// printf("Byte to write Aft: "); printBitsInByte(byteToWrite); printf("\n");
		if (takenBitsInLastByte + remainingBits > 8) {
			// no entran en el ultimo byte del buffer
			buffer->buff[buffer->byteToWriteInto] |= (byteToWrite >> takenBitsInLastByte);
			buffer->byteToWriteInto++;
			buffer->buff[buffer->byteToWriteInto] |= (byteToWrite << (8 - takenBitsInLastByte));
		} else {
			//los pongo a continuacion
			buffer->buff[buffer->byteToWriteInto] |= byteToWrite >> takenBitsInLastByte;
			if (takenBitsInLastByte + remainingBits == 8) {
				buffer->byteToWriteInto++;
			}
		}
		buffer->takenBits = (takenBitsInLastByte + remainingBits) % 8;
		remainingBits = 0;
	}
} 

void printBuffer(const bitBuffer* b) {
	for (int i = 0; i < b-> size; ++i) {
		printBitsInByte(b->buff[i]);
	}
	printf("\n\n");
}

unsigned char printBitsInByte(unsigned char byte) {
	//unsigned unsigned char masks[8] = {128,64,32,16,8,4,2,1};
	for (int i = 7; i >= 0; --i) {
		//unsigned char uno = 1;
		printf("%d ", (byte & ((unsigned char) 1 << i))>> i );
		if (i == 4)printf(". "); 
	}
	printf("  ");
	return byte;
}




