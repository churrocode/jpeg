#ifndef JPEG_BBUFF
#define JPEG_BBUFF

typedef struct {
	// un buffer de size bytes
	int size;
	//cuantos bits ocupados en el ultimo byte ocupado
	// de der a izq (de 7 a 0)
	int takenBits;
	// el primer byte al que puedo escribir
	// (o el ultimo ocupado, si no es el primero)
	int byteToWriteInto;
	// el buffer de bytes donde escribo
	unsigned char* buff;
} bitBuffer;

bitBuffer bB_new(int size);
void bB_free(bitBuffer* bb);

// size dice cuantos BITS tengo que copiar al buffer
// start apunta al byte donde empiezan (desde el bit7) los bits que hay que copiar 
void bB_write(unsigned char* start, int writeSize, bitBuffer* buffer);

// escribe en el buffer sólo los bits que sirven de num (los "primeros" numLength si no fuera por el endianness)
void bB_write_short(unsigned short num, int numLength, bitBuffer* buffer);

void printBuffer(const bitBuffer* b);


#endif
