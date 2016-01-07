#include "bitBuffer.h"
#include "bitsUtils.h"
#include "stdio.h"

void testFullBytes();
void testBitsAlternados();
void testFullBytesTakenHalf();
void testFullBytesTaken3();
void testManyBytesTaken3();
void testFullBytesTaken5();
void testDeath();
void testWriteShort();

int main() {
	// testFullBytes();
	// testFullBytesTakenHalf();
	// testFullBytesTaken3();
	// testManyBytesTaken3();
	// testFullBytesTaken5();
	// testBitsAlternados();
	// testDeath();
	testWriteShort();
	return 0;
}

void testFullBytes() {
	bitBuffer b = bB_new(5);
	unsigned char pattern = 0xF0;
	for (int i = 0; i < 5; ++i) {
		bB_write(&pattern, 8, &b);
	}
	printBuffer(&b);
	bB_free(&b);
}

void testFullBytesTaken5() {
	bitBuffer b = bB_new(6);
	//1010.1111
	unsigned char alt = 0xAF;
	unsigned char altt[2];
	altt[0] = alt;
	printf("Byte Alt: "); printBitsInByte(altt[0]); printf("\n");
	//0110.0110
	unsigned char pattern = 0x66;
	printf("WR0\n");
	bB_write(altt, 5, &b);
	for (int i = 0; i < 5; ++i) {
		printf("WR%d\n", i+1);
		bB_write(&pattern, 8, &b);
	}
	printBuffer(&b);
	bB_free(&b);
}


void testFullBytesTaken3() {
	bitBuffer b = bB_new(6);
	//1010.0000
	unsigned char alt = 0xA0;
	unsigned char altt[2];
	altt[0] = alt;
	printf("Byte Alt: "); printBitsInByte(altt[0]); printf("\n");
	//1001.1001
	unsigned char pattern = 0x99;
	printf("WR0\n");
	bB_write(altt, 3, &b);
	for (int i = 0; i < 5; ++i) {
		printf("WR%d\n", i+1);
		bB_write(&pattern, 8, &b);
	}
	printBuffer(&b);
	bB_free(&b);
}


void testManyBytesTaken3() {
	bitBuffer b = bB_new(6);
	//1010.0000
	unsigned char alt = 0xA0;
	unsigned char altt[2];
	altt[0] = alt;
	printf("Byte Alt: "); printBitsInByte(altt[0]); printf("\n");
	//1001.1001
	unsigned char pattern[3] = {0x99, 0x99, 0x99};
	printf("WR0\n");

	bB_write(altt, 3, &b);
	
	printf("WR1\n");
	bB_write(pattern, 24, &b);
	
	printf("WR2\n");
	bB_write(pattern, 16, &b);
	
	printBuffer(&b);
	bB_free(&b);
}

void testFullBytesTakenHalf() {
	bitBuffer b = bB_new(6);
	//1010.1111
	unsigned char alt = 0xAF;
	unsigned char altt[2];
	altt[0] = alt;
	printf("Byte Alt: "); printBitsInByte(altt[0]); printf("\n");
	//0110.1001
	unsigned char pattern = 0x69;
	bB_write(altt, 4, &b);
	for (int i = 0; i < 5; ++i) {
		bB_write(&pattern, 8, &b);
	}
	printBuffer(&b);
	bB_free(&b);	
}

void testBitsAlternados() {
	bitBuffer b = bB_new(5);
	// 1001.0010 0100.1001 0010.0100 1001.0010 
	unsigned char bits3[4] = {0x92, 0x49, 0x24, 0x92};
	
	// 1001.0010 01
	bB_write(bits3, 10, &b);
	
	//0010.0(000)
	unsigned char bits3_2[2] = {0x20, 0x00};
	bB_write(bits3_2, 5, &b);

	//1001.0010 0100.1(111)
	unsigned char bits3_3[2] = {0x92, 0x4F};
	bB_write(bits3_3, 13, &b);

	printBuffer(&b);
	bB_free(&b);
}

void testDeath() {
	// 1000.0100 0010.0001 0000.1000 0100.0010 0001.0000 1000.0100 0011.111s
	
	bitBuffer b = bB_new(7);
	// 1000.0(111)
	unsigned char bits1[1] = {0x87};
	bB_write(bits1, 5, &b);

	//1000.0100 0010.0001 0000.1(111)
	unsigned char bits2[3] = {0x84, 0x21, 0x0F};
	bB_write(bits2, 21, &b);

	//0000.1000 0100.0010 0001.0000 1111.1(000)
	unsigned char bits3[4] = {0x08, 0x42, 0x10, 0xF8};
	bB_write(bits3, 29, &b);

	printBuffer(&b);
	bB_free(&b);
}

void testWriteShort() {
	bitBuffer b;

	// Escribimos cosas que empiezan con 1
	b = bB_new(5);
	// 101(0.000)
	bB_write_short((unsigned short) 5, 3, &b);
	printBuffer(&b);

	// 1011.01(00)
	bB_write_short((unsigned short) 5, 3, &b);
	printBuffer(&b);

	// 1011.0111 001(0.000)
	bB_write_short((unsigned short) 25, 5, &b);
	printBuffer(&b);

	// 1011.0111 0011.0000 0000.0000 001(0.0000)
	bB_write_short((unsigned short) 0x8001, 16, &b);
	printBuffer(&b);

	// 1011.0111 0011.0000 0000.0000 0011.1111 1111.111(0)
	//                             0000.1111 1111.1111
	bB_write_short((unsigned short) 0x0FFF, 12, &b);
	printBuffer(&b);

	bB_free(&b);

	// Escribimos cosas que empiezan con 0
	b = bB_new(5);

	// 0001.11(00)
	bB_write_short((unsigned short) 7, 6, &b);
	printBuffer(&b);

	// 0001.1100 0111.1(000)
	bB_write_short((unsigned short) 15, 7, &b);
	printBuffer(&b);

	// 0001.1100 0111.1000 0000.0000 0000.1(000)
	bB_write_short((unsigned short) 1, 16, &b);
	printBuffer(&b);

	// 0001.1100 0111.1000 0000.0000 0000.1000 1000.0001
	bB_write_short((unsigned short) 0x81, 11, &b);
	printBuffer(&b);
}
