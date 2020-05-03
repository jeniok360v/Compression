#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 256

typedef unsigned char uchar;
typedef unsigned long int ulint;

double binseq2double(uchar* arr, int position, int length);
void encode_lli(unsigned long long int n, unsigned char buf[8]);
unsigned long long int decode_lli(unsigned char buf[8]);

float decode_float(unsigned char buf[4]);
void encode_float(float n, unsigned char buf[4]);
void encode_ulint(ulint n, uchar buf[4]);
ulint decode_ulint(unsigned char buf[4]);

int main()
{
	uchar* file_bits = (uchar*)malloc(32*sizeof(char)*8);
	file_bits = "0101011010010101011";
	printf("binseq: %lf\n\n", binseq2double(file_bits, 0, 19));
	
	
	uchar buffer = 'a';
	char c[8];	
	itoa(buffer, c, 2);
	for(int i=0;i<8;i++)
	{
		printf("%c",c[i]);
	}
	printf("\n\n");	

	FILE* f;
	f = fopen("f.txt", "wb"); 
	
	unsigned char buf[4] = {0};
	ulint die = 427294;
	//ulint die = 1;
	
	encode_ulint(die, buf);	
	for(int i=0;i<4;i++)
	{
		printf("%i: %c(%i)\n", i, buf[i], buf[i]);
	}
	printf("float: %lu\n", die);
	//fprintf(f, "%08c", &buf);
	//fputs(buf, f);
	fwrite(buf, sizeof(buf), 1, f);
	//printf("sizeof buf:%i\n", sizeof(buf));
	
	
	fclose(f);
	printf("~~~~~~reading~~~~~~\n");
	f = fopen("f.txt", "rb"); 
	unsigned char buf2[4] = {0};

	fread(buf2, sizeof(buf2), 1, f);
	for(int i=0;i<4;i++)
	{
		printf("%i: %c(%i)\n", i, buf2[i], buf2[i]);
	}	
	ulint sz = decode_ulint(buf2);
	printf("float: %lu\n", sz);
	
	fclose(f);
	return 0;
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

void encode_lli(unsigned long long int n, unsigned char buf[8])
{
	for(int i=0;i<8;i++)
	{
		buf[7-i] = n%256;
		n /= 256;
	}
}

unsigned long long int decode_lli(unsigned char buf[8])
{
	unsigned long long int n = *(unsigned long long int*)(buf);
	unsigned long long int temp = 1;
	for(int i=0;i<8;i++)
	{
		//temp = (buf[7-i])*pow(256,(i+1));
		
		n += (buf[7-i])*temp;
		temp*=256;
		//printf("n:%lli, temp:%lli\n", n, temp);
	}
	return n;
}

float decode_float(unsigned char buf[4])
{
	float f1 = *(float*)(buf);
	return f1;	
}

void encode_float(float n, unsigned char bytes_temp[4])
{ 
	memcpy(bytes_temp, (unsigned char*) (&n), 4);
	return;
}

void encode_ulint(ulint n, uchar buf[4])
{ 
	memcpy(buf, (uchar*) (&n), 4);
	return;
}

ulint decode_ulint(unsigned char buf[4])
{
	ulint f1 = *(ulint*)(buf);
	return f1;	
}
