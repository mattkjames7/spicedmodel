# CFLAGS for CC
CFLAGS=-lm -fopenmp

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all: obj test

obj:
	#these are the average model parameters
	ld -r -b binary -o mav.o mav.bin
	ld -r -b binary -o ps.o ps.bin
	ld -r -b binary -o pt.o pt.bin
	ld -r -b binary -o prob.o prob.bin

	#these files contain the ANN weights, biases etc.
	ld -r -b binary -o mavann.o mavann.bin 
	ld -r -b binary -o psann.o psann.bin 
	ld -r -b binary -o ptann.o ptann.bin 
	ld -r -b binary -o probann.o probann.bin 
	
	#source code
	$(CCo) activationfunctions.cc -o activationfunctions.o
	$(CCo) avmodel.cc -o avmodel.o
	$(CCo) avpsmodel.cc -o avpsmodel.o
	$(CCo) avptmodel.cc -o avptmodel.o
	$(CCo) avprobmodel.cc -o avprobmodel.o
	$(CCo) avmavmodel.cc -o avmavmodel.o
	$(CCo) boxcox.cc -o boxcox.o
	$(CCo) matrix.cc -o matrix.o
	$(CCo) matrixarray.cc -o matrixarray.o
	$(CCo) matrixmath.cc -o matrixmath.o
	$(CCo) polynomial.cc -o polynomial.o
	$(CCo) readarray.cc -o readarray.o
	$(CCo) reversearray.cc -o reversearray.o

test:
	$(CC) *.o test.cc -o test

	
exec:
	$(CC) *.o -o exe
	

	
clean:
	rm -v *.o exe test
