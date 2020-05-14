#include <iostream>
#include <string>
#include "gamma.h"

using namespace std;

string omega_encode(int n)
{
	string str = "0";
	int k = n;
	while (k>1)
	{
		string tmp = int2bin_str(k);
		str = tmp+str;
		k = tmp.size()-1;
	}
	return str;
}

void omega_decode(int length, string str, int arr[])
{
	int counter = 0;
	for(int i=0;i<length;i++)
	{
		string str2="";
		int n = 1;
		while(str.at(counter)=='1')
		{
			int temp = n;
			n = stoi(str.substr(counter,n+1), 0, 2);
			counter+=temp+1;
		}
		counter++;
		arr[i]=n;
	}
}
