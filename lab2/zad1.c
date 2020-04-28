#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define ALFABET 10

typedef unsigned long long int ullint;
typedef unsigned char uchar;


void encode_lli(ullint n, uchar buf[8]);
ullint decode_lli(uchar buf[8]);

float decode_float(uchar buf[4]);
void encode_float(float n, uchar buf[4]);



int main()
{
	FILE* output; 
	FILE* fptr2;
	int amount[SIZE]={0};
	float probability[SIZE]={0.0};
	fptr2 = fopen("input.txt", "rb"); 
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
	
	for(int i=0;i<SIZE;i++)
	{
		if(amount[i]>0)
		{
			printf("amount[%i]: %i\n", i, amount[i]);
		}
	}
	*/
	
	fptr2 = fopen("input.txt", "rb"); 
	output = fopen("archive.bin", "w"); 
	if (output == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}
	
	uchar buf[sizeof(ullint)];
	ullint die = 2575327;
	encode_lli(die, buf);
	fwrite(buf, sizeof(buf), 1, output);
	
	uchar buf2[sizeof(float)] = {0};
	for(int i=0;i<SIZE;i++)
	{
		encode_float(F[i+1], buf2);
		fwrite(buf2, sizeof(buf2), 1, output);
	}
	
	
	
	float l = 0;
	float p = 1;	
	float d;
	float z;
	while((n = fread(&buffer, 1, 1, fptr2)) != 0)
	{
		
		//printf("g");
		int c;
		//printf("arr[%i] %c\n", i, arr[i]);
		for(int j=0;j<SIZE;j++)
		{
			//printf("j");
			//printf("arr[%i] %c\n", j, alf[j]);
			//printf("%i strcmp(%c, %c)\n", strcmp(&alf[j], &arr[i]), alf[j], arr[i]);
			if(j==buffer)
			{
				//printf("l");
				c = j;
				break;
			}
			//printf("j");
		}
		//printf("\nl:%f, p:%f\n", l, p);
		d = p-l;
		p = l+F[c+1]*d;
		l = l+F[c]*d;
		z = (l+p)/2;
		printf("d:%f, l:%f, p:%f, z:%f, F[%i]:%f, F[%i]:%f\n", d, l, p, z, c, F[c], c+1, F[c+1]);
		int counter = 0;
		while(true)
		{
			//printf("d:%f, l:%f, p:%f, z:%f\n", d, l, p, z);
			if(l>=0 && p<=0.5)
			{
				fprintf(output, "0");
				for(int i=0;i<counter;i++)
				{
					fprintf(output, "1");
				}
				//printf("case 1\n");
				l=2*l;
				p=2*p;
				counter=0;
			}
			else if(l>=0.5 && p<=1)
			{
				fprintf(output, "1");
				for(int i=0;i<counter;i++)
				{
					fprintf(output, "0");
				}
				l=2*l-1;
				p=2*p-1;	
				counter=0;
			}
			else if(l>=0.25 && p<=0.75)
			{
				counter+=1;
				l=2*l-0.5;				
				p=2*p-0.5;	
			}
			else 
				break;			
		}
		//printf("~\n");
		//printf("arr[%i]:%c, d:%f, l:%f, p:%f, z:%f\n",i, arr[i], d, l, p, z);
	}	
	fclose(output);
	
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
	
	
	//sprintf(decode_buff, "%08lli", decode_size);
	//sscanf(decode_buff, "%08lli", &decode_size);
	
	//printf("size decode: %lli\n", decode_size);
	fclose(fdecode);
	
	
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

void encode_float(float n, uchar buf[4])
{ 
	memcpy(buf, (uchar*) (&n), 4);
	return;
}