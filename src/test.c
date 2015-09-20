#include "writers.h"
#include "typedefs.h"
#include <stdio.h>
//#include "EasyBMP_1.06/levantarBW.h"

//unsigned char* levantarBW(const char* filename);
extern unsigned char* levantarBW(const char* filename);

void test_file_writing() {
	fprintf(stderr, "Corriendo test_file_writing\n");
	write_file_bw(stdout, 1024, 1024, &qMatrix_70);
}

void test_levantar_BW(const char* filename) {
	fprintf(stderr, "Levantando BMP\n");
	unsigned char * img = levantarBW(filename);
	fprintf(stderr, "Devolviendo la memoria\n");
	free(img);
	fprintf(stderr, "FIN :)\n");
}

int main() {
	fprintf(stderr, "Corriendo tests\n");
	test_file_writing();
	test_levantar_BW("sample.bmp");
	return 0;
}