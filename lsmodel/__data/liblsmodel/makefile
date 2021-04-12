# CFLAGS for CC
CFLAGS=-lm -fopenmp

# Compiler
CCo=g++ -fPIC -c $(CFLAGS)
CC=g++ $(CFLAGS)

all: obj test lib

obj:
	#these are the average model parameters
	ld -r -b binary -o mavh.o mavh.bin
	ld -r -b binary -o mavcps.o mavcps.bin
	ld -r -b binary -o mavcpt.o mavcpt.bin
	ld -r -b binary -o ps.o ps.bin
	ld -r -b binary -o pt.o pt.bin
	ld -r -b binary -o prob.o prob.bin

	#these files contain the ANN weights, biases etc.
	ld -r -b binary -o mavann.o mavann.bin 
	ld -r -b binary -o psann.o psann.bin 
	ld -r -b binary -o ptann.o ptann.bin 
	ld -r -b binary -o probann.o probann.bin 
	
	#binary containing polynomals for mav transform
	ld -r -b binary -o mavlambda.o mavlambda.bin
	
	#source code
	$(CCo) activationfunctions.cc -o activationfunctions.o
	$(CCo) annmodel.cc -o annmodel.o
	$(CCo) annmavmodel.cc -o annmavmodel.o
	$(CCo) annprobmodel.cc -o annprobmodel.o
	$(CCo) annpsmodel.cc -o annpsmodel.o
	$(CCo) annptmodel.cc -o annptmodel.o
	$(CCo) avmodel.cc -o avmodel.o
	$(CCo) avpsmodel.cc -o avpsmodel.o
	$(CCo) avptmodel.cc -o avptmodel.o
	$(CCo) avprobmodel.cc -o avprobmodel.o
	$(CCo) avmavhmodel.cc -o avmavhmodel.o
	$(CCo) avmavpsmodel.cc -o avmavpsmodel.o
	$(CCo) avmavptmodel.cc -o avmavptmodel.o
	$(CCo) backpropagate.cc -o backpropagate.o
	$(CCo) boxcox.cc -o boxcox.o
	$(CCo) cliplog.cc -o cliplog.o
	$(CCo) costfunction.cc -o costfunction.o
	$(CCo) matrix.cc -o matrix.o
	$(CCo) matrixarray.cc -o matrixarray.o
	$(CCo) matrixmath.cc -o matrixmath.o
	$(CCo) mavtrans.cc -o mavtrans.o
	$(CCo) networkfunc.cc -o networkfunc.o
	$(CCo) polynomial.cc -o polynomial.o
	$(CCo) randomnumber.cc -o randomnumber.o
	$(CCo) readarray.cc -o readarray.o
	$(CCo) regularization.cc -o regularization.o
	$(CCo) rescale.cc -o rescale.o
	$(CCo) reversearray.cc -o reversearray.o
	$(CCo) softmax.cc -o softmax.o
	
	
	$(CCo) tests/matdot.cc -o tests/matdot.o
	$(CCo) tests/netfunc.cc -o tests/netfunc.o
	$(CCo) tests/probmodels.cc -o tests/probmodels.o
	$(CCo) tests/mavmodels.cc -o tests/mavmodels.o
	$(CCo) tests/psmodels.cc -o tests/psmodels.o
	$(CCo) tests/ptmodels.cc -o tests/ptmodels.o
	$(CCo) tests/testmavtrans.cc -o tests/testmavtrans.o

test:
	$(CC) *.o tests/*.o test.cc -o test

	

lib:
	$(CC) liblsmodel.cc *.o -fPIC -shared -o liblsmodel.so
	
clean:
	rm -v *.o tests/*.o test liblsmodel.so
