#ifndef DCT
#define DCT
#define _USE_MATH_DEFINES
#include <math.h>
#include "typedefs.h"

// calcula la DCT de 8x8 y devuelve la matriz de coeficientes
// bloque apunta al principio del bloque de 8x8 en memoria, ancho es el tamaño en memoria de una fila de imagen, res es el output
// TODO: Devolver el bloque de 8x8 en un array, ordenado en zigzag


void DCt(const char* bloque, const int ancho, double8x8* res);

void quantizar(const quant_matrix* qMatrix, double8x8* img);

const quant_matrix qMatrix_70;

#endif