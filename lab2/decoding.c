#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256

typedef unsigned long long int ullint;
typedef unsigned char uchar;



ullint decode_lli(uchar buf[8]);
float decode_float(uchar buf[4]);


int main()
{
	FILE* fdecode;
	fdecode = fopen("archive.bin", "rb"); 
	
	ullint decode_size = -1;
	uchar decode_buff[8];
	//fread(&decode_buff, 8, 1, fdecode);
	fread(decode_buff, sizeof(decode_buff), 1, fdecode);
	for(int i=0;i<8;i++)
	{
		printf("%i: %c(%i)\n", i, decode_buff[i], decode_buff[i]);
	}	
	decode_size = decode_lli(decode_buff);	
	printf("lli: %lli\n", decode_size);
	
	
	float F2[SIZE+1] = {0};
	uchar decode_buff2[sizeof(float)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		fread(decode_buff2, sizeof(decode_buff2), 1, fdecode);
		F2[i+1] = decode_float(decode_buff2);
	}
	
	/*
	for(int i=0;i<SIZE+1;i++)
	{
		printf("F2[%i]: %f\n", i, F2[i]);
	}	
	*/
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


