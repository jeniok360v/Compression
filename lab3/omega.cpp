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