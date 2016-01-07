#include "dct.h"

//#define PI M_PI
//#define INVSQRT2 M_SQRT1_2
#define PI 3.14159265358979323846
#define INVSQRT2 (1/sqrt(2))

const quant_matrix qMatrix_70 = {
	{10, 7, 6,10,14,24,31,37},
	{ 7, 8,11,16,35,36,33,37},
	{ 8, 8,10,14,24,34,41,34},
	{ 8,10,13,17,31,52,48,37},
	{11,13,22,34,41,65,62,46},
	{14,21,33,38,49,62,68,55},
	{29,38,47,52,62,73,72,61},
	{43,55,57,59,67,60,62,59}
};

int fruta = 0;

// calcula la DCT de 8x8 y devuelve la matriz de coeficientes
// bloque apunta al principio del bloque de 8x8 en memoria, ancho es el tamaño en memoria de una fila de imagen, res es el output
// TODO: Devolver el bloque de 8x8 en un array, ordenado en zigzag
void DCT(const char* bloque, const int ancho, double8x8* res) {
	int i, j, xOffset, yOffset;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			double coeficiente = 0;
			for (xOffset = 0; xOffset < 8; ++xOffset) {
				for (yOffset = 0; yOffset < 8; ++yOffset) {
					double punto = (double) *(bloque + ancho * yOffset + xOffset) - 128;
					coeficiente += punto * cos((2*xOffset + 1)*j*PI/16) * cos((2*yOffset + 1)*i*PI/16); 
				}
			}
			double C;
			C = 0.25 * (i == 0? INVSQRT2 : 1) * (j == 0? INVSQRT2 : 1);
			(*res)[i][j] = C * coeficiente;
		}
	}
}


//TODO: Cuantizar directamente adentro de la DCT para no tener que volver a levantar los 8x8 doubles de memoria.

// cuantiza el resultado de la DCT
// img es el fragmento de 8x8 que viene de la DCT y tambien donde se guarda el resultado
// qMatrix es la matriz con los valores de cuantizacion
void quantizar(const quant_matrix* qMatrix, double8x8* img) {
	int i,j;
	for (i = 0; i < 8; ++i) for (j = 0; j < 8; ++j)
		(*img)[i][j] /= (*qMatrix)[i][j];
}

