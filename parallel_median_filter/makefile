all : build_all 

thread:
	export OMP_NUM_THREADS=8
build_serial : 
	gcc -std=c99 MedianFilter.c -o serial.o
	
build_openmp : 
	gcc -std=c99 -fopenmp MedianFilterOpenMP.c -o openmp.o

build_pthread : 
	gcc -std=c99 -lpthread  MedianPthread.c -o pthread.o

	
	
build_all : build_serial build_openmp build_pthread 
	

	
run_huge_serial : 
	time ./serial.o lena_16380.bmp

run_huge_openmp : 
	OMP_NUM_THREADS=4 time ./openmp.o lena_16380.bmp

run_huge_pthread : 
	time ./pthread.o lena_16380.bmp

	
	
run_big_serial : 
	time ./serial.o lena_8192.bmp

run_big_openmp : 
	OMP_NUM_THREADS=4 time ./openmp.o lena_8192.bmp

run_big_pthread : 
	time ./pthread.o lena_8192.bmp
	
	
run_serial : 
	time ./serial.o lena_4096.bmp

run_openmp : 
	OMP_NUM_THREADS=4 time ./openmp.o lena_4096.bmp

run_pthread : 
	time ./pthread.o lena_4096.bmp

	
	
run_small_serial : 
	time ./serial.o lena_gray_1024.bmp

run_small_openmp : 
	OMP_NUM_THREADS=4 time ./openmp.o lena_gray_1024.bmp

run_small_pthread : 
	time ./pthread.o lena_1024.bmp

	
	
run_nano_serial : 
	time ./serial.o lena512.bmp

run_nano_openmp : 
	OMP_NUM_THREADS=4 time ./openmp.o lena512.bmp
	
run_nano_pthread : 
	time ./pthread.o lena512.bmp

	
	
clean :
	rm out.bmp *.o