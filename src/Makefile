CC=gcc
C++=g++
CFLAGS=-Wall -Wextra -pedantic -ggdb -lm -std=c99

all: main.c dct.o
	gcc $(CFLAGS) -o $@ $<

levantarBW.o: EasyBMP_1.06/levantarBW.cpp
	g++ -c EasyBMP_1.06/levantarBW.cpp
	cp EasyBMP_1.06/levantarBW.o levantarBW.o

# EasyBMP.o: EasyBMP_1.06/EasyBMP.cpp
#	g++ -c EasyBMP_1.06/EasyBMP.cpp
#	cp EasyBMP_1.06/EasyBMP.o EasyBMP.o	 

test: writers.o test.o levantarBW.o
	g++ $(CFLAGS) -lstdc++ -o $@ $< test.o levantarBW.o EasyBMP.o 

bBtest: bitBuffer.o bitsUtils.o testBBff.c
	gcc $(CFLAGS) -o bBTest testBBff.c bitBuffer.o bitsUtils.o

wrtTest: writers.o testWriters.c
	gcc $(CFLAGS) -o wrtTest testWriters.c writers.o

endTest: bitsUtils.o testEndianness.c
	gcc $(CFLAGS) -o endTest testEndianness.c bitsUtils.o

huffTest: huffman.o testHuffman.c bitBuffer.o bitsUtils.o
	gcc $(CFLAGS) -o huffTest testHuffman.c huffman.o bitBuffer.o bitsUtils.o

bitBuffer.o: bitBuffer.c bitsUtils.o
	gcc $(CFLAGS) -c -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f testbBTest wrtTest endTest huffTest
