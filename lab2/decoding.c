#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define SIZE_IN_BYTES 134217728	//pow(2,27), 128MB	(Maksymalny rozmiar pliku)

int min(int a, int b)
{
	if(a>b)
		return b;
	return a;
}

typedef unsigned long long int ullint;
typedef unsigned char uchar;
typedef unsigned long int ulint;

int necessary_precision(int amount[SIZE], ullint size);
double binseq2double(uchar* arr, int position, int length);

ullint decode_lli(uchar buf[8]);
float decode_float(uchar buf[4]);
ulint decode_ulint(unsigned char buf[4]);
int decode_int(unsigned char buf[4]);


int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Prosze podac nazwe pliku wyjsciowego!\n");
		return 0;
	}
	uchar* file_bytes = (char*)malloc(SIZE_IN_BYTES*sizeof(char));
	uchar* file_bits = (char*)malloc(SIZE_IN_BYTES*sizeof(char)*8);
	
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
	for(int i=0;i<SIZE+1;i++)
	{
		
		//printf("F[%i]: %f\n", i, F[i]);
	}	
	
	//printf("%i first bits\n", np);	
	
	uchar buffer = 0;
	char c[8];
	int n;
	int byte_counter = 0;
	while((n = fread(&buffer, 1, 1, archive)) != 0)
	{  
		for(int i=0;i<8;i++)
		{
			c[i] = ((buffer & (1 << (7-i))) ? '1' : '0');
			//printf("%c", c[i]);
		}
		memcpy(file_bits+(8*byte_counter), c, 8);
		byte_counter++;
	}
	fclose(archive);
	//uchar* ptr = (uchar*)malloc(20*sizeof(uchar));
	//ptr = "01010101001111111001";
	//double out;
	//out = binseq2double(ptr, atoi(argv[2]), atoi(argv[3]));
	//printf("out: %lf\n", out);	
 

	
	FILE* output;
	output = fopen(argv[1], "wb");	
	
	double lower = 0;
	double upper = 1;
	double diff;
	int np = necessary_precision(amount, size);
	printf("np: %i\n", np);
	int position = 0;
	double tag = 0;
	for(int i=0;i<size;i++)
	{
		//printf("\n~~~~next letter~~~~~~\n");
		//printf("position: %i\n", position);
		//printf("lower %lf\n", lower);
		diff = upper-lower;		
		//printf("diff %lf\n", diff);
		tag = binseq2double(file_bits, position, np);

		for(int k=0;k<SIZE;k++)
		{
			double lower_tmp = lower+F[k]*diff;			
			double upper_tmp = lower+F[k+1]*diff;
			//printf("%i\n", k);
			if(lower_tmp<=tag && tag<upper_tmp)
			{
				fprintf(output, "%c", k);
				//printf("%c", k);
				//printf("%c: [l: %lf, u: %lf](F[%i]:%f, F[%i]:%f)\n", k, lower_tmp, upper_tmp, k, F[k], k+1, F[k+1]);				
				while(true)
				{
					if(lower_tmp>=0 && upper_tmp<0.5)
					{
						
						lower_tmp *= 2;
						upper_tmp *= 2;
						//printf("rescale(1): [l: %lf, u: %lf]\n", lower_tmp, upper_tmp);			
							
						position++;
					}
					else if(lower_tmp>=0.5 && upper_tmp<1.0)
					{
						lower_tmp = lower_tmp*2-1;
						upper_tmp = upper_tmp*2-1;
						//printf("rescale(2): [l: %lf, u: %lf]\n", lower_tmp, upper_tmp);		
						position++;						
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
	fclose(output);	
	
	return 0;
}

int necessary_precision(int amount[SIZE], ullint size)
{
	int minimal = 2147483647;
	for(int i=0;i<SIZE;i++)
	{
		if(amount[i]>0)
		{
			minimal = min(minimal, amount[i]);
		}
	}
	return ceil(log2(size)-log2(minimal))+10;	
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
		//printf("%i", temp);
	}
	//printf(" - ret %lf\n", ret);
	
	return ret;
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