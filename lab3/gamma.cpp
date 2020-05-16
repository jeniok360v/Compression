#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "helper.h"

using namespace std;


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

vector<int> gamma_decode(string str)
{
	vector<int> arr;
	int counter = 0;
	
	while (counter < str.length())
	{
		int bits = 0;
		while(str.at(counter)=='0')
		{
			counter++;
			bits++;		
		}
		arr.push_back(stoi(str.substr(counter,bits+1), 0, 2));
		counter += bits +1;
	}
	return arr;
}






















