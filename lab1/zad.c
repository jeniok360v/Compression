#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>

#define SIZE 256

float calculate_entr(int arr[SIZE], long int amount);
float calculate_cond_entr(int arr[SIZE][SIZE], int ilosc[SIZE], long int amount);


int main(int argc, char* argv[]) 
{ 
	if(argc!=2)
	{
		printf("Prosze podac 1 plik!\n");
		return 0;
	}
	
	FILE *fptr; 
	int ilosc[SIZE];
	for (int i=0; i<SIZE;i++)
	{
		ilosc[i]=0;
	}
	
	int ilosc_war[SIZE][SIZE];
	for (int i=0;i<SIZE;i++)
	{
		for(int k=0;k<SIZE;k++)
		{
			ilosc_war[i][k]=0;
		}
	}

	fptr = fopen(argv[1], "rb"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	} 

	// Wczytywanie pliku
	long int amount=0;
	unsigned char buffer0 = 0;
	unsigned char buffer1;
	int n;
	while((n = fread(&buffer1, 1, 1, fptr)) != 0)
	{
		ilosc[(int)buffer1]++;
		ilosc_war[(int)buffer0][(int)buffer1]++;
		amount++;
		
		buffer0=buffer1;
	}
	

	float p_wo[SIZE];	//prawdopodobienstwo
	for(int i=0;i<SIZE;i++)
	{
		p_wo[i]=(float)ilosc[i]/(float)amount;
	}
	
	
	ilosc[(int)buffer0]--;	//skrajne przypadki
	ilosc[0]++;	
	float p_wo_war[SIZE][SIZE];	//prawdopodobienstwo warunkowe
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			p_wo_war[i][j]=(float)ilosc_war[i][j]/(float)ilosc[i];
		}
	}
	ilosc[0]--;
	ilosc[(int)buffer0]++;
	
	for(int i=0;i<SIZE;i++)
	{
		if(ilosc[i]>0)
		{
			printf("p(%3d): %f\n", i, p_wo[i]);
		}
	}

	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(ilosc_war[i][j]>0)
			{
				printf("p(%3d|%3d): %f\n", j, i, p_wo_war[i][j]);
			}
		}
	}

	if(amount>0)
	{
		float entr = calculate_entr(ilosc, amount);
		float cond_entr = calculate_cond_entr(ilosc_war, ilosc, amount);
		printf("\nentropia - %f", entr);	
		printf("\nentropia warunkowa - %f", cond_entr);	
		printf("\nroznica - %f", entr-cond_entr);
	}
	else
	{
		printf("Plik %s jest pusty!\n", argv[1]);
	}
	fclose(fptr); 
	return 0; 
}

float calculate_entr(int ilosc[SIZE], long int amount)	//amount to liczba bajtow
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

float calculate_cond_entr(int ilosc_war[SIZE][SIZE], int ilosc[SIZE], long int amount)
{
	float entropy=0;
	if(amount>0)
	{
		for (int i=0; i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++)
			{
				if(ilosc_war[i][j]>0)
				{
					entropy += ilosc_war[i][j]*(log2(ilosc_war[i][j]));
				}
			}
		}
		for (int i=0; i<SIZE;i++)
		{
			if(ilosc[i]>0)
			{
				entropy -= ilosc[i]*(log2(ilosc[i]));
			}
		}
		entropy= -entropy/(float)amount;
	}	
	return entropy;
}



