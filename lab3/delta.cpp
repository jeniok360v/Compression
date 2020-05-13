#include <iostream>
#include <string>
#include "gamma.h"

using namespace std;

string delta_encode(int n)
{
	string str1 = int2bin_str(n);
	string str2 = gamma_encode(str1.size());
	str1.erase(0, 1);
	return str2+str1;
}

void my_delta_decode(int length, string str, int arr[])
{
	int counter = 0;
	for(int i=0;i<length;i++)
	{
		int bits1 = 0;
		while(str.at(counter)=='0')
		{
			counter++;
			bits1++;		
		}
		int bit_size = stoi(str.substr(counter,bits1+1), 0, 2);
		counter += bits1+1;
		arr[i]=stoi("1"+str.substr(counter, bit_size-1), 0, 2);
		counter += bit_size-1;
	}
}








