#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define MAX_SIZE_IN_BYTES 1073741824	//pow(2,30), 1024MB
#define SIZE_IN_BYTES 134217728	//pow(2,27), 128MB	(Maksymalny rozmiar pliku)

typedef unsigned long long int ullint;
typedef unsigned long int ulint;
typedef unsigned char uchar;


void encode_lli(ullint n, uchar buf[8]);
void encode_float(float n, uchar buf[4]);
void encode_ulint(ulint n, uchar buf[4]);
void encode_int(int n, uchar buf[4]);



int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Prosze podac nazwe pliku wejsciowego!\n");
		return 0;		
	}
	uchar* file_bytes = (char*)malloc(SIZE_IN_BYTES*sizeof(char));
	uchar* file_bits = (char*)malloc(SIZE_IN_BYTES*sizeof(char)*8);
	
	FILE* output; 
	FILE* copy; 
	FILE* fptr2;
	int amount[SIZE]={0};
	fptr2 = fopen(argv[1], "rb"); 
	if (fptr2 == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}	
	
	ullint size=0;
	uchar buffer = 0;
	int n;
	while((n = fread(&buffer, 1, 1, fptr2)) != 0)
	{
		amount[(int)buffer]++;
		size++;
	}

	
	fclose(fptr2);
	
	double F[SIZE+1];	//prawdopodobienstwo
	F[0]=0;
	for(int i=0;i<SIZE;i++)
	{
		F[i+1]=(double)amount[i]/(double)size;
		F[i+1]+=F[i];
	}
	
	
	for(int i=0;i<SIZE+1;i++)
	{
		if(amount[i]>0)
		printf("F[%i]: %f\n", i, F[i]);
	}
	/*
	for(int i=0;i<SIZE;i++)
	{
		if(amount[i]>0)
		{
			printf("amount[%i]: %i\n", i, amount[i]);
		}
	}
	*/
	fptr2 = fopen(argv[1], "rb"); 
	output = fopen("archive.bin", "wb"); 
	copy = fopen("copy.txt", "wb"); 
	if (output == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}
		
	uchar buf[sizeof(ullint)];
	//ullint die = 2575327;
	encode_lli(size, buf);
	fwrite(buf, sizeof(buf), 1, output);
	
	uchar buf2[sizeof(int)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		encode_int(amount[i], buf2);
		fwrite(buf2, 4, 1, output);
		memset(buf2, 0, 4);	//to delete
	}
		
	double l = 0;
	double p = 1;	
	double d;
	double z;
	int licz = 0;
	int counter = 0;
	while((n = fread(&buffer, 1, 1, fptr2)) != 0)
	{
		//fprintf(copy, "%c", buffer);
		int c;
		for(int j=0;j<SIZE;j++)
		{
			if(j==buffer)
			{
				c = j;
				break;
			}
		}
		d = p-l;
		p = l+F[c+1]*d;
		l = l+F[c]*d;
		z = (l+p)/2;
		
		//int counter = 0;
		while(true)
		{
			//printf("licz:%i, l:%f, p:%f, z:%f, F[%i]:%f, F[%i]:%f\n", licz, l, p, z, c, F[c], c+1, F[c+1]);
			if(l>=0 && p<0.5f)
			{
				file_bits[counter] = '0';
				counter++;
				//fprintf(copy, "0");// 0
				//printf("0");

				l=2*l;
				p=2*p;
				//counter=0;
			}
			else if(l>=0.5f && p<1.0f)
			{
				file_bits[counter] = '1';
				counter++;
				//fprintf(copy, "1");//1
				//printf("1");
				l=2*l-1;
				p=2*p-1;	
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
		//for(int i=0;i<8;i++)
		//	printf("%c", total[i]);
		
		char c = strtol(total, 0, 2);
		file_bytes[byte_counter] = c;
	}
	fwrite(file_bytes, sizeof(char), (byte_counter+1)*sizeof(char), output);
	
	fclose(output);	
	fclose(copy);
	
	/*
	char out[S] = "";
	l=0; p=1; int c;
	for(int i=0;i<S;i++)
	{
		int j;
		for(j=0;j<S;j++)
		{
			printf("(%f, %f)\n", l+F[j]*(p-l), l+F[j+1]*(p-l));
		}
		
		for(int j=0;j<S;j++)
		{
			if(l+F[j]*(p-l)<=z && z<l+F[j+1]*(p-l))
			{
				c=j;
				printf("(%f <= %f < %f), j==%i\n", l+F[j]*(p-l), z, l+F[j+1]*(p-l), j);
				break;
				
			}
		}	
		
		out[i]=alf[c];
		printf("out[%i] = alf[%i]\n", i, c);
		
		d = p-l;
		p = l+F[c+1]*d;
		l = l+F[c]*d;
			
	}
	printf("%c \n%c \n%c \n%c string\n", out[0], out[1], out[2], alf[0]);
	printf("%s\n", out);
	*/
	
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


