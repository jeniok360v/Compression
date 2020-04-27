#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 256



int main()
{
	unsigned char n = 'D';
	for(int j=0;j<SIZE;j++)
	{
		if(j==n)
			printf("%i", j);
	}
	
	return 0;
}