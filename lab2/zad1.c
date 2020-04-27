#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 256
#define ALFABET 10

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
	
	long long int size=0;
	unsigned char buffer = 0;
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
	output = fopen("archive.txt", "w"); 
	if (output == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
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
		int licznik = 0;
		while(true)
		{
			//printf("d:%f, l:%f, p:%f, z:%f\n", d, l, p, z);
			if(l>=0 && p<=0.5)
			{
				fprintf(output, "0");
				for(int cs=0;cs<licznik;cs++)
				{
					fprintf(output, "1");
				}
				//printf("case 1\n");
				l=2*l;
				p=2*p;
				licznik=0;
			}
			else if(l>=0.5 && p<=1)
			{
				fprintf(output, "1");
				for(int cs=0;cs<licznik;cs++)
				{
					fprintf(output, "0");
				}
				l=2*l-1;
				p=2*p-1;	
				licznik=0;
			}
			else if(l>=0.25 && p<=0.75)
			{
				licznik+=1;
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





