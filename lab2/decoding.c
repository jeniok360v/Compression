#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define SIZE_IN_BYTES 134217728	//pow(2,27), 128MB	(Maksymalny rozmiar pliku)

typedef unsigned long long int ullint;
typedef unsigned char uchar;
typedef unsigned long int ulint;


ullint decode_lli(uchar buf[8]);
float decode_float(uchar buf[4]);
ulint decode_ulint(unsigned char buf[4]);
int decode_int(unsigned char buf[4]);


int main()
{
	uchar* file_bytes = (char*)malloc(SIZE_IN_BYTES*sizeof(char));
	uchar* file_bits = (char*)malloc(SIZE_IN_BYTES*sizeof(char)*8);
	
	FILE* fdecode;
	fdecode = fopen("archive.bin", "rb"); 
	
	ullint size = 0;
	uchar decode_buff[8];
	fread(decode_buff, sizeof(decode_buff), 1, fdecode);	
	size = decode_lli(decode_buff);	
	printf("lli: %lli\n", size);
	
	
	
	int amount[SIZE] = {0};
	uchar decode_buff2[sizeof(int)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		fread(decode_buff2, sizeof(decode_buff2), 1, fdecode);
		amount[i] = decode_int(decode_buff2);
	}
	

	float F[SIZE+1];	//prawdopodobienstwo
	F[0]=0;
	for(int i=0;i<SIZE;i++)
	{
		F[i+1]=(float)amount[i]/(float)size;
		F[i+1]+=F[i];
	}
	
	/*
	for(int i=0;i<SIZE+1;i++)
	{
		printf("F[%i]: %f\n", i, F[i]);
	}	
	
	/*
	for(int i=0;i<SIZE;i++)
	{
		if(amount[i]>0)
		printf("amount[%i]: %i\n", i, amount[i]);
	}	
	*/
	free(file_bytes);
	free(file_bits);
	fclose(fdecode);	
	
	return 0;
}

ullint decode_lli(uchar buf[8])
{
	ullint n = 0;
	ullint temp = 1;
	for(int i=0;i<8;i++)
	{
		n += (buf[7-i])*temp;
		temp*=256;
	}
	return n;
}

float decode_float(uchar buf[4])
{
	float f1 = *(float*)(buf);
	return f1;	
}

ulint decode_ulint(unsigned char buf[4])
{
	ulint f1 = *(ulint*)(buf);
	return f1;	
}

int decode_int(unsigned char buf[4])
{
	return *(int*)(buf);
}