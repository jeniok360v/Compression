#include <stdio.h>
#include <string.h>
#include <math.h>

#define S 3



int main()
{
	char alf[S] = "abc";
	char arr[S] = "abc";	
	
	for(int i=0;i<S;i++)
	{
		for(int j=0;j<S;j++)
		{
			printf("%i\n", strcmp(&alf[i], &alf[j]));
		}
	}
	
	return 0;
}