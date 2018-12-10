#include<stdio.h>
#include<stdlib.h>
//#include"medianfilter.h"
#include<memory.h>
#include<math.h>
#include<time.h> 

#define OUTPUT_FILE "out.bmp"

typedef char element;
long getImageInfo(FILE*,long,int);

// Median filtering
void _medianfilter( element* image,element* result,int nCols,int nRows)
{
	for(int m=1;m<nRows-1;++m)
		for(int n=1;n<nCols-1;++n)
		{
			int k=0;
			element window[9];
			for(int j=m-1;j<m+2;++j)
				for(int i=n-1;i<n+2;++i)
					window[k++]=image[j*nCols+i];
			for(int j=0;j<5;++j)
			{
				int min =j;
				for(int l=j+1;l<9;++l)
					if(window[l]<window[min])
						min=l;
				const element temp=window[j];
				window[j]=window[min];
				window[min]=temp;
				result[(m-1)*(nCols)+n-1]=window[4];
			}
		}
}

int main(int argc,char *argv[])
{

	FILE *bmpInput, *bmpOutput;
	unsigned char *pixel;
	char signature[2];
	long nRows,nCols,nbits;
	long xpixpeRm,ypixpeRm;
	long nColors;
	long fileSize;
	long vectorSize;
	long nBits;
	long rasterOffset;
	int i, j,k,l,m;
	unsigned char databuff[1024][1024][3];

	if(argc<2)
	{
		printf("Usage: %s <lena512.bmp>\n",argv[0]);
		exit(0);
	}

	//Open the specified input file for reading.
	printf("Reading %s ...\n",argv[1]);
	if((bmpInput = fopen(argv[1],"rb"))==NULL)
	{
		printf("Cannot read %s \n", argv[1]);
		exit(0);
	}

	//open output file.
	if((bmpOutput = fopen(argv[2],"w+"))==NULL)
	{
		if((bmpOutput = fopen(OUTPUT_FILE,"w+"))==NULL) //if user hasn't specified the output file use default output filename.
		{
			printf("Cannot read %s \n", argv[1]);
			exit(0);
		}
	}

	//position the pointer to the beginning of the file.
	fseek(bmpInput, 0L, SEEK_SET);

	//read First two characters of the input file.
	for(i=0; i<2; i++)
	{
		signature[i] = (char)getImageInfo(bmpInput,i,1);
	}

	//verify First two character of a BMP image file are BM
	if((signature[0]=='B') && (signature[1]=='M'))
	{
		printf("It is verified that the image is in Bitmap format\n");
	}
	else
	{
		printf("The image is not a BMP format,quitting....\n");
		exit(0);
	}

	//specifies number of bits per pixel in the image.
	nBits = getImageInfo(bmpInput, 28, 2);
	printf("The Image is \t%ld-bits per pixel. \n", nBits);

	//offset from the begining of the file where the pixel data starts.
	rasterOffset = getImageInfo(bmpInput,10,4);
	printf("The pixel Data is at \t%ld byte.\n",rasterOffset);

	//size of the file in bytes.
	fileSize=getImageInfo(bmpInput,2,4);
	printf("File size is \t%ld byte\n",fileSize);

	//number of columns in image.
	nCols = getImageInfo(bmpInput,18,4);
	printf("Width:\t\t%ld\n",nCols);

	//number of rows in image.
	nRows = getImageInfo(bmpInput,22,4);
	printf("Height:\t%ld\n",nRows);


	xpixpeRm = getImageInfo(bmpInput,38,4);
	printf("Image has \t%ld pixels per m in x-dir.\n",xpixpeRm);

	ypixpeRm = getImageInfo(bmpInput,42,4);
	printf("Image has \t%ld pixel per m in y-dir.\n",ypixpeRm);

	nColors = 1L<<nBits;
	printf("There are \t%ld number of colors \n",nColors);

	//it is the size of the array required to store the image pixel data.
	vectorSize = nCols*nRows;
	printf("vector Size is \t%ld\n",vectorSize);


	//write the bmp header to the output file.
	i = 0;
	while(i < rasterOffset)
	{
		fputc((char)getImageInfo(bmpInput, i, 1), bmpOutput);
		i++;
	}


	//now declare an 2D array to store & manipulate the image pixel data.
	printf("\n\nAlocare spatiu: ");	
	pixel = (char *) malloc(nRows*nCols*sizeof(char));

	

	//Read the bitmap data into array:
	printf("\n\nReading the pixel array: ");
	i = 0;
	while(i < vectorSize)
	{
		//NOTE: Pixel array starts at rasterOffset!!!
		pixel[i] = (char)getImageInfo(bmpInput, rasterOffset + i, 1);
		i++;
		// printf("%d ", i);
	}

	//Aplicare filtrului 
	printf("\n\nFilter..: ");
	clock_t t; 
    	t = clock();
	_medianfilter( pixel, pixel, nCols, nRows);
	t = clock() - t; 
    	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	printf("\n\nMEDIANFILTER took %f seconds to execute \n", time_taken);
	
	//write the modified pixel array to the output file.
	i = 0;
	while(i < vectorSize)
	{
		fputc(pixel[i], bmpOutput);
		i++;
	}

	//write the End-Of-File character the output file.
	fputc(EOF, bmpOutput);

	printf("\n");
	fclose(bmpInput);
	fclose(bmpOutput);
	free(pixel);
}

long getImageInfo(FILE* inputFile, long offset, int numberOfChars)
{
	unsigned char *ptrC;
	long value = 0L, temp;
	unsigned char dummy;
	int i;

	dummy = '0';
	ptrC = &dummy;

	//position the file pointer to the desired offset.
	fseek(inputFile, offset, SEEK_SET);

	//read the bytes into values (one byte at a time).
	for(i=0; i<numberOfChars; i++)
	{
		fread(ptrC,sizeof(char),1,inputFile);
		temp = *ptrC;
		value = (long) (value + (temp<<(8*i)));
	}

	return(value);
}
