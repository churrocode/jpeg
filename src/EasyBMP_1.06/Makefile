
all: EasyBMP.o levantarBW.o 
	cp levantarBW.o ../levantarBW.o 
	cp EasyBMP.o ../EasyBMP.o

levantarBW.o: EasyBMP.o levantarBW.h 
	g++ -c levantarBW.cpp
	cp levantarBW.o ../levantarBW.o

EasyBMP.o: EasyBMP.cpp EasyBMP*.h
	g++ -c EasyBMP.cpp

clean:
	rm *.o
	rm ../levantarBW.o
