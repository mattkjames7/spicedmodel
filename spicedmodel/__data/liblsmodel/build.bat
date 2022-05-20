ld -r -b binary -o mavh.o mavh.bin
ld -r -b binary -o mavcps.o mavcps.bin
ld -r -b binary -o mavcpt.o mavcpt.bin
ld -r -b binary -o ps.o ps.bin
ld -r -b binary -o pt.o pt.bin
ld -r -b binary -o prob.o prob.bin

ld -r -b binary -o mavhann.o mavhann.bin 
ld -r -b binary -o mavcpsann.o mavcpsann.bin 
ld -r -b binary -o mavcptann.o mavcptann.bin 
ld -r -b binary -o psann.o psann.bin 
ld -r -b binary -o ptann.o ptann.bin 
ld -r -b binary -o probann.o probann.bin 
	
ld -r -b binary -o mavlambda.o mavlambda.bin
	
g++ -fPIC -c -lm -fopenmp activationfunctions.cc -o activationfunctions.o
g++ -fPIC -c -lm -fopenmp  annmodel.cc -o annmodel.o
g++ -fPIC -c -lm -fopenmp  annmavhmodel.cc -o annmavhmodel.o
g++ -fPIC -c -lm -fopenmp  annmavpsmodel.cc -o annmavpsmodel.o
g++ -fPIC -c -lm -fopenmp  annmavptmodel.cc -o annmavptmodel.o
g++ -fPIC -c -lm -fopenmp  annprobmodel.cc -o annprobmodel.o
g++ -fPIC -c -lm -fopenmp  annpsmodel.cc -o annpsmodel.o
g++ -fPIC -c -lm -fopenmp  annptmodel.cc -o annptmodel.o
g++ -fPIC -c -lm -fopenmp  avmodel.cc -o avmodel.o
g++ -fPIC -c -lm -fopenmp  avpsmodel.cc -o avpsmodel.o
g++ -fPIC -c -lm -fopenmp  avptmodel.cc -o avptmodel.o
g++ -fPIC -c -lm -fopenmp  avprobmodel.cc -o avprobmodel.o
g++ -fPIC -c -lm -fopenmp  avmavhmodel.cc -o avmavhmodel.o
g++ -fPIC -c -lm -fopenmp  avmavpsmodel.cc -o avmavpsmodel.o
g++ -fPIC -c -lm -fopenmp  avmavptmodel.cc -o avmavptmodel.o
g++ -fPIC -c -lm -fopenmp  backpropagate.cc -o backpropagate.o
g++ -fPIC -c -lm -fopenmp  boxcox.cc -o boxcox.o
g++ -fPIC -c -lm -fopenmp  cliplog.cc -o cliplog.o
g++ -fPIC -c -lm -fopenmp  costfunction.cc -o costfunction.o
g++ -fPIC -c -lm -fopenmp  matrix.cc -o matrix.o
g++ -fPIC -c -lm -fopenmp  matrixarray.cc -o matrixarray.o
g++ -fPIC -c -lm -fopenmp  matrixmath.cc -o matrixmath.o
g++ -fPIC -c -lm -fopenmp  mavtrans.cc -o mavtrans.o
g++ -fPIC -c -lm -fopenmp  networkfunc.cc -o networkfunc.o
g++ -fPIC -c -lm -fopenmp  polynomial.cc -o polynomial.o
g++ -fPIC -c -lm -fopenmp  randomnumber.cc -o randomnumber.o
g++ -fPIC -c -lm -fopenmp  readarray.cc -o readarray.o
g++ -fPIC -c -lm -fopenmp  regularization.cc -o regularization.o
g++ -fPIC -c -lm -fopenmp  rescale.cc -o rescale.o
g++ -fPIC -c -lm -fopenmp  reversearray.cc -o reversearray.o
g++ -fPIC -c -lm -fopenmp  softmax.cc -o softmax.o
	
	
REM g++ -fPIC -c -lm -fopenmp  tests/matdot.cc -o tests/matdot.o
REM g++ -fPIC -c -lm -fopenmp  tests/netfunc.cc -o tests/netfunc.o
REM g++ -fPIC -c -lm -fopenmp  tests/probmodels.cc -o tests/probmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/mavhmodels.cc -o tests/mavhmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/mavpsmodels.cc -o tests/mavpsmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/mavptmodels.cc -o tests/mavptmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/psmodels.cc -o tests/psmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/ptmodels.cc -o tests/ptmodels.o
REM g++ -fPIC -c -lm -fopenmp  tests/testmavtrans.cc -o tests/testmavtrans.o

g++ -lm -fopenmp liblsmodel.cc *.o -fPIC -shared -o liblsmodel.dll
