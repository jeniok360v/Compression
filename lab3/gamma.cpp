#include "elias.h"
#include <iostream>
#include <string>

using namespace std;

string int2bin_str(int n)
{
	string str;
    while(n!=0) 
	{
		str=(n%2==0 ?"0":"1")+str; 
		n/=2;
	}
    return str;
}

string gamma_encode(int n)
{
	string str1 = int2bin_str(n);
	string str2 = "";
	for(int i=1;i<str1.size();i++)
	{
		str2+= "0";
	}
	return str2+str1;
}

void gamma_decode(int length, string str, int arr[])
{
	string temp[length];
	int counter = 0;
	
	for(int i=0;i<length;i++)
	{
		int bits = 0;
		while(str.at(counter)=='0')
		{
			counter++;
			bits++;		
		}
		arr[i]=stoi(str.substr(counter,bits+1), 0, 2);
		counter += bits +1;
	}
}





















