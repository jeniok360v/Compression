#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define SIZE_IN_BYTES 134217728	//pow(2,27), 128MB	(Maksymalny rozmiar pliku)
#define PRECISION 10

int min(int a, int b)
{
	if(a>b)
		return b;
	return a;
}

typedef unsigned long long int ullint;
typedef unsigned char uchar;
typedef unsigned long int ulint;

int necessary_precision(int amount[SIZE], ullint size, int precision);
double binseq2double(uchar* arr, int position, int length);
ullint binseq2ullint(uchar* arr, int position, int length, ullint M);

ullint decode_lli(uchar buf[8]);
float decode_float(uchar buf[4]);
ulint decode_ulint(unsigned char buf[4]);
int decode_int(unsigned char buf[4]);

double rescale1(double in);
double rescale2(double in);
double rescale3(double in);


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Prosze podac nazwe pliku wyjsciowego!\n");
		return 0;
	}

	uchar* file_bits = (uchar*)malloc(SIZE_IN_BYTES*sizeof(char)*8);
	
	// open archive.bin
	FILE* archive;
	archive = fopen("archive.bin", "rb"); 
	
	//size - number of charachters
	ullint size = 0;
	uchar decode_buff[8];
	fread(decode_buff, sizeof(decode_buff), 1, archive);	
	size = decode_lli(decode_buff);	
	
	//number of every character
	int amount[SIZE] = {0};
	uchar decode_buff2[sizeof(int)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		fread(decode_buff2, sizeof(decode_buff2), 1, archive);
		amount[i] = decode_int(decode_buff2);
	}
	

	double F[SIZE+1];	//prawdopodobienstwo
	F[0]=0;
	for(int i=0;i<SIZE;i++)
	{
		F[i+1]=(double)amount[i]/(double)size;
		F[i+1]+=F[i];
	}	
	
	ullint f[SIZE+1];	//prawdopodobienstwo
	f[0]=0;
	for(int i=0;i<SIZE;i++)
	{
		f[i+1]=(ullint)amount[i];
		f[i+1]+=f[i];
	}
	
	uchar buffer = 0;
	uchar c[8];
	int n;
	int byte_counter = 0;
	//zamiana symboli ASCII na '0' i '1'
	while((n = fread(&buffer, 1, 1, archive)) != 0)
	{  
		for(int i=0;i<8;i++)
		{
			c[i] = ((buffer & (1 << (7-i))) ? '1' : '0');
		}
		memcpy(file_bits+(8*byte_counter), c, 8);
		byte_counter++;
	}
	fclose(archive);


	FILE* output;
	output = fopen(argv[1], "wb");	
	
	int np = necessary_precision(amount, size, PRECISION);
	if(np>31)
	{
		printf("Za duza precyzja: %i bitow\n", np);
		return 0;
	}
	ullint m = ceil(log2(size))+2;
	ullint M = pow(2, m);	
	printf("M: %lli, m: %lli\n", M, m);
	
	
	ullint lower = 0;
	ullint upper = M-1;
	ullint diff = M;	
	np=31;	//maksymalna precyzja
	int position = 0;
	ullint tag = binseq2ullint(file_bits, position, np, M);
	int licznik = 0;
	for(int i=0;i<size;i++)
	{
		diff = upper-lower+1;	
		for(int k=0;k<SIZE;k++)
		{
			ullint lower_tmp = lower+floor((f[k]*diff)/size);		
			ullint upper_tmp = lower+floor((f[k+1]*diff)/size)-1;
			
			if(lower_tmp<=tag && (long long int)tag<(long long int)upper_tmp)
			{
				//if(i > 55 && i < 65) for(int h=position;h<position+32;h++) printf("%c", file_bits[h]);
				printf("licz:%i, lower:%lli, upper:%lli, tag %lli\n", i, lower_tmp, upper_tmp, tag);
				fprintf(output, "%c", k);
				printf("%c",k);
				while(true)
				{
					if(lower_tmp>=0 && upper_tmp<M/2)
					{
						
						lower_tmp *= 2;
						upper_tmp *= 2;
						position = position+licznik+1;
						licznik = 0;
						tag = binseq2ullint(file_bits, position, np, M);
						//printf("1:%i, lower:%f, upper:%f, tag %lf\n", i, lower_tmp, upper_tmp, tag);
					}
					else if(lower_tmp>=M/2 && upper_tmp<M)
					{
						lower_tmp = lower_tmp*2-M;
						upper_tmp = upper_tmp*2-M;
						position = position+licznik+1;
						licznik = 0;
						tag = binseq2ullint(file_bits, position, np, M);
						//printf("2:%i, lower:%f, upper:%f, tag %lf\n", i, lower_tmp, upper_tmp, tag);
					}
					else if(lower_tmp>=M/4 && upper_tmp<3*M/4)
					{
						lower_tmp = lower_tmp*2-M/2;
						upper_tmp = upper_tmp*2-M/2;
						tag = tag*2-M/2;
						licznik++;
						//printf("3:%i, lower:%f, upper:%f, tag %lf\n", i, lower_tmp, upper_tmp, tag);
					}
					else 
					{
						lower = lower_tmp;
						upper = upper_tmp;
						break;
					}
				}
				break;
			}
		}	
	}
	free(file_bits);
	fclose(output);	
	return 0;
}

int necessary_precision(int amount[SIZE], ullint size, int precision)
{
	int minimal = 2147483647;
	for(int i=0;i<SIZE;i++)
	{
		if(amount[i]>0)
		{
			minimal = min(minimal, amount[i]);
		}
	}
	return ceil(log2(size)-log2(minimal))+precision;	
}

double binseq2double(uchar* arr, int position, int length)
{
	double ret = 0.0;
	int div = 2; 
	int temp = 0;
	for(int i=0;i<length;i++)
	{
		temp = (*(arr+position+i) == '0' ? 0 : 1);
		ret += (double)temp/(double)div;
		div *= 2;
	}
	return ret;
}

ullint binseq2ullint(uchar* arr, int position, int length, ullint M)
{
	double ret = 0.0;
	int div = 2; 
	int temp = 0;
	for(int i=0;i<length;i++)
	{
		temp = (*(arr+position+i) == '0' ? 0 : 1);
		ret += (double)temp/(double)div;
		div *= 2;
	}
	ret*=(double)M;
	return (ullint)ret;
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


double rescale1(double in)
{
	double ret;
	ret = in*(double)2.0;
	return ret;
}

double rescale2(double in)
{
	double ret;
	ret = in*(double)2.0-(double)1.0;
	return ret;
}

double rescale3(double in)
{
	double ret;
	ret = in*(double)2.0-(double)0.5;
	return ret;	
}



