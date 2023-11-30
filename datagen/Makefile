all: datagen datagenRR

datagen: datagen.o
	g++ datagen.o -o datagen

datagenRR: datagenRR.o
	g++ datagenRR.o -o datagenRR

datagen.o: datagen.cpp
	g++ -c datagen.cpp

datagenRR.o: datagenRR.cpp
	g++ -c datagenRR.cpp

clean:
	del *.o *.exe *.txt
	rm -f *.o *.exe *.txt