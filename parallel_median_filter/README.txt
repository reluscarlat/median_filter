Comanda rulare sursa:
	gcc -std=c99 medianFilter.c && ./a.out lena_4096.bmp



Comenzi MPI: 	mpicc MedianFilterMPI.c -o mpiFilter
		
mpirun -np 4 ./mpiFilter ./lena_gray_1024.bmp out