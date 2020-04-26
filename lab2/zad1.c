#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define S 64
#define ALFABET 10

int main()
{
	FILE* fptr; 
	char alf[ALFABET] = "abcdefghkl";
	//char arr[S] = "abccabaa"; //8
	char arr[S] = "abccabaaabccabaaabccabaaabfcabaaabccabaaabccabaaabccabaaabccabaa";	//64
	float pw[S] = {0.5, 0.1, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
	float F[S+1];
	float l = 0;
	float p = 1;
	
	F[0]=0;
	float counter = 0;
	for (int i=0;i<S;i++)
	{
		counter += pw[i];
		F[i+1]=counter;
	}	

	fptr = fopen("troika.txt", "w"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}
	
	float d;
	float z;
	for (int i=0;i<S;i++)
	{
		
		//printf("g");
		int c;
		//printf("arr[%i] %c\n", i, arr[i]);
		for(int j=0;j<ALFABET;j++)
		{
			//printf("j");
			//printf("arr[%i] %c\n", j, alf[j]);
			//printf("%i strcmp(%c, %c)\n", strcmp(&alf[j], &arr[i]), alf[j], arr[i]);
			if(alf[j]==arr[i])
			{
				//printf("l");
				c = j;
				break;
			}
			//printf("j");
		}
		
		d = p-l;
		p = l+F[c+1]*d;
		l = l+F[c]*d;
		z = (l+p)/2;
		printf("arr[%i]:%c, d:%f, l:%f, p:%f, z:%f\n",i, arr[i], d, l, p, z);
	
		int licznik = 0;
		while(true)
		{
			if(l>=0 && p<=0.5)
			{
				fprintf(fptr, "0");
				for(int cs=0;cs<licznik;cs++)
				{
					fprintf(fptr, "1");
				}
				//printf("case 1\n");
				l=2*l;
				p=2*p;
				licznik=0;
			}
			else if(l>=0.5 && p<=1)
			{
				fprintf(fptr, "1");
				for(int cs=0;cs<licznik;cs++)
				{
					fprintf(fptr, "0");
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
				//printf("\n");
				
			}
			else 
				break;			
		}
		//printf("~\n");
		printf("arr[%i]:%c, d:%f, l:%f, p:%f, z:%f\n",i, arr[i], d, l, p, z);
	}	
	fclose(fptr);
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