#include "writers.h"

void write_file_bw(FILE* f, int height, int width, const quant_matrix* qMatrix) {
	unsigned char SOI[] = {
		0xFF, 0xD8	//0xFFD8 JPEG ile dSOI
	};
	if (fwrite(SOI, 1, 2, f) < 2) printf("Error escribiendo SOI\n");

	// No cambiar el orden de esto!!!
	write_sof_bw(f, height, width);
	write_dht_bw(f, DC_Selector, Y_identifier, 
					Y_DC_LENGTHS,
					Y_DC_HUFFVALS, Y_DC_HUFFVALS_SIZE);
	write_dht_bw(f, AC_Selector, Y_identifier, 
					Y_AC_LENGTHS,
					Y_AC_HUFFVALS, Y_AC_HUFFVALS_SIZE);
	write_dqt_bw(f, qMatrix);
	write_sos_bw(f);
} 

void write_sof_bw(FILE* f, int height, int width) {
	unsigned char SOF[] = { 
		0xFF,	//0xFF(start)
		192,	//192 std baseline sequential dct mode (?)
		0, 11,	// size of segment (0, 8 + 3 * #components)
		8,		// color depth
		(char) (height / 256), (char) (height % 256), 	// heigth = b1 * 256 + b2
		(char) (width / 256), (char) (width % 256),		// width = b1 * 256 + b2
		1, 		// # components
		Y_identifier,
		2*16 + 2,	// sampling (H * 16 + V)
		0 		// quant table for Y comp
	};
	if (fwrite(SOF, 1, 13, f) < 13) printf("Error escribiendo SOF\n");

}

void write_dht_bw(FILE* f, const unsigned char DC_ACSelector, const unsigned char Y_UVSelector, 
					const unsigned char* lengths,
					const unsigned char* vals, const unsigned char vals_size)
				 {
	unsigned char length1, length2;
	int totalLength = 3 + 16 + vals_size;
	length2 = totalLength % 256;
	length1 = totalLength / 256;
	unsigned char DHT[] = {	
		0xFF, 196, 	// start, DHT identif.
		(DC_ACSelector << 4) + Y_UVSelector, 
		length1, length2
	};	
	if (fwrite(DHT, 1, 5, f) < 5) printf("Error escribiendo DHT\n");
	if (fwrite(lengths, 1, 16, f) < 16) printf("Error escribiendo DHT:LENGTHS\n");
	if (fwrite(vals, 1, vals_size, f) < vals_size) printf("Error escribiendo DHT:VALS\n");
}

void write_dqt_bw(FILE* f, const quant_matrix* qMatrix) {
	unsigned char DQT[] = {
		0xFF, 219, 	// start, DQT ident
		0, 67,		// length
		0 * 16 + Y_identifier	// 0 = bytes, Y_ident para que componente es la tabla
	};

	unsigned char zigzag_matrix[64];
	/*(0, 0),
	(0, 1), (1, 0),
	(2, 0), (1, 1), (0, 2),
	(0, 3), (1, 2), (2, 1), (3, 0),
	(4, 0), (3, 1), (2, 2), (1, 3), (0, 4)
	obs: en cada diagonal, i+j es constante
	a la pos i,j le corresponde:
		si estoy en la primera mitad (i + j <= 7):
			lo que acumule de diagonales completas hasta ahora [sum_i=0^diag i] + las filas que baje [i] si vengo de arriba (i+j es par) o las cols que avance [j] si vengo de abajo
		si estoy en la segunda mitad (i + j > 7):
			64 - las diagonales enteras que me faltan [sum_i=0^14-diag i] + lo que me falta bajar (si estoy bajando, par) [7-i] o lo que me falta para la derecha (si estoy subiendo, impar) [7-j]
	*/
	int i, j;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			int pos;
			int d = i + j;
			if (d <= 7) {
				pos = d*(d+1)/2 + (d % 2 == 0? i : j); 
			} else {
				pos = 63 - (14-d)*(14-d+1)/2 - (d % 2 == 0? j : i);
			}
			zigzag_matrix[pos] = (*qMatrix)[i][j];
		}
	}

	if (fwrite(DQT, 1, 5, f) < 5 || fwrite(zigzag_matrix, 1, 64, f) < 64) printf("Error escribiendo DQT\n");
}

void write_sos_bw(FILE* f) {
	unsigned char SOS[] = {
		0xFF, 	// start
		218, 	// SOS segment marker
		0, 8,	// size of segment (0, 6 + 2 * #components)
		1,		// # components
		Y_identifier,
		DC_Selector * 16 + AC_Selector,	// medio byte para cada uno
		0, 63, 0 // quedan asi para sequential DCT
	};
	if (fwrite(SOS, 1, 10, f) < 10) printf("Error escribiendo SOS\n");
}
