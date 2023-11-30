all: fcfs HRRN LJF LRTF priority RoundRobin SJF SRTF

fcfs: fcfs.o 
	g++ fcfs.o  -o fcfs

HRRN: HRRN.o 
	g++ HRRN.o  -o HRRN

LJF: LJF.o 
	g++ LJF.o  -o LJF

LRTF: LRTF.o 
	g++ LRTF.o  -o LRTF


priority: priority.o 
	g++ priority.o  -o priority

RoundRobin: RoundRobin.o 
	g++ RoundRobin.o  -o RoundRobin

SJF: SJF.o 
	g++ SJF.o  -o SJF

SRTF: SRTF.o 
	g++ SRTF.o  -o SRTF

fcfs.o: fcfs.cpp
	g++ -c fcfs.cpp

HRRN.o: HRRN.cpp
	g++ -c HRRN.cpp

LJF.o: LJF.cpp
	g++ -c LJF.cpp

LRTF.o: LRTF.cpp
	g++ -c LRTF.cpp

priority.o: priority.cpp
	g++ -c priority.cpp

RoundRobin.o: RoundRobin.cpp
	g++ -c RoundRobin.cpp

SJF.o: SJF.cpp
	g++ -c SJF.cpp

SRTF.o: SRTF.cpp
	g++ -c SRTF.cpp

clean:
	del *.o *.exe
	rm -f *.o *.exe
