SHELL:=/bin/bash

nr_threads=2
vector_threads=2 3 4 5 6 7 8 9 10 11 12
image=input/lena_16380.bmp

all : build_all run_all

collect_data:
	touch data.csv
	printf "%s\n" "Rezolutie,Framework,Time,Threads" > data.csv

build_serial : collect_data
	gcc -std=c99 MedianFilter.c -o serial.o

build_openmp : collect_data
	gcc -std=c99 -fopenmp MedianFilterOpenMP.c -o openmp.o

build_pthread : collect_data
	gcc -std=c99 -lpthread  MedianPthread.c -o pthread.o

build_mpi: collect_data
	. /usr/share/Modules/init/bash; \
	module load libraries/openmpi-2.0.1-gcc-5.4.0; \
	mpicc -std=c99 MedianFilterMPI.c -o mpi.o

build_all: build_serial build_openmp build_pthread build_mpi


run_serial :
		./serial.o $(image) output/serial.bmp
run_openmp :
		OMP_NUM_THREADS=$(nr_threads) ./openmp.o $(image) output/openmp.bmp
run_pthread :
		./pthread.o $(image) output/pthread.bmp $(nr_threads)
run_mpi:
		. /usr/share/Modules/init/bash; \
		module load libraries/openmpi-2.0.1-gcc-5.4.0; \
		mpirun -np $(nr_threads) ./mpi.o $(image) output/mpi.bmp


run_all: run_serial run_openmp run_pthread run_mpi check_openmp check_pthread check_mpi


run_for_all: run_serial
				. /usr/share/Modules/init/bash; \
				for i in $(vector_threads);\
				do \
				OMP_NUM_THREADS=$$i ./openmp.o $(image) output/openmp.bmp;\
				./pthread.o $(image) output/pthread.bmp $$i;\
				module load libraries/openmpi-2.0.1-gcc-5.4.0; \
				mpirun -np $$i ./mpi.o $(image) output/mpi.bmp;\
				done;                     \



clean_check:
		rm  diff.txt
check_openmp:
	diff -i -w -B output/serial.bmp output/openmp.bmp >>diff.txt
check_pthread:
		diff -i -w -B output/serial.bmp output/pthread.bmp >>diff.txt
check_mpi:
		diff -i -w -B output/serial.bmp output/mpi.bmp >>diff.txt
check_all: check_openmp check_pthread check_mpi

clean_data:
	rm data.csv

clean :
	rm  data.csv *.o output/serial.bmp output/openmp.bmp output/mpi.bmp output/pthread.bmp

clean_all: clean clean_data check_init
