#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "helper.h"
#include "gamma.h"

using namespace std;

string delta_encode(int n)
{
	string str1 = int2bin_str(n);
	string str2 = gamma_encode(str1.size());
	str1.erase(0, 1);
	return str2+str1;
}

vector<int> my_delta_decode(string str)
{
	vector<int> arr;
	int counter = 0;
	while(counter < str.length())
	{
		int bits1 = 0;
		while(str.at(counter)=='0')
		{
			counter++;
			bits1++;		
		}
		int bit_size = stoi(str.substr(counter,bits1+1), 0, 2);
		counter += bits1+1;
		arr.push_back(stoi("1"+str.substr(counter, bit_size-1), 0, 2));
		counter += bit_size-1;
	}
	return arr;
}








