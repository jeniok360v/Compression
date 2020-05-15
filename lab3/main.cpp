#include <iostream>
#include "head.h"
#include <bitset>
#include <string>

using namespace std;

int main()
{
	string str = "";
	for(int i=1;i<14;i++)
	{
		str += fib_encode(i);
	}
	vector<int> ar;
	//int ar[13]={};
	//cout << str << endl;
	ar = fib_decode(13, str);
	for(int i=0;i<13;i++)
	{
		//cout << ar.at(i) << endl;
	}
	
	vector<int> oc;
	string s = "wabba-wabba-wabba-woo-woo-woo";
	oc = encode(s);
	
	string st = "";
	for(int i=0;i<oc.size();i++)
	{
		st += delta_encode(oc.at(i));
	}
	
	vector<int> newvec = my_delta_decode(oc.size(), st);
	
	str = "";
	str = decode(newvec);
	
	cout << str << endl;
	//cout << bitset< 64 >( 12345 ).to_string() << endl;
	//cout << int2bin_str(6) << endl;
	//cout << endl << endl << omega_encode(137) << endl;
}