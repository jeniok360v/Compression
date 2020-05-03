#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define SIZE_IN_BYTES 134217728	//pow(2,27), 128MB	(Maksymalny rozmiar pliku)

typedef unsigned long long int ullint;
typedef unsigned long int ulint;
typedef unsigned char uchar;


void encode_lli(ullint n, uchar buf[8]);
void encode_float(float n, uchar buf[4]);
void encode_ulint(ulint n, uchar buf[4]);
void encode_int(int n, uchar buf[4]);

float calculate_entr(int ilosc[SIZE], ullint amount);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Prosze podac nazwe pliku wejsciowego!\n");
		return 0;		
	}
	uchar* file_bytes = (uchar*)malloc(SIZE_IN_BYTES*sizeof(char));
	uchar* file_bits = (uchar*)malloc(SIZE_IN_BYTES*sizeof(char)*8);
	
	FILE* output; 
	FILE* input;
	int amount[SIZE]={0};
	input = fopen(argv[1], "rb"); 
	if (input == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}	
	
	ullint size=0;
	uchar buffer = 0;
	int n;
	while((n = fread(&buffer, 1, 1, input)) != 0)
	{
		amount[(int)buffer]++;
		size++;
	}
	fclose(input);
	
	double F[SIZE+1];	//prawdopodobienstwo
	F[0]=0;
	for(int i=0;i<SIZE;i++)
	{
		F[i+1]=(double)amount[i]/(double)size;
		F[i+1]+=F[i];
	}

	input = fopen(argv[1], "rb"); 
	output = fopen("archive.bin", "wb"); 
	if (output == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}
		
	uchar buf[sizeof(ullint)];
	encode_lli(size, buf);
	fwrite(buf, sizeof(buf), 1, output);
	
	uchar buf2[sizeof(int)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		encode_int(amount[i], buf2);
		fwrite(buf2, 4, 1, output);
		memset(buf2, 0, 4);	//to delete
	}
		
	double lower = 0;
	double upper = 1;	
	double diff = 1;
	int licz = 0;
	int counter = 0;
	int licznik = 0;
	while((n = fread(&buffer, 1, 1, input)) != 0)
	{
		int c;
		for(int j=0;j<SIZE;j++)
		{
			if(j==buffer)
			{
				c = j;
				break;
			}
		}
		diff = upper-lower;
		upper = lower+F[c+1]*diff;
		lower = lower+F[c]*diff;
		while(true)
		{	
			//printf("licz:%i, lower:%f, upper:%f, F[%i]:%f, F[%i]:%f\n", licz, lower, upper, c, F[c], c+1, F[c+1]);
			if(lower>=0 && upper<0.5)
			{
				file_bits[counter] = '0';
				counter++;
				for(int i=0;i<licznik;i++)
				{
					file_bits[counter] = '1';
					counter++;				
				}
				lower=(double)2*lower;
				upper=(double)2*upper;
				licznik = 0;
			}
			else if(lower>=0.5 && upper<1.0)
			{
				file_bits[counter] = '1';
				counter++;
				for(int i=0;i<licznik;i++)
				{
					file_bits[counter] = '0';
					counter++;				
				}
				lower=(double)2*lower-(double)1;
				upper=(double)2*upper-(double)1;
				licznik = 0;
			}
			else if(lower>=0.25 && upper<0.75)
			{
				lower=(double)2*lower-(double)0.5;
				upper=(double)2*upper-(double)0.5;				
				licznik++;
			}
			else 
				break;			
		}
		licz++;
	}	
	

	int byte_counter = counter/8;
	for(int i=0;i<byte_counter;i++)
	{
		char data[8];
		memcpy(data, file_bits+(8*i), 8);
		char c = strtol(data, 0, 2);
		file_bytes[i] = c;
	}
	
	// zera na koncu ostatniego bajtu
	int last_fragment = counter%8;
	if(last_fragment)
	{
		char data[last_fragment];
		memcpy(data, file_bits+(byte_counter*8), last_fragment);
		char zeros[8-last_fragment];
		for(int i=0;i<8-last_fragment;i++)
			zeros[i]='0';		
		
		char* total = malloc(8*sizeof(char));
		memcpy(total, data, last_fragment*sizeof(char));
		memcpy(total+last_fragment, zeros, (8-last_fragment)*sizeof(char));
		
		char c = strtol(total, 0, 2);
		file_bytes[byte_counter] = c;
	}
	else
	{
		file_bytes[byte_counter] = 0;	
	}
	for(int i=0;i<4;i++)
	{
		//jeszcze kilka zerowych bajtow na samym koncu pliku
		file_bytes[byte_counter+i] = 0;
	}
	fwrite(file_bytes, sizeof(char), (byte_counter+5)*sizeof(char), output);
	
	
	float entropy = calculate_entr(amount, size);
	printf("Entropia: %f\n", entropy);	
	printf("Srednia liczba bitow na symbol(sam tekst) %lf\n", 8.0f*(float)(byte_counter+5)/(float)size);
	printf("Srednia liczba bitow na symbol %lf\n", 8.0f*((float)(byte_counter+5)+sizeof(ullint)+256*sizeof(int))/(float)size);
	printf("Stopien kompresji %lf\n",(float)size/((float)(byte_counter+5)+sizeof(ullint)+256*sizeof(int)));
	
	
	fclose(output);	
	free(file_bits);
	free(file_bytes);
	return 0;
}


void encode_lli(ullint n, uchar buf[8])
{
	for(int i=0;i<8;i++)
	{
		buf[7-i] = n%256;
		n /= 256;
	}
}

void encode_float(float n, uchar buf[4])
{ 
	memcpy(buf, (uchar*) (&n), 4);
	return;
}

void encode_ulint(ulint n, uchar buf[4])
{ 
	memcpy(buf, (uchar*) (&n), 4);
	return;
}

void encode_int(int n, uchar buf[4])
{ 
	memcpy(buf, (uchar*) (&n), 4);
	return;
}

float calculate_entr(int ilosc[SIZE], ullint amount)	//amount to liczba bajtow
{
	float entropy=0;
	if(amount>0)
	{
		for (int i=0; i<SIZE;i++)
		{
			if(ilosc[i]>0)
			{
				entropy += ilosc[i]*(log2(ilosc[i]));
			}
		}
		entropy= -entropy/(float)amount;
		entropy+=log2((float)amount);
	}
	return entropy;
}
