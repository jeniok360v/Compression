#include <iostream>
#include "head.h"
#include <bitset>

using namespace std;

int main()
{
	string str = "";
	for(int i=1;i<14;i++)
	{
		str += omega_encode(i);
	}
	int ar[13]={};
	//cout << str << endl;
	omega_decode(13, str, ar);
	for(int i=0;i<13;i++)
	{
		cout << ar[i] << endl;
	}

	//cout << bitset< 64 >( 12345 ).to_string() << endl;
	//cout << int2bin_str(6) << endl;
	//cout << endl << endl << omega_encode(137) << endl;
}